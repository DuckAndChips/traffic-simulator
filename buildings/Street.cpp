#include "Street.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/** Construct a Street
 * 
 * Calls constructor for a Street object.
 * 
 * @param city A reference to the current city.
**/
Street::Street(City &city): Road(city) {}

/** Get the Node type of the Street
 * 
 * @return A Node::Type::Street enum value of Node::Type.
 */
Node::Type Street::get_type() const{
    return Node::Type::STREET;
}

/** Get the cost of building a Street
 * 
 * @return The const data member that holds the cost
 */
int Street::get_cost() const{
    return cost;
}

/** Get a long version of a string that contains information about the Street
 * 
 * Returns a string that contains information including the maximum traffic
 * flow, traffic flow, and travel time. 
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Street
 */
std::string Street::get_long_information() const{
    ostringstream out;
    out << STREET_HEADER << endl;
    out << ROAD_1_1 << get_max_traffic_flow() << endl;
    out << ROAD_2_1 << get_traffic_flow() << ROAD_2_2 << endl;
    out << ROAD_3_1 << get_travel_time() << endl;
    out << ROAD_4_1;

    return out.str();
}

/** Get a short version of a string that contains information about the Street
 * 
 * Returns a string that contains information including the maximum traffic
 * flow, traffic flow, and travel time. 
 * Calculations of these items are also included in the string.
 * 
 * @return Short version of the string of information about the Street
 */
std::string Street::get_short_information() const{
    ostringstream out;
    out << STREET_HEADER << endl;
    out << ROAD_1_1 << get_max_traffic_flow() << endl;
    out << ROAD_2_1 << get_traffic_flow() << ROAD_2_2 << endl;
    out << ROAD_3_1 << get_travel_time() << endl;

    return out.str();
}

/** Get the maximum traffic flow of the Street
 * 
 * @return The const data member that holds the maximum traffic flow
 */
double Street::get_max_traffic_flow() const{
    return max_traffic_flow;
}
