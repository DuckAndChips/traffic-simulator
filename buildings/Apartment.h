#ifndef APARTMENT_H
#define APARTMENT_H

#include "Residential.h"

/* *
* Apartment Class
* 
* This class holds information and methods for Apartment nodes in the city grid. 
* This class inherites the Residential class, which inherits the Node class. 
*
* */


class Apartment: public Residential {
public:
    static const int cost{300};

    explicit Apartment(City &city, int population);

    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;
    virtual int get_max_population() const override;
    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // APARTMENT_H
