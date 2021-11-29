#include "City.h"
#include <fstream>

using namespace std;

City::City(int size): grid_size(size), budget(150), turn(1) {
    grid = new Node **[size];
    for (int x = 0; x < size; x++) {
        grid[x] = new Node *[size];
        for (int y = 0; y < size; y++) {
            grid[x][y] = nullptr;
        }
    }
}

City::City(const std::string &filename): grid_size(0), budget(150), turn(1) {
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

            if (type >= 1 && type <= 8) {
                switch (static_cast<Node::Type>(type)) {
                    case Node::Type::CLINIC: {
                        Clinic* c = new Clinic{*this};
                        grid[x][y] = c;
                        all_health_buildings.push_back(c);
                        break;
                    }
                    case Node::Type::HOSPITAL: {
                        Hospital* hp = new Hospital{*this};
                        grid[x][y] = hp;
                        all_health_buildings.push_back(hp);
                        break;
                    }
                    case Node::Type::SILVER_MINE: {
                        SilverMine* sm = new SilverMine{*this};
                        grid[x][y] = sm;
                        all_revenue_buildings.push_back(sm);
                        break;
                    }
                    case Node::Type::GOLD_MINE: {
                        GoldMine* gm = new GoldMine{*this};
                        grid[x][y] = gm;
                        all_revenue_buildings.push_back(gm);
                        break;
                    }
                    case Node::Type::HOUSE: {
                        int population;
                        input >> population;
                        House* h = new House{*this, population};
                        grid[x][y] = h;
                        all_residential_buildings.push_back(h);
                        break;
                    }
                    case Node::Type::APARTMENT: {
                        int population;
                        input >> population;
                        Apartment* ap = new Apartment{*this, population};
                        grid[x][y] = ap;
                        all_residential_buildings.push_back(ap);
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
                grid[x][y] = nullptr;
            }
        }
    }

    input.close();

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

City::~City() {
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            delete grid[x][y];
        }
        delete[] grid[x];
    }
    delete[] grid;
}

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

int City::get_turn() const {
    return turn;
}

int City::get_budget() const {
    return budget;
}

int City::get_grid_size() const {
    return grid_size;
}

int City::get_revenue() const {
    int revenue = 0;
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                revenue += grid[x][y]->get_revenue();
            }
        }
    }
    return revenue;
}

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

int City::get_population_growth() const {
    int population_change = 0;
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                population_change += grid[x][y]->get_population_growth();
            }
        }
    }
    return population_change;
}

int City::get_population_growth_rate() const {
    int population_growth_rate = 0;
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                population_growth_rate += grid[x][y]->get_population_growth_rate_contribution();
            }
        }
    }
    return population_growth_rate;
}

Node* City::get_at(const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return nullptr;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return nullptr;

    return grid[coordinates.x][coordinates.y];
}

bool City::is_empty_at(const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    return get_at(coordinates) == nullptr;
}

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

bool City::can_construct(Node::Type type, const City::Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (!is_empty_at(coordinates.x, coordinates.y))
        return false;

    return can_construct(type);
}

bool City::construct_at(Node::Type type, const City::Coordinates &coordinates) {
    if (!can_construct(type, coordinates.x, coordinates.y))
        return false;

    Node *building;
    switch (type) {
        case Node::Type::CLINIC: {
            Clinic* c = new Clinic{*this};
            all_health_buildings.push_back(c);
            building = c;                           /// potential source of error here 
            break;
        }
        case Node::Type::HOSPITAL: {
            Hospital* hp = new Hospital{*this};
            building = hp;
            all_health_buildings.push_back(hp);
            break;
        }
        case Node::Type::SILVER_MINE: {
            SilverMine* sm = new SilverMine{*this};
            building = sm;
            all_revenue_buildings.push_back(sm);
            break;
        }
        case Node::Type::GOLD_MINE: {
            GoldMine* gm = new GoldMine{*this};
            building = gm;
            all_revenue_buildings.push_back(gm);
            break;
        }
        case Node::Type::HOUSE: {
            House* h = new House{*this, 0};
            building = h;
            all_residential_buildings.push_back(h);
            break;
        }
        case Node::Type::APARTMENT: {
            Apartment* ap = new Apartment{*this, 0};
            building = ap;
            all_residential_buildings.push_back(ap);
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

bool City::demolish_at(const City::Coordinates &coordinates) {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (grid[coordinates.x][coordinates.y] == nullptr)
        return false;

    Node *building = grid[coordinates.x][coordinates.y];
    switch (building->get_category())
    {
    case Node::Category::HEALTH: {
        vector<Health*>::iterator h = find(all_health_buildings.begin(),all_health_buildings.end(),building); /// potential source of error
        all_health_buildings.erase(h);
        break;
    }
    case Node::Category::RESIDENTIAL: {
        vector<Residential*>::iterator p = find(all_residential_buildings.begin(),all_residential_buildings.end(),building); /// potential source of error
        all_residential_buildings.erase(p);
        break;
    }
    case Node::Category::REVENUE: {
        vector<Revenue*>::iterator r = find(all_revenue_buildings.begin(),all_revenue_buildings.end(),building); /// potential source of error
        all_revenue_buildings.erase(r);
        break;
    }
    default:
        break;
    }

    // Set neighboring buildings
    if (coordinates.x > 0) {
        Node *neighbor = get_at(coordinates.x - 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::EAST,nullptr);
            // building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.x < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x + 1, coordinates.y);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::WEST,nullptr);
            // building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.y > 0) {
        Node *neighbor = get_at(coordinates.x, coordinates.y - 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::NORTH,nullptr);
            // building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.y < grid_size - 1) {
        Node *neighbor = get_at(coordinates.x, coordinates.y + 1);
        if (neighbor) {
            neighbor->set_neighboring_node(Node::Direction::SOUTH,nullptr);
            // building->deregister_neighboring_building(neighbor);
        }
    }

    delete building;
    grid[coordinates.x][coordinates.y] = nullptr;

    return true;
}

void City::move_to_next_turn() {
    turn++;

    /**
        * Handle traffic first
        */

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

    /// Then, we creat a Trip_Assignment object with dummy refrence passed to it
    std::vector<Road*> dummy_r;
    std::vector<std::vector<int>> dummy_od;
    Trip_Assignment trip_assignment(*this,dummy_r,dummy_r,dummy_od);

    /// Thirdly, we create 2 Trip_Distribution objects to handle home work trips and home health trips respectively
    /// If Trip_Distribution objects can done their works successfully, we call the Trip_Assignment object to assign traffic to
    /// the road network
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
        * Compute revenue 
        */

    budget += get_revenue();

    /**
        * Adjust population of the tile according to the change in population of the tile
        * Note that the change in population itself alters the population growth rate,
        * which in turn affects the change in population.
        *
        * Therefore we first save the change in populations in a tile in a separate array,
        * and then we apply the adjustments.
        */

    int** population_change = new int* [grid_size];
    for (int x = 0; x < grid_size; x++) {
        population_change[x] = new int[grid_size];
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] == nullptr) {
                population_change[x][y] = 0;
            }
            else {
                population_change[x][y] = grid[x][y]->get_population_growth();
            }
        }
    }

    // Now apply the change in population to each tile
    for (int x = 0; x < grid_size; x++) {
        for (int y = 0; y < grid_size; y++) {
            if (grid[x][y] != nullptr) {
                grid[x][y]->increase_population(population_change[x][y]);
            }
        }
    }

    // Remember to free the memory
    for (int x = 0; x < grid_size; x++) {
        delete[] population_change[x];
    }
    delete[] population_change;
}

void City::set_budget(int newbud){
    if (newbud < 0){return;}
    budget = newbud;
}
