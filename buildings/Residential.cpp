#include "Residential.h"
#include "../City.h"
#include <algorithm>
/// using namespace std;

Residential::Residential(City &city, int population) : Node(city), population(population) {}

Node::Category Residential::get_category() const {
    return Category::RESIDENTIAL;
}

int Residential::get_population() const {
    return population;
}


int Residential::get_population_growth() const {
    
    return std::min(
            city.get_population_growth_rate() * (number_neighboring_health_buildings() - number_neighboring_gold_mines()) / 10,
            get_max_population() - population
    );
}

int Residential::get_population_growth_rate_contribution() const {
    return -population;
}

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

int Residential::get_work_trips(){
    work_trips = population*(city.get_home_work_beta_0() + city.get_revenue()*city.get_home_work_beta_1());
    return work_trips;
}
int Residential::get_health_trips(){
    health_trips = population*(city.get_home_health_beta_0() + city.get_revenue()*city.get_home_health_beta_1());
    return health_trips;
}