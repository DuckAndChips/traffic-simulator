#include "GoldMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

GoldMine::GoldMine(City &city): Revenue(city) {}

Node::Type GoldMine::get_type() const {
    return Type::GOLD_MINE;
}

int GoldMine::get_cost() const {
    return GoldMine::cost;
}

int GoldMine::get_attractiveness() const {
    return GoldMine::attractiveness;
}

int GoldMine::get_revenue() const {
    return 2 * (city.get_population() + number_neighboring_population());
}

string GoldMine::get_long_information() const {
    ostringstream out;
    out << GOLD_HEADER << endl;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << GOLD_1_1 << get_revenue() << endl;
    out << GOLD_2_1 << endl;
    out << GOLD_3_1 << get_revenue_per_worker() << endl;
    out << GOLD_4_1 << get_working_population();

    return out.str();
}

string GoldMine::get_short_information() const {
    ostringstream out;
    if(!is_neighbor_road(Node::Direction::EAST) && !is_neighbor_road(Node::Direction::NORTH) && 
       !is_neighbor_road(Node::Direction::SOUTH) && !is_neighbor_road(Node::Direction::WEST)) {
           out << NO_ROAD_WARNING << endl;
    }
    out << GOLD_HEADER << endl;
    out << GOLD_1_1 << get_revenue() << endl;
    out << GOLD_3_1 << get_revenue_per_worker() << endl;
    out << GOLD_4_1 << get_working_population();

    return out.str();
}
