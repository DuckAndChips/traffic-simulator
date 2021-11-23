#include "Clinic.h"
#include "BuildingInformationFormatString.h"

#include <sstream>

using namespace std;

Clinic::Clinic(City &city): Health(city) {}

Building::Type Clinic::get_type() const {
    return Type::CLINIC;
}

int Clinic::get_cost() const {
    return Clinic::cost;
}

int Clinic::get_population_growth_rate_contribution() const {
    return 60 / (1 + number_neighboring_health_buildings());
}

string Clinic::get_long_information() const {
    ostringstream out;
    out << CLINIC_HEADER << endl;
    out << CLINIC_1_1 << get_population_growth_rate_contribution() << endl;
    out << CLINIC_2_1;

    return out.str();
}

string Clinic::get_short_information() const {
    ostringstream out;
    out << CLINIC_HEADER << endl;
    out << CLINIC_1_1 << get_population_growth_rate_contribution();

    return out.str();
}
