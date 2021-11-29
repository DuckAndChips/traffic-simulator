#include "SilverMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

/* * Construct a Silver Mine
 * 
 * Calls constructor for a Silver Mine object.
 * 
 * @param city   A reference to the current city.
 * @param Revenue   Revenue of the Silver Mine.
 * */
SilverMine::SilverMine(City &city): Revenue(city) {}

/** Get the Node type of the Silver Mine
 * 
 * @return A Node::Type::SILVER_MINE enum value of Node::Type.
 */
Node::Type SilverMine::get_type() const {
    return Type::SILVER_MINE;
}

/** Get the cost of building a Silver Mine
 * 
 * @return The const data member that holds the cost
 */
int SilverMine::get_cost() const {
    return SilverMine::cost;
}

/** Get the attractiveness of the Silver Mine
 * 
 * @return The const data member that holds the attractiveness
 */
int SilverMine::get_attractiveness() const {
    return SilverMine::attractiveness;
}

/** Get the revenue of the Silver Mine
 * 
 * Calculate the revenue by the following:
 * 2 * (city.get_population() + number_neighboring_population())
 * 
 * @return The calculated revenue
 */
int SilverMine::get_revenue() const {
    return city.get_population() + number_neighboring_population();
}

/** Get the revenue per worker of a Silver Mine. 
 * 
 * @return The data member that holds the revenue per worker
 */
int SilverMine::get_revenue_per_worker() const{
    return revenue_per_worker;
}

/** Set the revenue per worker of a Silver Mine. 
 * 
 * @param r The revenue per worker to be set to
 */
void SilverMine::set_revenue_per_worker(int r){
    revenue_per_worker = r;
}

/** Get a long version of a string that contains information about the Silver Mine
 * 
 * Returns a string that contains information including the presence of road 
 * in neighboring cells, and revenue.
 * Calculations of these items are also included in the string.
 * 
 * @return Long version of the string of information about the Silver Mine
 */
string SilverMine::get_long_information() const {
    ostringstream out;
    out << SILVER_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << SILVER_1_1 << get_revenue() << endl;
    out << SILVER_2_1 << endl;
    out << SILVER_3_1 << get_revenue_per_worker() << endl;
    out << SILVER_4_1 << get_working_population();

    return out.str();
}

/** Get a short version of a string that contains information about the Silver Mine
 * 
 * Returns a string that contains information including the presence of road 
 * in neighboring cells, and revenue.
 * Calculations of these items are also included in the string.
 * 
 * @return Short version of the string of information about the Silver Mine
 */
string SilverMine::get_short_information() const {
    ostringstream out;
    out << SILVER_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << SILVER_1_1 << get_revenue() << endl;
    out << SILVER_3_1 << get_revenue_per_worker() << endl;
    out << SILVER_4_1 << get_working_population();

    return out.str();
}
