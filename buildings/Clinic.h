#ifndef CLINIC_H
#define CLINIC_H

#include "Health.h"
class Clinic: public Health {
public:
    static const int cost{50};

    explicit Clinic(City &city);
    virtual Building::Type get_type() const override;
    virtual int get_cost() const override;

    virtual int get_population_growth_rate_contribution() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // CLINIC_H
