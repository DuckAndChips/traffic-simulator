#ifndef CLINIC_H
#define CLINIC_H

#include "Health.h"

/* *
* Clinic Class
* 
* This class holds information and methods for Clinic nodes in the city grid. 
* This class inherites the Health class, which inherits the Node class. 
*
* */


class Clinic: public Health {
public:
    static const int cost{50};
    static const int attractiveness{2};

    explicit Clinic(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;

    virtual int get_population_growth_rate_contribution() const override;
    virtual int get_attractiveness() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // CLINIC_H
