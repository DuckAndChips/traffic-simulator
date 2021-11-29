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
 * In this project, our group implements the Sequential Demand Forecasting Model introduced in CIVL3610 Traffic and
 * Transportation Engineering of HKUST to predict traffic flow and respective travel time in a city.
 * 
 * The Sequential Demand Focasting Model consists of four steps:
 * Step 1: Trip Generation (Decision: to travel or not)
 * Step 2: Trip Distrubution (Decision â€“ to where, what destination?)
 * Step 3: Modal Split (Decision â€“ how, what mode?)
 * Step 4: Traffic Assignment (Decision â€“ how, which route?)
 * 
 * In this project, these four steps are implemented by the following parts of our code respectively:
 * Step 1: member functions of Residential class
 * Step 2: Trip_Distrubution class in this file
 * Step 3: This step is skiped since we do not consider multiple travel modes in the city (e.g. MTR/bus)
 * Step 4: Trip_Assignment class in this file
 */


/**
 * Trip_Assignment is a class that perform the fourth step of the sequential demand focasting model.
 * 
 * Incremental Assignment is used in this class, in which:
 * -    A portion of the O-D entries is assigned at each iteration.
 * -    Travel times are then updated and an additional portion of the O-D matrix is loaded onto the network.
 * 
 * Part of the codes used in this step are implemented in the Road class.
 * 
 * We define City as the friend class of this class for City to get the results of Trip Assignment.
 */

/**
 * WARNINGS
 * 1.   This class is designed to handle Road* instead of Node*
 *      DO NOT PASS IN ANY VECTOR OF Node* TO THE OBJECTS OF THIS CLASS
 * 2.   This class can MODIFY the data members in Road objects
 */

class Trip_Assignment {
    
    private:
        std::vector<Road*>& origin;
        std::vector<Road*>& destination;
        std::vector<std::vector<int>>& OD_Matrix;
        City &city;
        friend class City;
    public:

        /// The incremental portion that used in trip assignment
        static const int incremental_amount{1};        

        /// constructors and function that setup data members
        explicit Trip_Assignment(City &citi, std::vector<Road*>& origins, std::vector<Road*>& destinations, std::vector<std::vector<int>>& OD);
        void set_Traffic_Model(std::vector<Road*> &origins, std::vector<Road*> &destinations, std::vector<std::vector<int>> &OD);

        /// Main functions used for trip assigment
        void trip_assignment_main();

        /// Remaining are some helper functions that needed for trip assignment 
        
        /// This function is used for checking whether the origin, destination, OD_matrix are probably set in correct size
        /// return true when there is an inconsistency in the size of them or they are empty 
        bool size_checking() const;

        /// This function is used to return a vector of Road* vector that records all possible paths from start_pt to end_pt
        std::vector<std::vector<Road*>> get_all_paths(Road* start_pt, Road* end_pt);
        bool get_all_paths(Road* start_pt, Road* end_pt,std::vector<std::vector<Road*>>& paths, std::vector<Road*>& path); /// an overloading function used for recursion 

        /// This function load each incremental flows to the road paths with shortest travel time
        void load_traffic(std::vector<std::vector<Road*>> &paths);

        /// This function returns the travel time of a given road path
        double get_travel_time(std::vector<Road*> &path);
};

#endif // TRIP_ASSIGNMENT_H







