/** 
 * This class is used to handle the road object in the game SimpleCity
*/

#ifndef ROAD_H
#define ROAD_H

#include "Node.h"

class Road: public Node{
    protected:
        int traffic_flow;   /// the current traffic flow in this road object
        double travel_time; /// the current traffic time when a car pass through this road object
    public:
        /// constructor
        explicit Road(City &city);

        /// get category
        virtual Node::Category get_category() const override;

        /// functions that return the current data member
        int get_traffic_flow() const;
        double get_travel_time() const; 
        virtual double get_max_traffic_flow() const = 0;
        Road* get_neighboring_road(Node::Direction direction) const;

        /// functions that modify traffic flow and hence update travel time by BPR functions
        void set_traffic_flow(int q);
        void traffic_flow_incremental(int flow);

        /// regression parameters
        static constexpr double free_flow_travel_time{10.0};
        static constexpr double alpha{0.15};
        static constexpr double beta{4.0};


        
};

#endif // ROAD_H