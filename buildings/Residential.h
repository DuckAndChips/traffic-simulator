#ifndef RESIDENTIAL_H
#define RESIDENTIAL_H

#include "Building.h"
class Residential: public Building {
public:
    virtual Building::Category get_category() const override;

    virtual int get_population() const override;
    virtual int get_population_growth() const override;
    virtual int get_population_growth_rate_contribution() const override;
    virtual void increase_population(int population) override;

protected:
    int population;
    explicit Residential(City &city, int population);
};
#endif // RESIDENTIAL_H
