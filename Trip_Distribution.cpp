#include "Trip_Distribution.h"
#include <iostream>
#include <cmath>
#include <QDebug>
#include "City.h"
using namespace std;


/***
for trip distribution step (step 2), first, initiallize the 3 vectors containing all residential, revenue and health categories building respectively in the object
***/
Trip_Distribution::Trip_Distribution(City &city, std::vector<Residential*> & residential_buildings,
        std::vector<Revenue*> & revenue_buildings, std::vector<Health*> & health_buildings):
        all_residential_building(residential_buildings), all_revenue_building(revenue_buildings),
        all_health_building(health_buildings), city(city){

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

/***
After creating the object, this main funciton is called. 
1. checking is done
2. call the set_origin() fucntion to set the origin vector, 
containing all road pointers pointed by all residential buidings. Each residential building corresponds to each road tile. 
3. either:
        3a. For home_work_trips, call set_work_destination() to set vector destination containing road pointers pointed by all revenue buildings
        3b. For home_health_trips, call set_health_destination() to set vector destination containing road pointers pointed by all health buildings
4. for each road tile in origin, generate the shortest path to road tile in each destination. Using the attrctiveness and shortest path, 
compute the factor for each origin-destiantion pair and store to factor 2d matrix, as well as store shortest path road nodes for all origin-destiantion pair. 
5. using the factor matrix and total number of trips for that origin to all destiantions in that category, 
assign the number of trips for that origin-destiantion pair in OD_matrix 2d matrix.
6. As the origin, destination and OD_matrix is passed by reference, and city is friend of Trip_Distribution, they can be used by other fucntions owned by city. 
***/
bool Trip_Distribution::trip_distribution_main(Node::Category category){
    /// No need for distribution and assignment
    if(all_residential_building.size() == 0 || category == Node::Category::RESIDENTIAL || category == Node::Category::ROAD)
        return false;

    /// Error check: this function should not be called twice
    if(origin.size() != 0 || destination.size() != 0 || all_destination_building.size() != 0) return false;
    set_origin(); // 2. origin vector is set here
    if(category == Node::Category::REVENUE){
        if(all_revenue_building.size() == 0 ) return false; /// 3a. No need for distribution and assignment
        set_work_destination(); //destination for home_work_trips is set here
    }else if(category == Node::Category::HEALTH){
        if(all_health_building.size() == 0 ) return false; /// 3b. No need for distribution and assignment
        set_health_destination(); //destination for home_health_trips is set here
    } else {return false;}

    /// Error check: check for size consistency
    if( all_residential_building.size() != origin.size() ||
        (all_revenue_building.size() != all_destination_building.size() && all_health_building.size() != all_destination_building.size())  ||
        all_destination_building.size() != destination.size()
        )return false;

    /// Error check: this function should not be called twice
    if(!(factors.size() == 0 || OD_path.size() == 0 || OD_matrix.size() == 0)) return false;
    set_factor_and_OD_path(); // 5. factor and OD path(shortest distance between each origin and destination) is set here
    set_OD_matrix(category); // 6. OD matrix containing number of trips from each origin to each destination is set here
    return true;
}

/***
2. origin vector is set by iterating all residential buidnings in all_residential_buildings and push back their corrsponding road pointer to origin vector
***/
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

/*** 
3a. For home_work_trips, call set_work_destination() to set vector destination by iterating all revenue buildings in all_revenue_buildings and push back their corrsponding 
road pointer to destination vector
***/
void Trip_Distribution::set_work_destination(){
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


/*** 
3b. For home_health_trips, call set_health_destination() to set vector destination by iterating all health buildings in all_health_buildings and push back their corrsponding 
road pointer to destination vector
***/
void Trip_Distribution::set_health_destination(){
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

/***
4. for each road tile in origin, generate the shortest path to road tile in each destination. Using the attrctiveness and shortest path, 
compute the factor for each origin-destiantion pair and store to factor 2d matrix, as well as store shortest path road nodes for all origin-destiantion pair. 
***/
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
            if(dist >= max_path){
                factors[i].push_back(0);
                OD_path[i].push_back(vector<Road*>());
            }else if(dist >= 0){
                factors[i].push_back(all_destination_building[j]->get_attractiveness()/dist);
                OD_path[i].push_back(path);
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

// overlaod fucntion when path is not needed for finding shortest path.
int Trip_Distribution::find_shortest_path(Road* start_pt, Road* end_pt){
    std::vector<Road*> temp;
    return find_shortest_path(start_pt, end_pt, temp);
}

/*** 
helper fucntion used by 
***/
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

    /// case 2: all road options have been walked
        std::vector<Road*> road_options;
        if(start_pt->get_neighboring_road(Node::Direction::NORTH)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::NORTH)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::NORTH));
        }
        if(start_pt->get_neighboring_road(Node::Direction::EAST)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::EAST)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::EAST));
        }
        if(start_pt->get_neighboring_road(Node::Direction::SOUTH)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::SOUTH)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::SOUTH));
        }

        if(start_pt->get_neighboring_road(Node::Direction::WEST)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::WEST)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::WEST));
        }
    if(road_options.empty()) return max_path; /// case 2 return statement

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

/***
5. using the factor matrix and total number of trips for that origin to all destiantions in that category, assign the number of trips for that origin-destiantion pair 
in OD_matrix 2d matrix.
***/
void Trip_Distribution::set_OD_matrix(Node::Category category){

    for(unsigned int i = 0; i < factors.size(); ++i){
        OD_matrix.push_back(std::vector<int>());

        int total_trips = 0;

        /// get total number of trips, depending on category
        if(category == Node::Category::REVENUE){
            total_trips = all_residential_building[i]->get_work_trips();
        }else if(category == Node::Category::HEALTH){
            total_trips = all_residential_building[i]->get_health_trips();
        }

        /// set OD_matrix
        for(unsigned int j=0; j<factors[i].size(); ++j){
            OD_matrix[i].push_back(total_trips*factors[i][j]);
        }
    }
}
