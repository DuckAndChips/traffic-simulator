#include "SilverMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

SilverMine::SilverMine(City &city): Revenue(city) {}

Building::Type SilverMine::get_type() const {
    return Type::SILVER_MINE;
}

int SilverMine::get_cost() const {
    return SilverMine::cost;
}

int SilverMine::get_revenue() const {
    return city.get_population() + number_neighboring_population();
}

string SilverMine::get_long_information() const {
    ostringstream out;
    out << SILVER_HEADER << endl;
    out << SILVER_1_1 << get_revenue() << endl;
    out << SILVER_2_1;

    return out.str();
}

string SilverMine::get_short_information() const {
    ostringstream out;
    out << SILVER_HEADER << endl;
    out << SILVER_1_1 << get_revenue();

    return out.str();
}
