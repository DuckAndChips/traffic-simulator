#include "Residential.h"
#include "../City.h"
#include <algorithm>
/// using namespace std;

/** Construct a Residential building. 
 * 
 * Virtual function. 
 * This constructor can only be called by its childs. 
 * Constructs a Node with the current city and sets population of building as provided.
 * 
 * @param city A reference to the current city.
 * @param population Population of the Residential buildings to be set to.
 */
Residential::Residential(City &city, int population) : Node(city), population(population) {}

/** Get the category of a Residential building. 
 * 
 * @return A Node::Category::RESIDENTIAL enum value of Node::Category.
 * */
Node::Category Residential::get_category() const {
    return Category::RESIDENTIAL;
}

/** Get population of a Residential building. 
 * 
 * Virtual function. 
 * Returns the population of the Residential building. 
 *  
 * @return Population of the Residential building 
 */
int Residential::get_population() const {
    return population;
}

/** Get the population growth for a Residential building. 
 * 
 * Virtual function. 
 * Calculate the maximum population of a Residential building by the following: 
 * The minimum between 
 * i) population growth rate of the city * (number of neighboring Health buildings - number of neighboring Gold Mines) / 10. 
 * ii) The remaining population: maximum population - population. 
 * 
 * @return Population growth for the Residential building
 */
int Residential::get_population_growth() const {
    
    return std::min(
            city.get_population_growth_rate() * (number_neighboring_health_buildings() - number_neighboring_gold_mines()) / 10,
            get_max_population() - population
    );
}

/** Get the population growth rate contribution for a Node. 
 * 
 * This is an original function in PA4 that is depreciated
 * due to the different game mechanics.
 * 
 * Virtual function. 
 * Calculate the maximum population of a Residential or Health building by the following: 
 * For Residential buildings, it is -population of the building. 
 * For Clinics, it is 60 / (1 + number of neighboring Health buildings). 
 * For Hospitals, it is 360 / (1 + number of neighboring Health buildings). 
 * For other buildings, it is 0. 
 * 
 * @return Maximum population of a Residential building
 */
int Residential::get_population_growth_rate_contribution() const {
    return -population;
}

/** Increase the population of a Residential building. 
 * 
 * Increases the population of a Residential building 
 * by the provided amount until it reaches its maximum population.
 * 
 * @param p Population increase
 */
void Residential::increase_population(int p) {
    population += p;
    const int max_population = get_max_population();
    if (population > max_population) {
        population = max_population;
    }
    if (population < 0) {
        population = 0;
    }
}

/** Get the number of work trips generated from a Residential building. 
 * 
 * Virtual function. 
 * Work trips are trips from a Residential building to a Revenue building. 
 * Calculate the number of work trips generated from a Residential building by the following: 
 * The building's population * (get_home_work_beta_0 + city's revenue * get_home_work_beta_1) 
 * where get_home_work_beta_0 and get_home_work_beta_1 are regression coefficients. 
 * 
 * @return Work trips generated from a Residential building
 */
int Residential::get_work_trips(){
    work_trips = population*(city.get_home_work_beta_0() + city.get_revenue()*city.get_home_work_beta_1());
    return work_trips;
}

/** Get the number of health trips generated from a Residential building. 
 * 
 * Virtual function. 
 * Health trips are trips from a Residential building to a Health building. 
 * Calculate the number of health trips generated from a Residential building by the following: 
 * The building's population * (get_home_health_beta_0 + city's revenue * get_home_health_beta_1) 
 * where get_home_health_beta_0 and get_home_health_beta_1 are regression coefficients. 
 *
 * @return Health trips generated from a Residential building
 */
int Residential::get_health_trips(){
    health_trips = population*(city.get_home_health_beta_0() + city.get_revenue()*city.get_home_health_beta_1());
    return health_trips;
}