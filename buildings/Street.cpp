#include "Street.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

Street::Street(City &city): Road(city) {}

Node::Type Street::get_type() const{
    return Node::Type::STREET;
}

int Street::get_cost() const{
    return cost;
}

std::string Street::get_long_information() const{
    ostringstream out;
    out << STREET_HEADER << endl;
    out << ROAD_1_1 << get_max_traffic_flow() << endl;
    out << ROAD_2_1 << get_traffic_flow() << ROAD_2_2 << endl;
    out << ROAD_3_1 << get_travel_time() << endl;
    out << ROAD_4_1;

    return out.str();
}

std::string Street::get_short_information() const{
    ostringstream out;
    out << STREET_HEADER << endl;
    out << ROAD_1_1 << get_max_traffic_flow() << endl;
    out << ROAD_2_1 << get_traffic_flow() << ROAD_2_2 << endl;
    out << ROAD_3_1 << get_travel_time() << endl;

    return out.str();
}

double Street::get_max_traffic_flow() const{
    return max_traffic_flow;
}
