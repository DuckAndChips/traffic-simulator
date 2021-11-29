#include "Clinic.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/* * Construct a Clinic
 * 
 * Calls constructor for a Clinic object.
 * 
 * @param city A reference to the current city.
 * */
Clinic::Clinic(City &city): Health(city) {}

/** Get the Node type of the Clinic
 * 
 * @return A Node::Type::CLINIC enum value of Node::Type.
 */
Node::Type Clinic::get_type() const {
    return Type::CLINIC;
}

/** Get the cost of building a Clinic
 * 
 * @return The const data member that holds the cost
 */
int Clinic::get_cost() const {
    return Clinic::cost;
}

/** Get the attractiveness of the Clinic
 * 
 * @return The const data member that holds the attractiveness
 */
int Clinic::get_attractiveness() const {
    return Clinic::attractiveness;
}

/** Get the population growth rate contribution of the Clinic
 * 
 * Calculate the population growth rate contribution of the clinic by the following:
 * 60 / (1 + number_neighboring_health_buildings()
 * 
 * @return The calculated population growth rate contribution 
 */
int Clinic::get_population_growth_rate_contribution() const {
    return 60 / (1 + number_neighboring_health_buildings());
}

/** Get a long version of a string that contains information about the Clinic
 * 
 * Returns a string that contains information including the prsence of road in 
 * nearby cells, and population growth rate contribution.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Clinic
 */
string Clinic::get_long_information() const {
    ostringstream out;
    out << CLINIC_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << CLINIC_1_1 << get_population_growth_rate_contribution() << endl;
    out << CLINIC_2_1;

    return out.str();
}

/** Get a short version of a string that contains information about the Clinic
 * 
 * Returns a string that contains information including the prsence of road in 
 * nearby cells, and population growth rate contribution.
 * Calculations of these items are also included in the string.
 * 
 * @return short version of the string of information about the Clinic
 */
string Clinic::get_short_information() const {
    ostringstream out;
    out << CLINIC_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << CLINIC_1_1 << get_population_growth_rate_contribution();

    return out.str();
}
