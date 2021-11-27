#ifndef TRIP_DISTRIBUTION_H
#define TRIP_DISTRIBUTION_H

#include <vector>
#include <algorithm>
#include "Buildings/Road.h"
#include "Buildings/Residential.h"

class Trip_distribution{
    private:
        std::vector<Residential*> all_residential;


        std::vector<Road*> origin;
        City& city;
    public:
        explicit Trip_distribution(City& city);
        void set_all_residential();

};



#endif //TRIP_DISTRIBUTION_H