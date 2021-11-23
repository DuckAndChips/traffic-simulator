#include "Apartment.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

Apartment::Apartment(City &city, int population) : Residential(city, population) {}

Building::Type Apartment::get_type() const {
    return Type::APARTMENT;
}

int Apartment::get_cost() const {
    return Apartment::cost;
}

int Apartment::get_max_population() const {
    return 250 * (1 + number_neighboring_residential_buildings());
}

string Apartment::get_long_information() const {
    ostringstream out;
    out << APARTMENT_HEADER << endl;
    out << APARTMENT_1_1 << get_population() << endl;
    out << APARTMENT_2_1 << get_max_population() << endl;
    out << APARTMENT_3_1 << endl;
    out << APARTMENT_4_1 << get_population_growth_rate_contribution() << endl;
    out << APARTMENT_5_1 << endl;
    out << APARTMENT_6_1 << get_population_growth() << APARTMENT_6_2 << (get_max_population() - get_population()) << APARTMENT_6_3 << endl;
    out << APARTMENT_7_1;
    return out.str();
}

string Apartment::get_short_information() const {
    ostringstream out;
    out << APARTMENT_HEADER << endl;
    out << APARTMENT_1_1 << get_population() << endl;
    out << APARTMENT_2_1 << get_max_population() << endl;
    out << APARTMENT_4_1 << get_population_growth_rate_contribution() << endl;
    out << APARTMENT_6_1 << get_population_growth();
    return out.str();
}
