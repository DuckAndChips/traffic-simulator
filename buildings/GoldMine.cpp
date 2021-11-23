#include "GoldMine.h"
#include "../City.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

GoldMine::GoldMine(City &city): Revenue(city) {}

Building::Type GoldMine::get_type() const {
    return Type::GOLD_MINE;
}

int GoldMine::get_cost() const {
    return GoldMine::cost;
}

int GoldMine::get_revenue() const {
    return 2 * (city.get_population() + number_neighboring_population());
}

string GoldMine::get_long_information() const {
    ostringstream out;
    out << GOLD_HEADER << endl;
    out << GOLD_1_1 << get_revenue() << endl;
    out << GOLD_2_1;

    return out.str();
}

string GoldMine::get_short_information() const {
    ostringstream out;
    out << GOLD_HEADER << endl;
    out << GOLD_1_1 << get_revenue();

    return out.str();
}
