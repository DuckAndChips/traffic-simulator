#include "Traffic_Model.h"

#include <iostream>
#include <cmath>
using namespace std;


/**
 * The following set functions maybe move to city's class

Trip_Distribution::Trip_Distribution(City &city):city(city){
    Trip_Distribution::set_all_residential();
    Trip_Distribution::set_all_revenue();
    Trip_Distribution::set_all_health();
}

void Trip_Distribution::set_all_residential(){
    for(int i=0; i<city.get_grid_size(); ++i){
        for(int j=0; j<city.get_grid_size(); ++j){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::RESIDENTIAL){
                    all_residential_building.push_back(dynamic_cast<Residential*>(city.grid[i][j]));
                }
            }
        }
    }
}

void Trip_Distribution::set_all_revenue(){
    for(int i=0; i<city.get_grid_size(); ++i){
        for(int j=0; j<city.get_grid_size(); ++j){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::REVENUE){
                    all_destination_building.push_back(dynamic_cast<Revenue*>(city.grid[i][j]));
                }
            }
        }
    }
}

void Trip_Distribution::set_all_health(){
    for(int i=0; i<city.get_grid_size(); ++i){
        for(int j=0; j<city.get_grid_size(); ++j){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::HEALTH){
                    all_destination_building.push_back(dynamic_cast<Health*>(city.grid[i][j]));
                }
            }
        }
    }
}
*/

Trip_Distribution::Trip_Distribution(City &city, std::vector<Residential*> & residential_buildings,
        std::vector<Revenue*> & revenue_buildings, std::vector<Health*> & health_buildings):
        city(city),all_residential_building(residential_buildings),
        all_revenue_building(revenue_buildings), all_health_building(health_buildings){}

Trip_Assignment::Trip_Assignment(City &citi, std::vector<Road*>& origins, std::vector<Road*>& destinations, std::vector<std::vector<int>>& OD):
        city(citi),origin(origins),destination(destinations), OD_Matrix(OD){}

void Trip_Assignment::set_Traffic_Model(std::vector<Road*> &origins, std::vector<Road*> &destinations, std::vector<std::vector<int>> &OD){
    this->origin = origins;
    this->destination = destination;
    this->OD_Matrix = OD;
}

bool Trip_Distribution::trip_distribution_main(Node::Category category){
    /// No need for distribution and assignment
    if(all_residential_building.size() == 0 || category == Node::Category::RESIDENTIAL || category == Node::Category::ROAD)
        return false;

    /// Error check: this function should not be called twice
    if(origin.size() != 0 || destination.size() != 0 || all_destination_building.size() != 0) return false;
    set_origin();
    if(category == Node::Category::REVENUE){
        if(all_revenue_building.size() == 0 ) return false; /// No need for distribution and assignment
        set_work_destination();
    }else if(category == Node::Category::HEALTH){
        if(all_health_building.size() == 0 ) return false; /// No need for distribution and assignment
        set_health_destination();
    } else {return false;}

    /// Error check: check for size consistency
    if( all_residential_building.size() != origin.size() ||
        (all_revenue_building.size() != all_destination_building.size() && all_health_building.size() != all_destination_building.size())  ||
        all_destination_building.size() != destination.size()
        )return false;
    
    /// Error check: this function should not be called twice
    if(factors.size() == 0 || OD_path.size() == 0 || OD_matrix.size() == 0) return false;
    set_factor_and_OD_path();
    set_OD_matrix(category);
    return true;    
}

void Trip_Distribution::set_origin(){
    for(std::vector<Residential*>::iterator i = all_residential_building.begin(); i != all_residential_building.end(); i++){
        Residential* residential = *i;
        if(residential->is_neighbor_road(Node::Direction::NORTH) == true){
            origin.push_back(dynamic_cast<Road*>(residential->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(residential->is_neighbor_road(Node::Direction::EAST) == true){
            origin.push_back(dynamic_cast<Road*>(residential->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(residential->is_neighbor_road(Node::Direction::SOUTH) == true){
            origin.push_back(dynamic_cast<Road*>(residential->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(residential->is_neighbor_road(Node::Direction::WEST) == true){
            origin.push_back(dynamic_cast<Road*>(residential->get_neighboring_node(Node::Direction::WEST)));
        }else{
            origin.push_back(nullptr);
        }
    }
}

void Trip_Distribution::set_work_destination(){
    // all_destination_building = static_cast<std::vector<Node*>>(all_revenue_building);
    for(std::vector<Revenue*>::iterator i = all_revenue_building.begin(); i != all_revenue_building.end(); i++){
        Revenue* revenue = *i;
        all_destination_building.push_back(revenue);
        if(revenue->is_neighbor_road(Node::Direction::NORTH) == true){
            destination.push_back(dynamic_cast<Road*>(revenue->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::EAST) == true){
            destination.push_back(dynamic_cast<Road*>(revenue->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::SOUTH) == true){
            destination.push_back(dynamic_cast<Road*>(revenue->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::WEST) == true){
            destination.push_back(dynamic_cast<Road*>(revenue->get_neighboring_node(Node::Direction::WEST)));
        }else{
            destination.push_back(nullptr);
        }
    }
}

void Trip_Distribution::set_health_destination(){
    // all_destination_building = static_cast<std::vector<Node*>>(all_health_building);
    for(std::vector<Health*>::iterator i = all_health_building.begin(); i != all_health_building.end(); ++i){
        Health* health = *i;
        all_destination_building.push_back(health);
        if(health->is_neighbor_road(Node::Direction::NORTH) == true){
            destination.push_back(dynamic_cast<Road*>(health->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(health->is_neighbor_road(Node::Direction::EAST) == true){
            destination.push_back(dynamic_cast<Road*>(health->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(health->is_neighbor_road(Node::Direction::SOUTH) == true){
            destination.push_back(dynamic_cast<Road*>(health->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(health->is_neighbor_road(Node::Direction::WEST) == true){
            destination.push_back(dynamic_cast<Road*>(health->get_neighboring_node(Node::Direction::WEST)));
        }else{
            destination.push_back(nullptr);
        }
    }
}


void Trip_Distribution::set_factor_and_OD_path(){
    for(int i=0; i<origin.size(); i++){
        /// Calculate factors using gravity model
        /// call find_shortest_path and store store the respective shortest path in OD_path
        factors.push_back(std::vector<float>());
        OD_path.push_back(std::vector<vector<Road*>>());
        for(int j=0; j<destination.size(); j++){
            std::vector<Road*>path;
            if(origin[i] == nullptr || destination[j] == nullptr){
                factors[i].push_back(0);
                OD_path[i].push_back(vector<Road*>());
                continue;
            }
            float dist = find_shortest_path(origin[i],destination[j],path);
            if(dist >= max_path){
                factors[i].push_back(0);
                OD_path[i].push_back(vector<Road*>());
            }else if(dist >= 0){
                factors[i].push_back(all_destination_building[j]->get_attractiveness()/dist);
                OD_path[i].push_back(path);
            }else{
                cerr<<"Error in Trip_Distribution::find_shortest_path: return 0 or -ve number"<<endl;
                exit(-1);
            }
        }

        /// Change factors to weight
        float total_factors = 0;
        for(int j=0; j<factors[i].size(); ++j){
            total_factors += factors[i][j];
        }
        if(total_factors == 0) continue;
        for(int j=0; j<factors[i].size(); ++j){
            factors[i][j] = factors[i][j]/total_factors;
        }
    }
}

int Trip_Distribution::find_shortest_path(Road* start_pt, Road* end_pt){
    std::vector<Road*> temp;
    return find_shortest_path(start_pt, end_pt, temp);
}

int Trip_Distribution::find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& path){

    /// handling path to make sure it contains the current road*    
    if(path.size() == 0){
        path.push_back(start_pt);
    }else{
        if(path.back() != start_pt)
            path.push_back(start_pt);
    }

    /// end cases
    /// case 1: reach destination
    if(start_pt == end_pt) return 1;

    /**
    /// case 2: reach the end of road (seems redudent here coz case 3 include case 2)
    /// 2.0 terminate as a single road
        if( start_pt->get_neighboring_road(Node::Direction::EAST) == nullptr && 
            start_pt->get_neighboring_road(Node::Direction::WEST) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::NORTH) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::SOUTH) == nullptr  
        ){
            return max_path;
        }
    if(path.size() > 0){
        /// 2.1 terminate as the north edge
        if( start_pt->get_neighboring_road(Node::Direction::EAST) == nullptr && 
            start_pt->get_neighboring_road(Node::Direction::WEST) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::NORTH) == nullptr &&
            path.back() == start_pt->get_neighboring_road(Node::Direction::SOUTH) 
            /// here have error too coz last element of path should be start_pt itself
        ){
            return max_path;
        }
        /// 2.2 terminate as the east edge
        if( start_pt->get_neighboring_road(Node::Direction::EAST) == nullptr && 
            start_pt->get_neighboring_road(Node::Direction::SOUTH) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::NORTH) == nullptr &&
            path.back() == start_pt->get_neighboring_road(Node::Direction::EAST)   
        ){
            return max_path;
        }
        /// 2.3 terminate as the south edge
        if( start_pt->get_neighboring_road(Node::Direction::EAST) == nullptr && 
            start_pt->get_neighboring_road(Node::Direction::SOUTH) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::WEST) == nullptr &&
            path.back() == start_pt->get_neighboring_road(Node::Direction::SOUTH)    
        ){
            return max_path;
        }
        /// 2.4 terminate as the west edge
        if( start_pt->get_neighboring_road(Node::Direction::WEST) == nullptr && 
            start_pt->get_neighboring_road(Node::Direction::SOUTH) == nullptr &&
            start_pt->get_neighboring_road(Node::Direction::NORTH) == nullptr &&
            path.back() == start_pt->get_neighboring_road(Node::Direction::WEST)    
        ){
            return max_path;
        }
    }
    */
        
    /// case 3: all road options have been walked
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

    if(road_options.size() == 0) return max_path; /// case 3 return statement

    /// recursive part
    int path_dist = max_path;
    std::vector<Road*> new_path = path;

    std::vector<Road*>::iterator q;
    for(q = road_options.begin(); q != road_options.end(); ++q){
        std::vector<Road*> temp = path;
        int dist = 1 + find_shortest_path(*q,end_pt,temp); 
        if(dist < path_dist){
            path_dist = dist;
            new_path = temp;
        }
    }

    path = new_path;
    return path_dist;   

}


void Trip_Distribution::set_OD_matrix(Node::Category category){

    for(int i = 0; i < factors.size(); ++i){
        OD_matrix.push_back(std::vector<int>());

        int total_trips = 0;

        /// get total number of trips, depending on category
        if(category == Node::Category::REVENUE){
            total_trips = all_residential_building[i]->get_work_trips();
        }else if(category == Node::Category::HEALTH){
            total_trips = all_residential_building[i]->get_health_trips();
        }else{
            cerr<<"Weird category input in Trip_Distribution::OD_matrix_traffic"<<endl;
            exit(-1);
        }

        /// set OD_matrix
        for(int j=0; j<factors[i].size(); ++j){
            OD_matrix[i].push_back(total_trips*factors[i][j]);
        }
    }
}


void Trip_Assignment::trip_assignment_main(){
    
    /// Error checking
    if(size_checking()){
        return;
    }

    /// loops
    for(int i = 0; i < origin.size(); ++i){
        if(origin[i] == nullptr) continue;
        for(int j = 0; j < destination.size(); ++j){
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

    for(int i=0; i < road_options.size(); ++i){
        std::vector<std::vector<Road*>> temp_paths;
            std::vector<Road*> path_zero;
            path_zero.push_back(road_options[i]);
            std::vector<Road*> temp_path;
            temp_path = path;
            temp_path.push_back(road_options[i]);
        temp_paths.push_back(path_zero);
        if(get_all_paths(road_options[i],end_pt,temp_paths,temp_path)){
            for(int j = 0; j < temp_paths.size(); ++j){
                add_paths.push_back(temp_paths[j]);
            }
        }
    }

    if(add_paths.size()==0) return false;

    paths[0].insert(paths[0].end(),add_paths[0].begin(),add_paths[0].end());

    for(int i = 1; i <add_paths.size(); ++i){
        std::vector<Road*> temp = path;
        temp.insert(temp.end(),add_paths[i].begin(),add_paths[i].end());
        paths.push_back(temp);
    }

    return true;
}

void Trip_Assignment::load_traffic(std::vector<std::vector<Road*>> &paths){
    int index = 0;
    double shortest_time = get_travel_time(paths[0]);
    for(int i = 1; i<paths.size(); ++i){
        double time = get_travel_time(paths[i]);
        if(time < shortest_time){
            index = i;
            shortest_time = time;
        }
    }
    for(int j=0; j<paths[index].size(); ++j){
        paths[index][j]->traffic_flow_incremental(incremental_amount);
    }
}

double Trip_Assignment::get_travel_time(std::vector<Road*> &path){
    double time = 0;
    for(int i = 0; i < path.size(); ++i){
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


