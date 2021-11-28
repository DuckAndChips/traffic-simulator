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