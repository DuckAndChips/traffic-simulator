#include "Apartment.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/* * Construct a House
 * 
 * Calls constructor for a Apartment object.
 * 
 * @param city A reference to the current city.
 * @param population Population of the apartment
 * */
Apartment::Apartment(City &city, int population) : Residential(city, population) {}

/** Get the Node type of the Apartment
 * 
 * @return A Node::Type::APARTMENT enum value of Node::Type.
 */
Node::Type Apartment::get_type() const {
    return Type::APARTMENT;
}

/** Get the cost of building a Apartment
 * 
 * @return The const data member that holds the cost
 */
int Apartment::get_cost() const {
    return Apartment::cost;
}

/** Get the maximum population of a Apartment
 * 
 * Calculate the maximum population of a apartment by the following:
 * 250 * (1 + number_neighboring_residential_buildings())
 * 
 * @return The calculated maximum population
 */
int Apartment::get_max_population() const {
    return 250 * (1 + number_neighboring_residential_buildings());
}

/** Get a long version of a string that contains information about the Apartment
 * 
 * Returns a string that contains information including the population, maximum
 * population, population growth rate contribution and population growth.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Apartment
 */
string Apartment::get_long_information() const {
    ostringstream out;
    out << APARTMENT_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << APARTMENT_1_1 << get_population() << endl;
    out << APARTMENT_2_1 << get_max_population() << endl;
    out << APARTMENT_3_1 << endl;
    out << APARTMENT_4_1 << get_population_growth_rate_contribution() << endl;
    out << APARTMENT_5_1 << endl;
    out << APARTMENT_6_1 << get_population_growth() << APARTMENT_6_2 << (get_max_population() - get_population()) << APARTMENT_6_3 << endl;
    out << APARTMENT_7_1;
    return out.str();
}

/** Get a short version of a string that contains information about the Apartment
 * 
 * Returns a string that contains information including the population, maximum
 * population, population growth rate contribution and population growth.
 * Calculations of these items are not included in the string.
 * 
 * @return Short version of the string of information about the Apartment
 */
string Apartment::get_short_information() const {
    ostringstream out;
    out << APARTMENT_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << APARTMENT_1_1 << get_population() << endl;
    out << APARTMENT_2_1 << get_max_population() << endl;
    out << APARTMENT_4_1 << get_population_growth_rate_contribution() << endl;
    out << APARTMENT_6_1 << get_population_growth();
    return out.str();
}
