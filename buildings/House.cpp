#include "House.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

House::House(City &city, int population) : Residential(city, population) {}

Building::Type House::get_type() const {
    return Type::HOUSE;
}

int House::get_cost() const {
    return House::cost;
}

int House::get_max_population() const {
    return 50 * (1 + number_neighboring_residential_buildings());
}

std::string House::get_long_information() const {
    ostringstream out;
    out << HOUSE_HEADER << endl;
    out << HOUSE_1_1 << get_population() << endl;
    out << HOUSE_2_1 << get_max_population() << endl;
    out << HOUSE_3_1 << endl;
    out << HOUSE_4_1 << get_population_growth_rate_contribution() << endl;
    out << HOUSE_5_1 << endl;
    out << HOUSE_6_1 << get_population_growth() << HOUSE_6_2 << (get_max_population() - get_population()) << HOUSE_6_3 << endl;
    out << HOUSE_7_1;
    return out.str();
}

string House::get_short_information() const {
    ostringstream out;
    out << HOUSE_HEADER << endl;
    out << HOUSE_1_1 << get_population() << endl;
    out << HOUSE_2_1 << get_max_population() << endl;
    out << HOUSE_4_1 << get_population_growth_rate_contribution() << endl;
    out << HOUSE_6_1 << get_population_growth();
    return out.str();
}
