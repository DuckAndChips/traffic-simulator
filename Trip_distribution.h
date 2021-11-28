/***
Trip_distribution is an object used to generate 3 vectors, which include origin matrix, destination matrix, and OD number of trips 2d vector. 
First, 3 vectors containing residential, revenue, and health buildings are generated. Then, according to the category of trips, including
home-work trips and home-health trips, it will call corresponding set origin and set destination function to set origin and destination vector. 
After that, travel time matrix and number of trips matrix is generated one after he other. 
***/
#ifndef TRIP_DISTRIBUTION_H
#define TRIP_DISTRIBUTION_H

#include <vector>
#include <algorithm>
#include "Buildings/Road.h"
#include "Buildings/Residential.h"
#include "City.h"
#include "Traffic_Model.h"
using namespace std;

class Trip_distribution{
    private:
        std::vector<Residential*> all_residential_building;
        std::vector<Revenue*> all_revenue_building;
        std::vector<Health*> all_health_building;
        std::vector<Node*> all_destination_building;

        std::vector<Road*> origin;
        std::vector<Road*> destination;
        std::vector<vector<int>> travel_time;
        std::vector<vector<int>> OD_matrix_number_of_trips;
        City& city;
        Trip_Generation trip_generation;
    public:
        explicit Trip_distribution(City& city);
        void set_all_residential();
        void set_all_revenue();
        void set_all_health();

        void set_origin();
        void set_work_destination();
        void set_health_destination();

        void OD_matrix_travel_time();
        void OD_matrix_traffic(Node::Category category);
        
        static const int max_path{999};

};



#endif //TRIP_DISTRIBUTION_H


/**********
at each turn, first create an object Trip_distibution home_work, then call Trip_distribution::set_origin() and 
Trip_distribution::set_work_destination(), then call Trip_distribution::OD_matrix_travel_time(), 
then call OD_matrix_traffic(Node::Category::REVENUE). Repeat the above, but change work to health, and REVENUE to HEALTH. 
The resulting is std::vector<Node*> origin, std::vector<Node*> destination, and std::vector<std::vector<int>> OD_matrix_number_of_trips. 
**********/ 