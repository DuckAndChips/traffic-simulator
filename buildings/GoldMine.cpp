#include "GoldMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/* * Construct a Gold Mine
 * 
 * Calls constructor for a Gold Mine object.
 * 
 * @param city   A reference to the current city.
 * @param Revenue   Revenue of the Gold Mine.
 * */
GoldMine::GoldMine(City &city): Revenue(city) {}

/** Get the Node type of the Gold Mine
 * 
 * @return A Node::Type::GOLD_MINE enum value of Node::Type.
 */
Node::Type GoldMine::get_type() const {
    return Type::GOLD_MINE;
}

/** Get the cost of building a Gold Mine
 * 
 * @return The const data member that holds the cost
 */
int GoldMine::get_cost() const {
    return GoldMine::cost;
}

/** Get the attractiveness of the Gold Mine
 * 
 * @return The const data member that holds the attractiveness
 */
int GoldMine::get_attractiveness() const {
    return GoldMine::attractiveness;
}

/** Get the revenue of the Gold Mine
 * 
 * Calculate the revenue by the following:
 * 2 * (city.get_population() + number_neighboring_population())
 * 
 * @return The calculated revenue
 */
int GoldMine::get_revenue() const {
    return 2 * (city.get_population() + number_neighboring_population());
}

/** Get a long version of a string that contains information about the Gold Mine
 * 
 * Returns a string that contains information including the presence of road 
 * in neighboring cells, and revenue.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Gold Mine
 */
string GoldMine::get_long_information() const {
    ostringstream out;
    out << GOLD_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << GOLD_1_1 << get_revenue() << endl;
    out << GOLD_2_1;

    return out.str();
}

/** Get a short version of a string that contains information about the Gold Mine
 * 
 * Returns a string that contains information including the presence of road 
 * in neighboring cells, and revenue.
 * Calculations of these items are also included in the string.
 * 
 * @return Short version of the string of information about the Gold Mine
 */
string GoldMine::get_short_information() const {
    ostringstream out;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << GOLD_HEADER << endl;
    out << GOLD_1_1 << get_revenue();

    return out.str();
}
