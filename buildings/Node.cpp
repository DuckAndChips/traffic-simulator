#include "Node.h"
#include "../City.h"


Node::Node(City &city): city(city) {
    for(int i = 0; i < 4; i++)
        neighboring_nodes[i] = nullptr;
}

int Node::get_revenue() const {
    return 0;
}

int Node::get_population() const {
    return 0;
}

int Node::get_max_population() const {
    return 0;
}

int Node::get_population_growth() const {
    return 0;
}

int Node::get_population_growth_rate_contribution() const {
    return 0;
}

int Node::get_work_trips(){
    return 0;
}

int Node::get_health_trips(){
    return 0;
}

int Node::get_attractiveness() const{
    return 0;
}

void Node::increase_population(int population){}

Node* Node::get_neighboring_node(Node::Direction direction) const{
    return neighboring_nodes[static_cast<int>(direction)];
}
void Node::set_neighboring_node(Node::Direction direction, Node* n){
    neighboring_nodes[static_cast<int>(direction)] = n;
}

bool Node::is_neighbor_empty(Node::Direction direction){
    if(neighboring_nodes[static_cast<int>(direction)] == nullptr){
        return true;
    }
    else{
        return false;
    }
}

bool Node::is_neighbor_road(Node::Direction direction) const{
    Node* check = neighboring_nodes[static_cast<int>(direction)];
    if(check == nullptr){
        return false;
    }
    else if(check->get_category() == Node::Category::ROAD){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Warning:
 * The following implementations are for the original PA3 and PA4 and should be modified after implementation of the new game algorithm 
 *

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
*/

// Dummy Implementations
int Node::number_neighboring_residential_buildings() const{
    return 0;
}

int Node::number_neighboring_health_buildings() const{
    return 0;
}

int Node::number_neighboring_gold_mines() const{
    return 0;
}

int Node::number_neighboring_population() const{
    return 0;
}




