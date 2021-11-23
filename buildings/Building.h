/**
* Do not modify
*/

#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include "../Node.h"

class City;

class Building: public Node {
public:
    enum class Type {
        CLINIC = 1,
        HOSPITAL = 2,
        SILVER_MINE = 3,
        GOLD_MINE = 4,
        HOUSE = 5,
        APARTMENT = 6
        
    };

    enum class Category {
        HEALTH,
        REVENUE,
        RESIDENTIAL
    };

    virtual ~Building() = default;

    virtual Building::Type get_type() const = 0;

    virtual Building::Category get_category() const = 0;

//     virtual int get_cost() const = 0;

//     virtual std::string get_long_information() const = 0;

//     virtual std::string get_short_information() const = 0;

    virtual int get_revenue() const;
    virtual int get_population() const;
    virtual int get_max_population() const;
    virtual int get_population_growth() const;
    virtual int get_population_growth_rate_contribution() const;
    virtual void increase_population(int population);
    
    virtual int update_work_trips();
    virtual int update_health__trips();

//     bool register_neighboring_building(Building *building);
//     bool deregister_neighboring_building(Building *building);
    int number_neighboring_residential_buildings() const;
    int number_neighboring_health_buildings() const;
    int number_neighboring_gold_mines() const;
    int number_neighboring_population() const;

protected:
    explicit Building(City &city);

    City &city;

private:
//     Building *neighboring_buildings[4]{};
};
#endif // BUILDING_H
