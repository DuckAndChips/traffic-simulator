#include "Road.h"
#include "../City.h"
#include <algorithm>
#include <cmath> 

Road::Road(City &city):Node(city),traffic_flow(0),travel_time(free_flow_travel_time){}

Node::Category Road::get_category() const {
    return Category::ROAD;
}

int Road::get_traffic_flow() const{
    return traffic_flow;
}

double Road::get_travel_time() const{
    return travel_time;
}

Road* Road::get_neighboring_road(Node::Direction direction) const{
    if(is_neighbor_road(direction)){
        return dynamic_cast<Road*>(get_neighboring_node(direction));
    }
}
        
void Road::set_traffic_flow(int q){
    traffic_flow = q;
    travel_time = free_flow_travel_time * (1+alpha*pow((traffic_flow/get_max_traffic_flow()),beta));
}

void Road::traffic_flow_incremental(int flow){
    traffic_flow += flow;
    travel_time = free_flow_travel_time * (1+alpha*pow((traffic_flow/get_max_traffic_flow()),beta));
}