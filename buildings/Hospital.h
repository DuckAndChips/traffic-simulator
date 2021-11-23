#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Health.h"
class Hospital: public Health {
public:
    static const int cost{500};

    explicit Hospital(City &city);
    virtual Building::Type get_type() const override;
    virtual int get_cost() const override;

    virtual int get_population_growth_rate_contribution() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // HOSPITAL_H
