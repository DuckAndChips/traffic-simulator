#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Health.h"

/* *
* Hospital Class
* 
* This class holds information and methods for Hospital nodes in the city grid. 
* This class inherites the Health class, which inherits the Node class. 
*
* */


class Hospital: public Health {
public:
    static const int cost{500};
    static const int attractiveness{5};

    explicit Hospital(City &city);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_attractiveness() const override;

    virtual int get_population_growth_rate_contribution() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // HOSPITAL_H
