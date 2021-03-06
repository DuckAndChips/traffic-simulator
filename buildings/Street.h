#ifndef STREET_H
#define STREET_H

#include "Road.h"
/**
* Street Class
* 
* This class holds information and methods for Street nodes in the city grid. 
* This class inherites the Road class, which inherits the Node class. 
*
**/
class Street: public Road {
    public:
        static const int cost{20};
        static constexpr double max_traffic_flow{65};

        // constructor
        explicit Street(City &city);

        virtual Node::Type get_type() const override;
        virtual int get_cost() const override;
        virtual std::string get_long_information() const override;
        virtual std::string get_short_information() const override;

        virtual double get_max_traffic_flow() const override;
};
#endif // STREET_H

