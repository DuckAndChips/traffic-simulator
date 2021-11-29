/** 
 * This class is used to handle the road object in the game SimpleCity
*/

#ifndef ROAD_H
#define ROAD_H

#include "Node.h"

/**
 * Revenue class
 * 
 * This class holds information and methods for Road nodes in the city grid.
 * This class inherits the Node class.
 * 
 */
class Road: public Node{
    protected:
        int traffic_flow;   /// The current traffic flow in this road object
        double travel_time; /// The current traffic time when a car pass through this road object
    public:
        /// Constructor
        explicit Road(City &city);

        /// Get category
        virtual Node::Category get_category() const override;

        /// Functions that return the current data member
        int get_traffic_flow() const;
        double get_travel_time() const; 
        virtual double get_max_traffic_flow() const = 0;
        Road* get_neighboring_road(Node::Direction direction) const;

        /// Functions that modify traffic flow and hence update travel time by BPR functions
        void set_traffic_flow(int q);
        void traffic_flow_incremental(int flow);

        /// Regression parameters
        static constexpr double free_flow_travel_time{10.0};
        static constexpr double alpha{0.15};
        static constexpr double beta{4.0};


        
};

#endif // ROAD_H