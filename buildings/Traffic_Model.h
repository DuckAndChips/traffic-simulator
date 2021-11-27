#include "buildings/Clinic.h"
#include "buildings/Hospital.h"
#include "buildings/SilverMine.h"
#include "buildings/GoldMine.h"
#include "buildings/House.h"
#include "buildings/Apartment.h"

/**
 * The following code should be incorperatred into the city's class, probably
 */ 


vector<Residential*> all_residential_buildings;
vector<Revenue*> all_revenue_buildings;
vector<Health*> all_health_buildings;


/**
 * The following code should remained here
 * This source code should be involving all global functions that handle the OD Matrix
 * The initialisation of the OD_Maxtrix should be handled outside this source code
 */ 

#include <vector>
#include <algorithm>
using namespace std;

#include "City.h"
#include "Node.h"
#include "buildings/Road.h"


class Trip_Generation {
    
    public:
        int find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& paths);
        static const int max_path{999};
};



/**
 * WARNING
 * This class is designed to handle Road* instead of Node*
 * DO NOT PASS IN ANY VECTOR OF Node* TO THE OBJECTS OF THIS CLASS
 */
class Trip_Assignment {
    
    private:

        std::vector<Road*> origin;
        std::vector<Road*> destination;
        std::vector<std::vector<int>> OD_Matrix;
        City &city;
    public:

        /// The incremental portion that used in trip assignment
        static const int incremental_amount{1};        

        /// constructors and functions that setup data members
        explicit Trip_Assignment();
        explicit Trip_Assignment(std::vector<Road*> origin, std::vector<Road*> destination, std::vector<std::vector<int>> OD_Matrix);
        void set_Traffic_Model(std::vector<Road*> origin, std::vector<Road*> destination, std::vector<std::vector<int>> OD_Matrix);

        /// Main functions used for trip assigment
        void trip_assignment_main();

        /// Remaining are some helper functions that needed for trip assignment 
        
        /// This function is used for checking whether the origin, destination, OD_matrix are probably set in correct size
        /// return true when there is an inconsistency in the size of them or they are empty 
        bool size_checking() const;

        /// This function is used to return a vector of Road* vector that records all possible paths from start_pt to end_pt
        std::vector<std::vector<Road*>> get_all_paths(Road* start_pt, Road* end_pt);
        bool get_all_paths(Road* start_pt, Road* end_pt,std::vector<std::vector<Road*>>& paths); /// an overloading function used for recursion 

        /// This function load each incremental flows to the road paths with shortest travel time
        void load_traffic(std::vector<std::vector<Road*>> &paths);

        /// This function returns the travel time of a given road path
        double get_travel_time(std::vector<Road*> &path);
};








