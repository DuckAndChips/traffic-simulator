#include "Hospital.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

Hospital::Hospital(City &city): Health(city) {}

Building::Type Hospital::get_type() const {
    return Type::HOSPITAL;
}

int Hospital::get_cost() const {
    return Hospital::cost;
}

int Hospital::get_population_growth_rate_contribution() const {
    return 360 / (1 + number_neighboring_health_buildings());
}

string Hospital::get_long_information() const {
    ostringstream out;
    out << HOSPITAL_HEADER << endl;
    out << HOSPITAL_1_1 << get_population_growth_rate_contribution() << endl;
    out << HOSPITAL_2_1;

    return out.str();
}

string Hospital::get_short_information() const {
    ostringstream out;
    out << HOSPITAL_HEADER << endl;
    out << HOSPITAL_1_1 << get_population_growth_rate_contribution();

    return out.str();
}
