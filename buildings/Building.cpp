#include "Building.h"
#include "../City.h"

Building::Building(City &city): city(city) {}

int Building::get_revenue() const {
    return 0;
}

int Building::get_population() const {
    return 0;
}

int Building::get_max_population() const {
    return 0;
}

int Building::get_population_growth() const {
    return 0;
}

int Building::get_population_growth_rate_contribution() const {
    return 0;
}

void Building::increase_population(int population) {

}

bool Building::register_neighboring_building(Building *building) {
    for (int i = 0; i < 4; ++i) {
        if (neighboring_buildings[i] == nullptr) {
            neighboring_buildings[i] = building;
            return true;
        }
    }
    return false;
}

bool Building::deregister_neighboring_building(Building *building) {
    for (int i = 0; i < 4; ++i) {
        if (neighboring_buildings[i] == building) {
            neighboring_buildings[i] = nullptr;
            return true;
        }
    }
    return false;
}

int Building::number_neighboring_health_buildings() const {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        Building *building = neighboring_buildings[i];
        if (building && building->get_category() == Building::Category::HEALTH)
            ++count;
    }

    return count;
}

int Building::number_neighboring_residential_buildings() const {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        Building *building = neighboring_buildings[i];
        if (building && building->get_category() == Building::Category::RESIDENTIAL)
            ++count;
    }

    return count;
}

int Building::number_neighboring_population() const {
    int population = 0;
    for (int i = 0; i < 4; ++i) {
        Building *building = neighboring_buildings[i];
        if (building)
            population += building->get_population();
    }

    return population;
}

int Building::number_neighboring_gold_mines() const {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        Building *building = neighboring_buildings[i];
        if (building && building->get_type() == Building::Type::GOLD_MINE)
            ++count;
    }

    return count;
}
