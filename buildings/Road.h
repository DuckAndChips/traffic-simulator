/** 
 * This class is used to handle the road object in the game SimpleCity
*/

#include "Node.h"

class Road:Node{
    private:
        int traffic_flow;   /// the current traffic flow in this road object
        double travel_time; /// the current traffic time when a car pass through this road object
    public:
        /// functions that return whether the neighouring pointers are road object or not
        virtual bool is_east_road() const override;
        virtual bool is_south_road() const override;
        virtual bool is_west_road() const override;
        virtual bool is_north_road() const override;

        /// functions that return the current data member
        int get_traffic_flow() const;
        double get_travel_time() const;
        virtual double get_free_flow_travel_time() const = 0;

        /// functions that calculate the travel time 
        void update_travel_time();
        void set_traffic_flow(int q);
        void traffic_flow_incremental();
        
};