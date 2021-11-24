/**
* Do not modify
*/

#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include "Node.h"

class City;

class Building: public Node {
public:
    enum class Type {
        CLINIC = 1,
        HOSPITAL = 2,
        SILVER_MINE = 3,
        GOLD_MINE = 4,
        HOUSE = 5,
        APARTMENT = 6,
        STREET = 7,
        AVENUE = 8        
    };

    enum class Category {
        HEALTH,
        REVENUE,
        RESIDENTIAL,
        ROAD
    };

    enum class Direction{
            NORTH,
            EAST,
            SOUTH,
            WEST
        };

    virtual ~Building() = default;

    // get building information
    virtual Building::Type get_type() const = 0;
    virtual Building::Category get_category() const = 0;
    virtual int get_cost() const = 0;
    virtual std::string get_long_information() const = 0;
    virtual std::string get_short_information() const = 0;

    virtual int get_revenue() const;
    virtual int get_population() const;
    virtual int get_max_population() const;
    virtual int get_population_growth() const;
    virtual int get_population_growth_rate_contribution() const;

    virtual int get_work_trips();
    virtual int get_health_trips();

    // do work
    virtual void increase_population(int population);
    virtual void update_work_trips();
    virtual void update_health__trips();

    // neighboring building
    Node* get_neighboring_building(Direction direction) const;
    void set_neighboring_building(Direction direcion, Building* n);
    bool is_neighbor_empty(Direction direction) const;

    virtual bool is_neighbor_road(Direction direcion) const;
    int number_neighboring_residential_buildings() const;
    int number_neighboring_health_buildings() const;
    int number_neighboring_gold_mines() const;
    int number_neighboring_population() const;

protected:
    explicit Building(City &city);

    City &city;

private:
    Building *neighboring_buildings[4]{};
};
#endif // BUILDING_H
