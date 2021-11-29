#include "Trip_Distribution.h"
#include <iostream>
#include <cmath>
#include <QDebug>
#include "City.h"
using namespace std;



Trip_Distribution::Trip_Distribution(City &city, std::vector<Residential*> & residential_buildings,
        std::vector<Revenue*> & revenue_buildings, std::vector<Health*> & health_buildings):
        all_residential_building(residential_buildings), all_revenue_building(revenue_buildings),
        all_health_building(health_buildings), city(city){}

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
                    all_revenue_building.push_back(dynamic_cast<Revenue*>(city.grid[i][j]));
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
                    all_health_building.push_back(dynamic_cast<Health*>(city.grid[i][j]));
                }
            }
        }
    }
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
    if(!(factors.size() == 0 || OD_path.size() == 0 || OD_matrix.size() == 0)) return false;
    set_factor_and_OD_path();
    set_OD_matrix(category);
//    //debug
//    for(unsigned int i=0; i<OD_matrix.size(); i++){
//        for(unsigned int j=0; j<OD_matrix[i].size(); j++){
//            qDebug()<<OD_matrix[i][j];
//        }
//    }
//    //debug end
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
        }
        else{
            destination.push_back(nullptr);
        }
    }
}


void Trip_Distribution::set_factor_and_OD_path(){
    for(unsigned int i=0; i<origin.size(); i++){
        /// Calculate factors using gravity model
        /// call find_shortest_path and store store the respective shortest path in OD_path
        factors.push_back(std::vector<float>());
        OD_path.push_back(std::vector<vector<Road*>>());
        for(unsigned int j=0; j<destination.size(); j++){
            std::vector<Road*>path;
            if(origin[i] == nullptr || destination[j] == nullptr){
                factors[i].push_back(0);
                OD_path[i].push_back(vector<Road*>());
                continue;
            }
            float dist = find_shortest_path(origin[i],destination[j],path);
//            qDebug()<<"shortest path"<<dist;
            for(unsigned int i=0; i<path.size(); i++){
//                path[i]->set_traffic_flow(-3);
            }
            if(dist >= max_path){
                factors[i].push_back(0);
                OD_path[i].push_back(vector<Road*>());
            }else if(dist >= 0){
                factors[i].push_back(all_destination_building[j]->get_attractiveness()/dist);
                OD_path[i].push_back(path);
            }else{
//                qDebug()<<"Error in Trip_Distribution::find_shortest_path: return 0 or -ve number"<<endl;
                exit(-1);
            }
        }

        /// Change factors to weight
        float total_factors = 0;
        for(unsigned int j=0; j<factors[i].size(); ++j){
            total_factors += factors[i][j];
        }
        if(total_factors == 0) continue;
        for(unsigned int j=0; j<factors[i].size(); ++j){
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
            start_pt->get_neighbor
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
//    qDebug()<<path_dist; //debug
    return path_dist;

}


void Trip_Distribution::set_OD_matrix(Node::Category category){

    for(unsigned int i = 0; i < factors.size(); ++i){
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
        for(unsigned int j=0; j<factors[i].size(); ++j){
            OD_matrix[i].push_back(total_trips*factors[i][j]);
        }
    }
}