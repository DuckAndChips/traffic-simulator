#ifndef TRIP_ASSIGNMENT_H
#define TRIP_ASSIGNMENT_H

#include "buildings/Clinic.h"
#include "buildings/Hospital.h"
#include "buildings/SilverMine.h"
#include "buildings/GoldMine.h"
#include "buildings/House.h"
#include "buildings/Apartment.h"
#include "buildings/Node.h"
#include "buildings/Road.h"

#include <vector>
#include <algorithm>
using namespace std;


/**
 * Trip_Assignment is a class that perform the fourth step of the sequential demand focasting model.
 * 
 * Incremental Assignment is used in this class, in which:
 * -    A portion of the O-D entries is assigned at each iteration.
 * -    Travel times are then updated and an additional portion of the O-D matrix is loaded onto the network.
 * 
 * The result of the trip assignment will be loaded to the road network directly.  
 * (And therefore part of the codes used in the trip assignment step are implemented in the Road class too.
 */

/**
 * WARNINGS
 * 1.   This class is designed to handle Road* instead of Node*
 *      DO NOT PASS IN ANY VECTOR OF Node* TO THE OBJECTS OF THIS CLASS
 * 2.   This class can MODIFY the data members in Road objects
 */

class Trip_Assignment {
    
    private:
        std::vector<Road*> origin;                  /// a vector storing all pointers to the origins (Road objects)
        std::vector<Road*> destination;             /// a vector storing all pointers to the destinations (Road objects)
        std::vector<std::vector<int>> OD_Matrix;    /// a 2D vector storing the number of trips from origins to destinations

    public:

        /// The incremental portion that used in trip assignment
        static const int incremental_amount{1};        

        /// constructors and function that setup data members
        explicit Trip_Assignment() = default;
        void set_Traffic_Model(std::vector<Road*> &origins, std::vector<Road*> &destinations, std::vector<std::vector<int>> &OD);

        /// Main functions used for trip assigment
        void trip_assignment_main();

        /// This function returns the travel time of a given road path
        double get_travel_time(std::vector<Road*> &path);

        /// Remaining are some helper functions that needed for trip assignment 
        
        /// This function is used for checking whether the origin, destination, OD_matrix are probably set in correct size
        /// return true when there is an inconsistency in the size of them or they are empty 
        bool size_checking() const;

        /// This function is used to return a vector of Road* vector that records all possible paths from start_pt to end_pt
        std::vector<std::vector<Road*>> get_all_paths(Road* start_pt, Road* end_pt);
        bool get_all_paths(Road* start_pt, Road* end_pt,std::vector<std::vector<Road*>>& paths, std::vector<Road*>& path); /// an overloading function used for recursion 

        /// This function load each incremental flows to the road paths with shortest travel time
        void load_traffic(std::vector<std::vector<Road*>> &paths);

        // shortest path
        int find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& path);
};

#endif // TRIP_ASSIGNMENT_H







