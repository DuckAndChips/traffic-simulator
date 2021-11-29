#include "SilverMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

SilverMine::SilverMine(City &city): Revenue(city) {}

Node::Type SilverMine::get_type() const {
    return Type::SILVER_MINE;
}

int SilverMine::get_cost() const {
    return SilverMine::cost;
}

int SilverMine::get_attractiveness() const {
    return SilverMine::attractiveness;
}

int SilverMine::get_revenue() const {
    return city.get_population() + number_neighboring_population();
}

int SilverMine::get_revenue_per_worker() const{
    return revenue_per_worker;
}

void SilverMine::set_revenue_per_worker(int r){
    revenue_per_worker = r;
}

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
