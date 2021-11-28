#include "buildings/Clinic.h"
#include "buildings/Hospital.h"
#include "buildings/SilverMine.h"
#include "buildings/GoldMine.h"
#include "buildings/House.h"
#include "buildings/Apartment.h"
#include "Node.h"
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
 * Step 2: Trip Distrubution (Decision – to where, what destination?)
 * Step 3: Modal Split (Decision – how, what mode?)
 * Step 4: Traffic Assignment (Decision – how, which route?)
 * 
 * In this project, these four steps are implemented by the following parts of our code respectively:
 * Step 1: member functions of Residential class
 * Step 2: Trip_Distrubution class in this file
 * Step 3: This step is skiped since we do not consider multiple travel modes in the city (e.g. MTR/bus)
 * Step 4: Trip_Assignment class in this file
 */

/**
 * Trip_Distribution is a class that perform the second step of the sequential demand focasting model.
 * 
 * Gravity model is used as the trip distribution model in our project.
 * Q(I,J) = k*P(I)*A(J)/W(I,J)^c
 * where    Q(I,J) is the traffic flow from origin I to destination J
 *          P(I) is the number of trip production at origin I 
 *          A(J) is the attractiveness of destination J
 *          W(I,J) is a measure of the predetermined travel time/ distance between I and J
 *          c   is a parameter obtained from calibration of real life data. Here we set c = 1 as a dummy variable
 *              for the SimpleCity game
 *          k   is a parameter that can be eliminated by applying the trip-production balance constraints:
 *                  P(I) = sum of Q(I,J) over all J
 * 
 * An OD matrix (origin-destination matrix) is defined as a matrix storing Q(I,J) for all I,J.
 * In our code, a 2D vector of int is used to be the OD matrix.
 * To provide more flexibility for the user, we also define a 2D vector of vector<Road*> to stores the shortest
 * path from origin to destination.
 * 
 * We define City as the friend class of this class for City to get the results of Trip Distribution.
 */

/*** Note by Jacky: I have change some of the implementation of the code so the following discription is inaccurate now
Trip_Distribution is an object used to generate 3 vectors, which include origin matrix, destination matrix, and OD number of trips 2d vector. 
First, 3 vectors containing residential, revenue, and health buildings are generated. Then, according to the category of trips, including
home-work trips and home-health trips, it will call corresponding set origin and set destination function to set origin and destination vector. 
After that, travel time matrix and number of trips matrix is generated one after he other. 
***/

/**
 * WARNING
 * This class is designed to perform trip distribution for one set of OD only.
 * Create a seperate object for another set of OD.
 * DO NOT call the trip_distribution_main function more than once.
 */

class Trip_Distribution{
    friend class City;
    private:
        std::vector<Residential*> & all_residential_building;
        std::vector<Revenue*> & all_revenue_building;
        std::vector<Health*> & all_health_building;

        std::vector<Node*> all_destination_building;
        std::vector<Road*> origin; /// store nullptr if the residential building does not have road nearby
        std::vector<Road*> destination; /// store nullptr if the revenue/health building does not have road nearby

        std::vector<vector<float>> factors; /// store 0 if their is no path if there is no possible path from the origin to destination
                                            /// This is a temporatory 2D vector used for the intermediate steps of the 
        std::vector<vector<vector<Road*>>> OD_path; /// store EMPTY vector<Road*> if there is no possible path from the origin to destination
        std::vector<vector<int>> OD_matrix; /// store 0 if their is no path if there is no possible path from the origin to destination
        City& city;
        

    public:
        /// Regression parameter used in gravity model
        static const float c{1.0f};
        static const int max_path{999};


        /// constructor
        explicit Trip_Distribution(City &city, std::vector<Residential*> & residential_buildings,
        std::vector<Revenue*> & revenue_buildings, std::vector<Health*> & health_buildings);

        /// Main function used for trip distrubution
        /// return true only if this function is correctly implemented
        /// return false if there is no origin/destination for trip distribution, or the code is wrongly implmented
        /// Call this function ONCE only for each object
        bool trip_distribution_main(Node::Category category);

        /// Remaining are some helper functions that needed for trip assignment 

        /**
         * These three functions set the origin and destination data member of this class.
         * Warning: nullptr will be set if there is no road near the residential/commercial/health buildings
         */ 
        void set_origin();
        void set_work_destination();
        void set_health_destination();
        void set_factor_and_OD_path();
        void set_OD_matrix(Node::Category category);

        /** 
         * Function that returns the number of road that needed to go from start_pt to end_pt, as well as a vector containing
         * all the road pointers that point to the road objects in this path
         * Pass an EMPTY vector<Road*> to this function for it to work
         * Note that for the gravity model to hold, this function will return 1 if start_pt = end_pt
         * Return max_path if it is impossible to go from start_pt to end_pt
         */
        int find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& path);
        int find_shortest_path(Road* start_pt, Road* end_pt); /// an overloading function for correct implementation without path

};

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
        std::vector<std::vector<float>> OD_travel_time;
        City &city;
        friend class City;
    public:

        /// The incremental portion that used in trip assignment
        static const int incremental_amount{1};        

        /// constructors and function that setup data members
        explicit Trip_Assignment(std::vector<Road*>& origin, std::vector<Road*>& destination, std::vector<std::vector<int>>& OD_Matrix);
        void set_Traffic_Model(std::vector<Road*> origin, std::vector<Road*> destination, std::vector<std::vector<int>> OD_Matrix);

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








