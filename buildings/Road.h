/** 
 * This class is used to handle the road object in the game SimpleCity
*/

#include "Building.h"

class Road: public Node{
    private:
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
        virtual double get_free_flow_travel_time() const = 0;
        Road* get_neighboring_road(Node::Direction direction) const;
        virtual bool is_neighbor_road(Node::Direction direcion) const;

        /// functions that calculate the travel time 
        void update_travel_time();
        void set_traffic_flow(int q);
        void traffic_flow_incremental(int flow);


        
};