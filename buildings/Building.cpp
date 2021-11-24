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

int Building::get_work_trips(){
    return 0;
}

int Building::get_health_trips(){
    return 0;
}


void Building::increase_population(int population){}
void Building::update_work_trips(){}
void Building::update_health__trips(){}

Node* Building::get_neighboring_building(Building::Direction direction) const{
    return neighboring_buildings[static_cast<int>(direction)];
}
void Building::set_neighboring_building(Building::Direction direction, Building* n){
    neighboring_buildings[static_cast<int>(direction)] = n;
}
bool Building::is_neighbor_empty(Building::Direction direction) const{
    if(neighboring_buildings[static_cast<int>(direction)] == nullptr){
        return true;
    }
    else{
        return false;
    }
}
bool Building::is_neighbor_road(Building::Direction direction) const{
    Building* check = neighboring_buildings[static_cast<int>(direction)];
    if(check == nullptr){
        return false;
    }
    else if(check->get_category() == Building::Category::ROAD){
        return true;
    }
    else{
        return false;
    }
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
