#ifndef STREET_H
#define STREET_H

#include "Road.h"
class Street: public Road {
    public:
        static const int cost{50};
        static const int free_flow_travel_time{10};

        // constructor
        explicit Street(City &city);

        virtual Building::Type get_type() const override;
        virtual int get_cost() const override;
        virtual std::string get_long_information() const override;
        virtual std::string get_short_information() const override;

        virtual double get_free_flow_travel_time() const override;
};
#endif // STREET_H