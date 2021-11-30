#include "City.h"
#include <fstream>

using namespace std;

/** Construct a City (a new city). 
 *   
 * Create a dynamic 2-D array of Node pointer, assign pointer to nullptr.
 * 
 * @param size A integer representing the size of City
 */
City::City(int size): grid_size(size), budget(200), turn(1), revenue(0), population_growth(0),population_growth_rate(0.0f) {
    grid = new Node **[size];
    for (int x = 0; x < size; x++) {
        grid[x] = new Node *[size];
        for (int y = 0; y < size; y++) {
            grid[x][y] = nullptr;
        }
    }
}

/** Construct a City (Load from file). 
 *   
 * Read the data from a .txt file
 * Create a dynamic 2-D array of Node pointer
 * Create different types of node and assign it's pointer to the grid[x][y]
 * according to the value read from the file
 * 
 * @param filename a constant string which gives the filename
 */
City::City(const std::string &filename): grid_size(0), budget(200), turn(1), revenue(0), population_growth(0),population_growth_rate(0.0f) {
    ifstream input;
    input.open(filename);

    input >> grid_size;
    input >> budget;
    input >> turn;

    grid = new Node **[grid_size];
    for (int x = 0; x < grid_size; x++) {
        grid[x] = new Node *[grid_size];
        for (int y = 0; y < grid_size; y++) {
            int type;
            input >> type;
            // Create different type of node, which is dynamically allocated
            if (type >= 1 && type <= 8) {
                switch (static_cast<Node::Type>(type)) {
                    case Node::Type::CLINIC: {
                        grid[x][y] = new Clinic{*this};
                        break;
                    }
                    case Node::Type::HOSPITAL: {
                        grid[x][y] = new Hospital{*this};
                        break;
                    }
                    case Node::Type::SILVER_MINE: {
                        grid[x][y] = new SilverMine{*this};
                        break;
                    }
                    case Node::Type::GOLD_MINE: {
                        grid[x][y] = new GoldMine{*this};
                        break;
                    }
                    case Node::Type::HOUSE: {
                        int population;
                        input >> population;
                        grid[x][y] = new House{*this, population};
                        break;
                    }
                    case Node::Type::APARTMENT: {
                        int population;
                        input >> population;
                        grid[x][y] = new Apartment{*this, population};
                        break;
                    }
                    case Node::Type::STREET: {
                        grid[x][y] = new Street{*this};
                        break;
                    }
                    case Node::Type::AVENUE: {
                        grid[x][y] = new Avenue{*this};
                        break;
                    }
                }
            }  
            else {
                // that grid cell would have no node, assign nullptr to it
                grid[x][y] = nullptr;
            }
        }
    }

    input.close();
    // Initialize / Set neighboring node for each building / road
    for (int x = 0; x < grid_size; ++x) {
        for (int y = 0; y < grid_size; ++y) {
            Node* building = grid[x][y];
            if (building) {
                if (x > 0) {
                    Node *neighbor = get_at(x - 1, y);
                    if (neighbor) {
                        building->set_neighboring_node(Node::Direction::WEST,neighbor);
                    }
                }

                if (x < grid_size - 1) {
                    Node *neighbor = get_at(x + 1, y);
                    if (neighbor) {
                        building->set_neighboring_node(Node::Direction::EAST,neighbor);
                    }
                }

                if (y > 0) {
                    Node *neighbor = get_at(x, y - 1);
                    if (neighbor) {
                        building->set_neighboring_node(Node::Direction::SOUTH,neighbor);
                    }
                }

                if (y < grid_size - 1) {
                    Node *neighbor = get_at(x, y + 1);
                    if (neighbor) {
                        building->set_neighboring_node(Node::Direction::NORTH,neighbor);
                    }
                }
            }
        }
    }
}

/** Destruct a City. 
 *   
 * Dynamically deallocate the memory used for storing the grid 
 *
 */
City::~City() {
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            delete grid[x][y];
        }
        delete[] grid[x];
    }
    delete[] grid;
}

/** Save a City to a .txt file. 
 *   
 * Output the city's information (grid_size, budget, turn, each grid cell's type) into a .txt file
 * 
 * @param filename A constant reference to a string; storing the filename of the saved file
 */
void City::save(const string &filename) const {
    ofstream output{filename, ios_base::trunc};

    output << grid_size << endl;
    output << budget << endl;
    output << turn << endl;

    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] == nullptr) {
                output << 0 << endl;
            } else {
                output << static_cast<int>(grid[x][y]->get_type());
                if (grid[x][y]->get_category() == Node::Category::RESIDENTIAL) {
                    output << " " << grid[x][y]->get_population();
                }
                output << endl;
            }
        }
    }

    output.flush();
    output.close();
}

/** Get the turn of the city
 *   
 * @return turn  the data member turn 
 *
 */
int City::get_turn() const {
    return turn;
}

/** Get the budget of the city
 *   
 * @return budget  the data member budget 
 *
 */
int City::get_budget() const {
    return budget;
}

/** Get the grid size of the city
 *   
 * @return grid_size  the data member grid_size 
 *
 */
int City::get_grid_size() const {
    return grid_size;
}

/** Get the population of the city
 *   
 * Return the sum of population from all nodes
 *
 * @return population A integer representing the total population of the city
 *
 */
int City::get_population() const {
    int population = 0;
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                population += grid[x][y]->get_population();
            }
        }
    }
    return population;
}

/** Get the Maximum population of the city
 *   
 * Return the sum of maximum population from all nodes
 *
 * @return max_population A integer representing the total maximum population of the city
 *
 */
int City::get_max_population() const {
    int max_population = 0;
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                max_population += grid[x][y]->get_max_population();
            }
        }
    }
    return max_population;
}

/** Get the population growth of the city
 *
 * @return population_growth A data member population_growth
 *
 */
int City::get_population_growth() const {
   return population_growth;
}


/** Get the population growth rate of the city
 *
 * @return population_growth_rate A data member population_growth_rate
 *
 */
float City::get_population_growth_rate() const {

    return population_growth_rate;
}


/** Get the node at grid[x][y]
 *
 * If the coordinates are not out of bound, get the nodes' pointer of that coordinate
 *
 * @param coordinates A constant reference to City::Coordinates
 *
 * @return grid[coordinates.x][coordinates.y] A pointer to a node
 *
 */
Node* City::get_at(const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return nullptr;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return nullptr;

    return grid[coordinates.x][coordinates.y];
}

/** Check whether grid[x][y] is empty
 *
 * If the coordinates are out of bound, return false
 * If the coordinates have a node, return true. Otherwise, return false
 *
 * @param coordinates A constant reference to City::Coordinates
 *
 * @return get_at(coordinates) == nullptr ; A boolean value indicating whether it is empty
 *
 */
bool City::is_empty_at(const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    return get_at(coordinates) == nullptr;
}

/** Determine whether a specific type of node can be constructed
 *
 * If the budget >= the required cost for that type of node, return true. Otherwise, false.
 *
 * @param type A Node::Type indicating the type of node user want to build
 *
 * @return (cost <= budget) A boolean value indicating whether we got sufficient budget to build
 *
 */
bool City::can_construct(Node::Type type) const {
    int cost;
    switch (type) {
        case Node::Type::CLINIC:
            cost = Clinic::cost;
            break;
        case Node::Type::HOSPITAL:
            cost = Hospital::cost;
            break;
        case Node::Type::SILVER_MINE:
            cost = SilverMine::cost;
            break;
        case Node::Type::GOLD_MINE:
            cost = GoldMine::cost;
            break;
        case Node::Type::HOUSE:
            cost = House::cost;
            break;
        case Node::Type::APARTMENT:
            cost = Apartment::cost;
            break;
        case Node::Type::STREET:
            cost = Street::cost;
            break;
        case Node::Type::AVENUE:
            cost = Avenue::cost;
            break;
    }

    return (cost <= budget);
}

/** Determine whether a specific type of node can be constructed
 *
 * If the coordinates if out of bound, return false.
 * If that coordinate already have other node, return false
 * If the budget >= the required cost for that type of node, return true. Otherwise, return false.
 *
 * @param type A Node::Type indicating the type of node user want to build
 * @param coordinates A constant reference to City::Coordinates indicating the coordinates users want to build on
 *
 * @return can_construct(type) A boolean value indicating whether we can build that type of node in that coordinate
 *
 */
bool City::can_construct(Node::Type type, const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (!is_empty_at(coordinates.x, coordinates.y))
        return false;

    return can_construct(type);
}

/** Construct a node at that coordinate
 *
 * By calling can_construct(), if we can construct there
 * Construct the node, and register the neighboring nodes
 *
 * @param type A Node::Type indicating the type of node user want to build
 * @param coordinates A constant reference to City::Coordinates indicating the coordinates users want to build on
 *
 * @return a boolean value, which indicates whether the construction success or not 
 *
 */
bool City::construct_at(Node::Type type, const City::Coordinates &coordinates) {
    if (!can_construct(type, coordinates.x, coordinates.y))
        return false;

    Node *building;
    switch (type) {
        case Node::Type::CLINIC: {
            building = new Clinic{*this};
            break;
        }
        case Node::Type::HOSPITAL: {
            building = new Hospital{*this};
            break;
        }
        case Node::Type::SILVER_MINE: {
            building = new SilverMine{*this};
            break;
        }
        case Node::Type::GOLD_MINE: {
            building = new GoldMine{*this};
            break;
        }
        case Node::Type::HOUSE: {
            building = new House{*this, 10};
            break;
        }
        case Node::Type::APARTMENT: {
            building = new Apartment{*this, 20};
            break;
        }
        case Node::Type::STREET: {
            building = new Street{*this};
            break;
        }
        case Node::Type::AVENUE: {
            building = new Avenue{*this};
            break;
        }
    }

    grid[coordinates.x][coordinates.y] = building;
    this->budget -= building->get_cost();

    // Set neighboring buildings
    if (coordinates.x > 0) {
        Node *neighbor = get_at(coordinates.x - 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::EAST,building);
            building->set_neighboring_node(Node::Direction::WEST,neighbor);
        }
    }

    if (coordinates.x < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x + 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::WEST,building);
            building->set_neighboring_node(Node::Direction::EAST,neighbor);
        }
    }

    if (coordinates.y > 0) {
        Node *neighbor = get_at(coordinates.x, coordinates.y - 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::NORTH,building);
            building->set_neighboring_node(Node::Direction::SOUTH,neighbor);
        }
    }

    if (coordinates.y < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x, coordinates.y + 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::SOUTH,building);
            building->set_neighboring_node(Node::Direction::NORTH,neighbor);
        }
    }

    return true;
}



/** Demolish a node at that coordinate
 *
 * If the coordinates is out of bound, return false.
 * If the grid cell at that coordinates is empty, return false
 * Otherwise, deregister the neighbroing buildings and dynamically deallocate the node
 *
 * @param coordinates A constant reference to City::Coordinates indicating the coordinates users want to build on
 *
 * @return a boolean value, which indicates whether the destruction success or not 
 *
 */
bool City::demolish_at(const City::Coordinates &coordinates) {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (grid[coordinates.x][coordinates.y] == nullptr)
        return false;

    Node *building = grid[coordinates.x][coordinates.y];

    // Set neighboring buildings
    if (coordinates.x > 0) {
        Node *neighbor = get_at(coordinates.x - 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::EAST,nullptr);
        }
    }

    if (coordinates.x < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x + 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::WEST,nullptr);
        }
    }

    if (coordinates.y > 0) {
        Node *neighbor = get_at(coordinates.x, coordinates.y - 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::NORTH,nullptr);
        }
    }

    if (coordinates.y < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x, coordinates.y + 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::SOUTH,nullptr);
        }
    }

    delete building;
    grid[coordinates.x][coordinates.y] = nullptr;

    return true;
}

/** Move to the next turn of the game
 *
 * Handle the traffic calculation and assign population change
 * Increase turn by one
 *
 */
void City::move_to_next_turn() {
    turn++;
    
    // Handle traffic first
    
    /// First, we reset all the traffic on the road to zero
    for (int i = 0; i < grid_size; ++i){
        for (int j = 0; j < grid_size; ++j){
            if(grid[i][j] != nullptr){
                if(grid[i][j]->get_category() == Node::Category::ROAD){
                    Road* p = dynamic_cast<Road*>(grid[i][j]);
                    p->set_traffic_flow(0);
                }
            }
        }
    }

    /// Secondly, we create 2 Trip_Distribution objects to handle home work trips and home health trips respectively
    /// If Trip_Distribution objects can done their works successfully, we call the Trip_Assignment object to assign traffic to
    /// the road network

    set_all_health();
    set_all_residential();
    set_all_revenue();

    Trip_Assignment trip_assignment;
    Trip_Distribution home_work_trip(*this, all_residential_buildings, all_revenue_buildings, all_health_buildings);
    if(home_work_trip.trip_distribution_main(Node::Category::REVENUE)){
       trip_assignment.set_Traffic_Model(
            home_work_trip.origin, home_work_trip.destination, home_work_trip.OD_matrix
        );
        trip_assignment.trip_assignment_main();
    }

    Trip_Distribution home_health_trip(*this, all_residential_buildings, all_revenue_buildings, all_health_buildings);
    if(home_health_trip.trip_distribution_main(Node::Category::HEALTH)){
        trip_assignment.set_Traffic_Model(
            home_health_trip.origin, home_health_trip.destination, home_health_trip.OD_matrix
        );
        trip_assignment.trip_assignment_main();
    }

    /**
        * Assign working population to each revenue buildings and compute city's revenue:
        * Revenue of each Revenue buildings = no. of trips to that building * Revenue of that buildings
        */

    revenue = 0;
    for (unsigned int i = 0; i < all_revenue_buildings.size(); ++i){
        int no_of_trips = 0;
        for (unsigned int j=0; j < home_work_trip.OD_matrix.size(); ++j){
            no_of_trips += home_work_trip.OD_matrix[j][i];
        }
        all_revenue_buildings[i]->set_working_population(no_of_trips);
        revenue += all_revenue_buildings[i]->get_revenue_per_worker() * no_of_trips;
    }

    budget += revenue;

    /**
        * Assign population change to each revenue buildings:
        * if (travel time <= 10.5)
        *   population growth rate = no. of trips to health buildings / travel time to building 
        * if (10.5 <= travel time <= 11)
        *   population growth rate = no. of trips to health buildings / travel time to building / 10
        * if (11 <= travel time <= 15)
        *   population growth rate = no. of trips to health buildings / travel time to building / 100
        * if (travel time > 15 mins)
        *   population growth rate = - no. of trips to health buildings / travel time to building / 10
        * population change = current population * population growth
        */

    population_growth = 0;
    population_growth_rate = 0.0f;
    for (unsigned int i = 0; i < all_residential_buildings.size(); ++i){
        float growth_rate = 0.0f;
        for(unsigned int j = 0; j < all_health_buildings.size(); ++j){
            vector<Road*> path = home_health_trip.OD_path[i][j];
            if(!path.empty()){
                float travel_time = trip_assignment.get_travel_time(path);
                if(travel_time <= 10.5f)
                    growth_rate += (0.1f+ (home_health_trip.OD_matrix[i][j]/trip_assignment.get_travel_time(path)));
                else if(travel_time <= 11.0f)
                    growth_rate += (home_health_trip.OD_matrix[i][j]/trip_assignment.get_travel_time(path))/10;
                else if(travel_time <= 15.0f)
                    growth_rate += (home_health_trip.OD_matrix[i][j]/trip_assignment.get_travel_time(path))/100;
                else growth_rate -= (home_health_trip.OD_matrix[i][j]/trip_assignment.get_travel_time(path))/10;
            }
        }
        all_residential_buildings[i]->increase_population(all_residential_buildings[i]->get_population()*growth_rate);
        population_growth += all_residential_buildings[i]->get_population()*growth_rate;
    }
    if(get_population() != 0 ) population_growth_rate = static_cast<float>(population_growth) / get_population();

}


/** Set budget of the city to newbudget
 *
 * Warning : This function is for the demo purpose only. Typically, when gaming, this function won't be called
 * If newbud is invalid, return back.
 * Otherwise, assign newbud's value to city's budget
 *
 * @param newbud An integer value representing the new budget users want to change to
 *
 */
void City::set_budget(int newbud){
    if (newbud < 0){return;}
    budget = newbud;
}

/** Set All residential 
 *
 * Push all residential buildings in the city.
 *
 */
void City::set_all_residential(){
    all_residential_buildings.clear();
    for(int i=0; i<grid_size; ++i){
        for(int j=0; j<grid_size; ++j){
            if(grid[i][j] != nullptr){
                if(grid[i][j]->get_category() == Node::Category::RESIDENTIAL){
                    all_residential_buildings.push_back(dynamic_cast<Residential*>(grid[i][j]));
                }
            }
        }
    }
}


/** Set All revenue 
 *
 * Push all revenue buildings in the city.
 *
 */
void City::set_all_revenue(){
    all_revenue_buildings.clear();
    for(int i=0; i<grid_size; ++i){
        for(int j=0; j<grid_size; ++j){
            if(grid[i][j] != nullptr){
                if(grid[i][j]->get_category() == Node::Category::REVENUE){
                    all_revenue_buildings.push_back(dynamic_cast<Revenue*>(grid[i][j]));
                }
            }
        }
    }
}


/** Set All health 
 *
 * Push all health buildings in the city.
 *
 */
void City::set_all_health(){
    all_health_buildings.clear();
    for(int i=0; i<grid_size; ++i){
        for(int j=0; j<grid_size; ++j){
            if(grid[i][j] != nullptr){
                if(grid[i][j]->get_category() == Node::Category::HEALTH){
                    all_health_buildings.push_back(dynamic_cast<Health*>(grid[i][j]));
                }
            }
        }
    }
}
