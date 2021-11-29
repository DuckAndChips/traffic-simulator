#include "House.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/** Construct a House
 * 
 * Calls constructor for a Residential object.
 * 
 * @param city A reference to the current city.
 * @param population Population of the House
 */
House::House(City &city, int population) : Residential(city, population) {}

/** Get the Node type of the House
 * 
 * @return A Node::Type::HOUSE enum value of Node::Type.
 */
Node::Type House::get_type() const {
    return Type::HOUSE;
}

/** Get the cost of building a House
 * 
 * @return The const data member that holds the cost
 */
int House::get_cost() const {
    return House::cost;
}

/** Get the maximum population of a House
 * 
 * Calculate the maximum population of a house by the following:
 * 50 * (1 + number of neighboring residential buildings)
 * 
 * @return The calculated maximum population
 */
int House::get_max_population() const {
    return 50 * (1 + number_neighboring_residential_buildings());
}

/** Get a long version of a string that contains information about the House
 * 
 * Returns a string that contains information including the population, maximum
 * population, population growth rate contribution and population growth.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the house
 */
std::string House::get_long_information() const {
    ostringstream out;
    out << HOUSE_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << HOUSE_1_1 << get_population() << endl;
    out << HOUSE_2_1 << get_max_population() << endl;
    out << HOUSE_3_1 << endl;
    out << HOUSE_4_1 << get_population_growth_rate_contribution() << endl;
    out << HOUSE_5_1 << endl;
    out << HOUSE_6_1 << get_population_growth() << HOUSE_6_2 << (get_max_population() - get_population()) << HOUSE_6_3 << endl;
    out << HOUSE_7_1;
    return out.str();
}

/** Get a short version of a string that contains information about the House
 * 
 * Returns a string that contains information including the population, maximum
 * population, population growth rate contribution and population growth.
 * Calculations of these items are not included in the string.
 * 
 * @return Short version of the string of information about the house
 */
string House::get_short_information() const {
    ostringstream out;
    out << HOUSE_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << HOUSE_1_1 << get_population() << endl;
    out << HOUSE_2_1 << get_max_population() << endl;
    out << HOUSE_4_1 << get_population_growth_rate_contribution() << endl;
    out << HOUSE_6_1 << get_population_growth();
    return out.str();
}
