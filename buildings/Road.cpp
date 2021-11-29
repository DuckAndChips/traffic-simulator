#include "Road.h"
#include "../City.h"
#include <algorithm>
#include <cmath> 

/** Construct a Road building. 
 * 
 * Virtual function. 
 * This constructor can only be called by its childs. 
 * Constructs a Node with the current city and sets traffic flow and travel time to 
 * 0 and its free flow travel time respectively.
 * 
 * @param city A reference to the current city.
 */
Road::Road(City &city):Node(city),traffic_flow(0),travel_time(free_flow_travel_time){}

/** Get the category of a Residential building. 
 * 
 * @return A Node::Category::ROAD enum value of Node::Category.
 * */
Node::Category Road::get_category() const {
    return Category::ROAD;
}

/** Get the traffic flow of a Road. 
 * 
 * @return Traffic flow of the Road.
 * */
int Road::get_traffic_flow() const{
    return traffic_flow;
}

/** Get the travel time of a Road. 
 * 
 * @return Travel time of the Road. (double)
 * */
double Road::get_travel_time() const{
    return travel_time;
}

/** Get neighboring Road. 
 * 
 * Returns a pointer to its neighboring Roade in the direction provided. 
 * 
 * @param direction Direction of the neighboring Road to be retrieved. 
 * @return Pointer to the neighboring Road in the direction provided. 
 */
Road* Road::get_neighboring_road(Node::Direction direction) const{
    if(is_neighbor_road(direction)){
        return dynamic_cast<Road*>(get_neighboring_node(direction));
    }
}

/** Set traffic flow. 
 * 
 * Sets traffic flow of the road as provided. 
 * 
 * @param q Traffic flow to be set to
 */
void Road::set_traffic_flow(int q){
    traffic_flow = q;
    travel_time = free_flow_travel_time * (1+alpha*pow((traffic_flow/get_max_traffic_flow()),beta));
}

/** Incremenet traffic flow. 
 * 
 * Increments traffic flow of the road as provided. 
 * 
 * @param flow Increment of traffic flow
 */
void Road::traffic_flow_incremental(int flow){
    traffic_flow += flow;
    travel_time = free_flow_travel_time * (1+alpha*pow((traffic_flow/get_max_traffic_flow()),beta));
}