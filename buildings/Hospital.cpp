#include "Hospital.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/* * Construct a Hospital
 * 
 * Calls constructor for a Hospital object.
 * 
 * @param city A reference to the current city.
 * */
Hospital::Hospital(City &city): Health(city) {}

/** Get the Node type of the Hospital
 * 
 * @return A Node::Type::HOSPITAL enum value of Node::Type.
 */
Node::Type Hospital::get_type() const {
    return Type::HOSPITAL;
}

/** Get the cost of building a Hospital
 * 
 * @return The const data member that holds the cost
 */
int Hospital::get_cost() const {
    return Hospital::cost;
}

/** Get the attractiveness of the Hospital
 * 
 * @return The const data member that holds the attractiveness
 */
int Hospital::get_attractiveness() const {
    return Hospital::attractiveness;
}

/** Get the population growth rate contribution of the Hospital
 * 
 * Calculate the population growth rate contribution of the hospital by the following:
 * 360 / (1 + number_neighboring_health_buildings())
 * 
 * @return The calculated population growth rate contribution 
 */
int Hospital::get_population_growth_rate_contribution() const {
    return 360 / (1 + number_neighboring_health_buildings());
}

/** Get a long version of a string that contains information about the Hospital
 * 
 * Returns a string that contains information including the prsence of road in 
 * nearby cells, and population growth rate contribution.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Hospital
 */
string Hospital::get_long_information() const {
    ostringstream out;
    out << HOSPITAL_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << HOSPITAL_1_1 << get_population_growth_rate_contribution() << endl;
    out << HOSPITAL_2_1;

    return out.str();
}

/** Get a short version of a string that contains information about the Hospital
 * 
 * Returns a string that contains information including the prsence of road in 
 * nearby cells, and population growth rate contribution.
 * Calculations of these items are also included in the string.
 * 
 * @return short version of the string of information about the Hospital
 */
string Hospital::get_short_information() const {
    ostringstream out;
    out << HOSPITAL_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << HOSPITAL_1_1 << get_population_growth_rate_contribution();

    return out.str();
}
