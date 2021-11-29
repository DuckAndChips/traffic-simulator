#ifndef HOUSE_H
#define HOUSE_H

#include "Residential.h"

/**
 * House class
 * 
 * This class holds information and methods for House nodes in the city grid.
 * This class inherits the Residential class, which inherits the Node class.
 * 
 */
class House: public Residential {
public:
    static const int cost{50};

    explicit House(City &city, int population);
    virtual Node::Type get_type() const override;
    virtual int get_cost() const override;

    virtual int get_max_population() const override;

    virtual std::string get_long_information() const override;
    virtual std::string get_short_information() const override;
};
#endif // HOUSE_H
