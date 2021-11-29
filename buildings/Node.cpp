#include "Node.h"
#include "../City.h"

/** Construct a Node. 
 * 
 * Virtual function. 
 * This constructor can only be called by its childs. 
 * Sets its data member city as the provided city and sets all neighboring. 
 * nodes to null pointers.
 * 
 * @param city A reference to the current city.
 */
Node::Node(City &city): city(city) {
    for(int i = 0; i < 4; i++)
        neighboring_nodes[i] = nullptr;
}

/** Get revenue of a Node. 
 * 
 * Virtual function. 
 * Returns the amount of revenue earned by the Node. 
 * 
 * Returns zero because only Revenue buildings have revenue. 
 * @return 0 
 */
int Node::get_revenue() const {
    return 0;
}

/** Get population of a Node. 
 * 
 * Virtual function. 
 * Returns the population of the Node. 
 * 
 * Returns zero because only Residential buildings have residential. 
 * @return 0 
 */
int Node::get_population() const {
    return 0;
}

/** Get the maximum population of a Node. 
 * 
 * Virtual function. 
 * Calculate the maximum population of a Residential building by the following: 
 * For Houses, it is 50 * (1 + neighboring Residential building). 
 * For Apartments, it is 250 * (1 + neighboring Residential building). 
 * 
 * Returns zero because only Residential buildings have maximum population. 
 * @return 0
 */
int Node::get_max_population() const {
    return 0;
}

/** Get the population growth for a Node. 
 * 
 * Virtual function. 
 * Calculate the maximum population of a Residential building by the following: 
 * The minimum between 
 * i) population growth rate of the city * (number of neighboring Health buildings - number of neighboring Gold Mines) / 10. 
 * ii) The remaining population: maximum population - population. 
 * 
 * Returns zero because only Residential buildings have population growth. 
 * @return 0
 */
int Node::get_population_growth() const {
    return 0;
}

/** Get the population growth rate contribution for a Node. 
 * 
 * Virtual function. 
 * Calculate the maximum population of a Residential or Health building by the following: 
 * For Residential buildings, it is -population of the building. 
 * For Clinics, it is 60 / (1 + number of neighboring Health buildings). 
 * For Hospitals, it is 360 / (1 + number of neighboring Health buildings). 
 * For other buildings, it is 0. 
 * 
 * Returns zero because only Residential and Health buildings have population growth rate contribution. 
 * @return 0 
 */
int Node::get_population_growth_rate_contribution() const {
    return 0;
}

/** Get the number of work trips generated from a Node. 
 * 
 * Virtual function. 
 * Work trips are trips from a Residential building to a Revenue building. 
 * Calculate the number of work trips generated from a Residential building by the following: 
 * The building's population * (get_home_work_beta_0 + city's revenue * get_home_work_beta_1) 
 * where get_home_work_beta_0 and get_home_work_beta_1 are regression coefficients. 
 * 
 * Returns zero because only Residential buildings have work trip generation. 
 * @return 0
 */
int Node::get_work_trips(){
    return 0;
}

/** Get the number of health trips generated from a Node. 
 * 
 * Virtual function. 
 * Health trips are trips from a Residential building to a Health building. 
 * Calculate the number of health trips generated from a Residential building by the following: 
 * The building's population * (get_home_health_beta_0 + city's revenue * get_home_health_beta_1) 
 * where get_home_health_beta_0 and get_home_health_beta_1 are regression coefficients. 
 * 
 * Returns zero because only Residential buildings have health trip generation. 
 * @return 0
 */
int Node::get_health_trips(){
    return 0;
}

/** Get the attractiveness factor of a Node. 
 * 
 * Virtual function. 
 * Returns the attractiveness of a Revenue or Health building. 
 * 
 * Returns zero because only Revenue or Health buildings have attractiveness. 
 * @return 0
 */
int Node::get_attractiveness() const{
    return 0;
}

/** Get the revenue per worker of a Node. 
 * 
 * Virtual function. 
 * Returns the revenue per worker of a Revenue building. 
 * 
 * Returns zero because only Revenue buildings have revenue per worker. 
 * @return 0
 */
int Node::get_revenue_per_worker() const{
    return 0;
}

/** Get the working population factor of a Node. 
 * 
 * Virtual function. 
 * Returns the working population of a Revenue building. 
 * 
 * Returns zero because only Revenue buildings have working population. 
 * @return 0
 */
int Node::get_working_population() const{
    return 0;
}

/** Increase the population of a Node. 
 * 
 * Virtual function. 
 * Increases the population of a Residential building. 
 * Does nothing because only Residential buildings have population. 
 */
void Node::increase_population(int population){}

/** Set the working population of a Node. 
 * 
 * Virtual function. 
 * Does nothing because only Revenue buildings have a working population.
 * @param population Working population of the Revenue building to be set to.
 * */
void Node::set_working_population(int population) {}

/** Get neighboring Node. 
 * 
 * Returns a pointer to its neighboring Node in the direction provided. 
 * 
 * @param direction Direction of the neighboring Node to be retrieved. 
 * @return Pointer to the neighboring Node in the direction provided. 
 */
Node* Node::get_neighboring_node(Node::Direction direction) const{
    return neighboring_nodes[static_cast<int>(direction)];
}

/** Set neighboring Node. 
 * 
 * Sets the pointer to a Node to this Node's neighbor in the direction provided. 
 * 
 * @param direction Direction of the neighboring Node to be set. 
 * @param n Pointer to the neighboring Node. 
 */
void Node::set_neighboring_node(Node::Direction direction, Node* n){
    neighboring_nodes[static_cast<int>(direction)] = n;
}

/** Get whether if a neighbouring Node is empty. 
 * 
 * Returns a boolean of whether a neighbouring Node is empty. 
 * 
 * @param direction Direction of the neighboring Node to be checked. 
 * @return Boolean for whether the neighboring Node is empty. 
 */
bool Node::is_neighbor_empty(Node::Direction direction){
    if(neighboring_nodes[static_cast<int>(direction)] == nullptr){
        return true;
    }
    else{
        return false;
    }
}

/** Get whether if a neighbouring Node is a road. 
 * 
 * Returns a boolean of whether a neighbouring Node is a road. 
 * 
 * @param direction Direction of the neighboring Node to be checked. 
 * @return Boolean for whether the neighboring Node is a road. 
 */
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

/** Get the number of neighbouring Residential buildings. 
 * 
 * Returns the number of neighbouring Residential buildings. 
 * 
 * @return Number of neighbouring Residential buildings 
 */
int Node::number_neighboring_residential_buildings() const{
    int num = 0;
    for(int i = 0; i < 4; i++)
        if(neighboring_nodes[i] != nullptr)
            if(neighboring_nodes[i]->get_category() == Node::Category::RESIDENTIAL) num++;
    return num;
}

/** Get the number of neighbouring Health buildings. 
 * 
 * Returns the number of neighbouring Health buildings.
 * 
 * @return Number of neighbouring Heatlth buildings 
 */
int Node::number_neighboring_health_buildings() const{
    int num = 0;
    for(int i = 0; i < 4; i++)
        if(neighboring_nodes[i] != nullptr)
            if(neighboring_nodes[i]->get_category() == Node::Category::HEALTH) num++;
    return num;
}

/** Get the number of neighbouring GoldMine buldings. 
 * 
 * Returns the number of neighbouring GoldMine buildings. 
 * 
 * @return Number of neighbouring GoldMine buildings
 */
int Node::number_neighboring_gold_mines() const{
    int num = 0;
    for(int i = 0; i < 4; i++)
        if(neighboring_nodes[i] != nullptr)
            if(neighboring_nodes[i]->get_type() == Node::Type::GOLD_MINE) num++;
    return num;
}

/** Get the total neighbouring population. 
 * 
 * Returns the total population of all neighbouring buildings. 
 * 
 * @return Total neighbouring population
 */
int Node::number_neighboring_population() const{
    int num = 0;
    for(int i = 0; i < 4; i++)
        if(neighboring_nodes[i] != nullptr)
            if(neighboring_nodes[i]->get_category() == Node::Category::RESIDENTIAL)
                num += neighboring_nodes[i]->get_population();
    return num; 
}




