#include "Traffic_Model.h"

#include <iostream>
#include <cmath>
#include <QDebug>
using namespace std;


/**
 * The following set functions maybe move to city's class*/

//Trip_Distribution::Trip_Distribution(City &city):city(city){
//    Trip_Distribution::set_all_residential();
//    Trip_Distribution::set_all_revenue();
//    Trip_Distribution::set_all_health();
//}


Trip_Assignment::Trip_Assignment(City &citi, std::vector<Road*>& origins, std::vector<Road*>& destinations, std::vector<std::vector<int>>& OD):
        origin(origins),destination(destinations), OD_Matrix(OD), city(citi){}

void Trip_Assignment::set_Traffic_Model(std::vector<Road*> &origins, std::vector<Road*> &destinations, std::vector<std::vector<int>> &OD){
    this->origin = origins;
    this->destination = destinations;
    this->OD_Matrix = OD;
}

void Trip_Assignment::trip_assignment_main(){
    
    /// Error checking
    if(size_checking()){
        return;
    }

    /// loops
    for(unsigned int i = 0; i < origin.size(); ++i){
        if(origin[i] == nullptr) continue;
        for(unsigned int j = 0; j < destination.size(); ++j){
            if(destination[j] == nullptr) continue;
            int trips = OD_Matrix[i][j];
            if(trips == 0) continue;
            std::vector<std::vector<Road*>> paths = get_all_paths(origin[i], destination[j]);
            for(int k = 0; k < trips; k+= incremental_amount){
                load_traffic(paths);  
            }
        }
    }

    /// old version of code using iterator
    /**
    std::vector<Road*>::iterator p;
    int i = 0;
    for(p = origin.begin(); p != origin.end(); ++p, ++i){
        std::vector<Road*>::iterator q;
        int j = 0;
        for(q = destination.begin(); q != destination.end(); ++q, ++j){
            int trips = OD_Matrix[i][j];
            std::vector<std::vector<Road*>> paths = get_all_paths(*p, *q);
            for(int k = 0; k < trips; ++k){
                load_traffic(paths);  
            }                    
        }
    }
    */
}


std::vector<std::vector<Road*>> Trip_Assignment::get_all_paths(Road* start_pt, Road* end_pt){
    std::vector<std::vector<Road*>> paths;
    std::vector<Road*> path_zero;
    path_zero.push_back(start_pt);
    paths.push_back(path_zero);
    get_all_paths(start_pt,end_pt,paths,path_zero);
    return paths;
}

bool Trip_Assignment::get_all_paths(Road* start_pt, Road* end_pt,std::vector<std::vector<Road*>>& paths, std::vector<Road*>& path){
    
    /// source of error: index handling
    if (paths.size() == 0) return false;
    
    /// end case: reach destination
    if(start_pt == end_pt) return true;

    /// to store an array of all available road options
        std::vector<Road*> road_options;
        if(start_pt->get_neighboring_road(Node::Direction::NORTH)) 
            road_options.push_back(start_pt->get_neighboring_road(Node::Direction::NORTH));        
        if(start_pt->get_neighboring_road(Node::Direction::EAST)) 
            road_options.push_back(start_pt->get_neighboring_road(Node::Direction::EAST));
        if(start_pt->get_neighboring_road(Node::Direction::SOUTH)) 
            road_options.push_back(start_pt->get_neighboring_road(Node::Direction::SOUTH));
        if(start_pt->get_neighboring_road(Node::Direction::WEST)) 
            road_options.push_back(start_pt->get_neighboring_road(Node::Direction::WEST)); 
    
    
    std::vector<std::vector<Road*>::iterator> walked_road_options;
    for(std::vector<Road*>::const_iterator p = path.begin(); p != path.end(); ++p){
        std::vector<Road*>::iterator q;
        for(q = road_options.begin(); q != road_options.end(); ++q){
            if (*p==*q)
                walked_road_options.push_back(q);                             
        }                      
    }

    for(std::vector<std::vector<Road*>::iterator>::iterator p = walked_road_options.begin(); p != walked_road_options.end(); ++p){
       road_options.erase(*p);                     
    }

    /// end case: reach termination
    if(road_options.size() == 0) return false;

    /// recursive part
    std::vector<std::vector<Road*>> add_paths;

    for(unsigned int i=0; i < road_options.size(); ++i){
        std::vector<std::vector<Road*>> temp_paths;
            std::vector<Road*> path_zero;
            path_zero.push_back(road_options[i]);
            std::vector<Road*> temp_path;
            temp_path = path;
            temp_path.push_back(road_options[i]);
        temp_paths.push_back(path_zero);
        if(get_all_paths(road_options[i],end_pt,temp_paths,temp_path)){
            for(unsigned int j = 0; j < temp_paths.size(); ++j){
                add_paths.push_back(temp_paths[j]);
            }
        }
    }

    if(add_paths.size()==0) return false;

    paths[0].insert(paths[0].end(),add_paths[0].begin(),add_paths[0].end());

    for(unsigned int i = 1; i <add_paths.size(); ++i){
        std::vector<Road*> temp = path;
        temp.insert(temp.end(),add_paths[i].begin(),add_paths[i].end());
        paths.push_back(temp);
    }

    return true;
}

void Trip_Assignment::load_traffic(std::vector<std::vector<Road*>> &paths){
    int index = 0;
    double shortest_time = get_travel_time(paths[0]);
    for(unsigned int i = 1; i<paths.size(); ++i){
        double time = get_travel_time(paths[i]);
        if(time < shortest_time){
            index = i;
            shortest_time = time;
        }
    }
    for(unsigned int j=0; j<paths[index].size(); ++j){
        paths[index][j]->traffic_flow_incremental(incremental_amount);
    }
}

double Trip_Assignment::get_travel_time(std::vector<Road*> &path){
    double time = 0;
    for(unsigned int i = 0; i < path.size(); ++i){
        time += path[i]->get_travel_time();
    }
    return time;
}

bool Trip_Assignment::size_checking() const{
    int origin_size = origin.size();
    int destination_size = destination.size();

    /// check if the OD info are empty or not
    if(origin_size == 0 || destination_size == 0) return true;
    if(origin_size != OD_Matrix.size()) return true;

    /// check the no of rows and columns matches with origin's size and destination's size or not
    for(int i = 0; i<origin_size ; ++i){
        if(OD_Matrix[i].size() != destination_size) return true;
    }

    return false;
}

/**
bool Trip_Assignment::error_checking(Road* start_pt, const Road* end_pt, const std::vector<std::vector<Node::Direction>> &paths) const{
    if(start_pt == end_pt){
        if (paths.size()) return true;
        return false;
    }
    
    for(std::vector<std::vector<Node::Direction>>::const_iterator p = paths.begin();
        p != paths.end(); ++p){
        Road* temp = start_pt;
        for(std::vector<Node::Direction>::const_iterator q = p->begin();
            q != p->end(); ++q){
            temp = temp->get_neighboring_road(*q);  
            if(temp == nullptr) {
                cerr<<"Obtain nullptr in the paths"<<endl; 
                exit(-1);
                return true;
            }     
        }
        if(temp != end_pt) {
            cerr<< "Cannot go back to end_pt after paths"<<endl;
            exit(-1);
            return true;
        }
    }
    return false;
}
*/


