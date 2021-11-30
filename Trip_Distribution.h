#ifndef TRIP_DISTRIBUTION_H
#define TRIP_DISTRIBUTION_H

#include "buildings/Node.h"
#include "buildings/Residential.h"
#include "buildings/Revenue.h"
#include "buildings/Road.h"
#include "buildings/Health.h"
#include <vector>
using namespace std;


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

/**
 * WARNING
 * This class is designed to perform trip distribution for one set of OD only.
 * Create a seperate object for another set of OD.
 * DO NOT call the trip_distribution_main function more than once.
 */

class Trip_Distribution{
    friend class City;
    friend class Trip_Assignment;
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
        static constexpr float c{1.0f};
        static constexpr int max_path{999};


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
        void set_origin(); //Will be called every object
        void set_work_destination(); //only call for home_work
        void set_health_destination(); //only call for home_health
        void set_factor_and_OD_path(); //call for every object after the prev 2 functions
        void set_OD_matrix(Node::Category category); //call for every object after previous function


        void set_all_residential();
        void set_all_revenue();
        void set_all_health();

        /**
         * Function that returns the number of road that needed to go from start_pt to end_pt, as well as a vector containing
         * all the road pointers that point to the road objects in this path
         * Pass an EMPTY vector<Road*> to this function for it to work
         * Note that for the gravity model to hold, this function will return 1 if start_pt = end_pt
         * Return max_path if it is impossible to go from start_pt to end_pt
         */
        int find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& path); // helper function to return the shortest path
        int find_shortest_path(Road* start_pt, Road* end_pt); /// an overloading function for correct implementation without path

};




#endif // TRIP_DISTRIBUTION_H
