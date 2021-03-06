#ifndef AVENUE_H
#define AVENUE_H

#include "Road.h"

/* *
* Avenue Class
* 
* This class holds information and methods for Avenue nodes in the city grid. 
* This class inherites the Road class, which inherits the Node class. 
*
* */


class Avenue: public Road {
    public:
        static const int cost{200};
        static constexpr double max_traffic_flow{350};

        // constructor
        explicit Avenue(City &city);

        virtual Node::Type get_type() const override;
        virtual int get_cost() const override;
        virtual std::string get_long_information() const override;
        virtual std::string get_short_information() const override;

        virtual double get_max_traffic_flow() const override;

};
#endif // AVENUE_H


