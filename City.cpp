#include "City.h"
#include <fstream>

using namespace std;

City::City(int size): grid_size(size), budget(150), turn(1) {
    grid = new Building **[size];
    for (int x = 0; x < size; x++) {
        grid[x] = new Building *[size];
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

    grid = new Building **[grid_size];
    for (int x = 0; x < grid_size; x++) {
        grid[x] = new Building *[grid_size];
        for (int y = 0; y < grid_size; y++) {
            int type;
            input >> type;

            if (type >= 1 && type <= 6) {
                switch (static_cast<Building::Type>(type)) {
                    case Building::Type::CLINIC:
                        grid[x][y] = new Clinic{*this};
                        break;
                    case Building::Type::HOSPITAL:
                        grid[x][y] = new Hospital{*this};
                        break;
                    case Building::Type::SILVER_MINE:
                        grid[x][y] = new SilverMine{*this};
                        break;
                    case Building::Type::GOLD_MINE:
                        grid[x][y] = new GoldMine{*this};
                        break;
                    case Building::Type::HOUSE: {
                        int population;
                        input >> population;
                        grid[x][y] = new House{*this, population};
                        break;
                    }
                    case Building::Type::APARTMENT: {
                        int population;
                        input >> population;
                        grid[x][y] = new Apartment{*this, population};
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
            Building *building = grid[x][y];
            if (building) {
                if (x > 0) {
                    Building *neighbor = get_at(x - 1, y);
                    if (neighbor) {
                        building->register_neighboring_building(neighbor);
                    }
                }

                if (x < grid_size - 1) {
                    Building *neighbor = get_at(x + 1, y);
                    if (neighbor) {
                        building->register_neighboring_building(neighbor);
                    }
                }

                if (y > 0) {
                    Building *neighbor = get_at(x, y - 1);
                    if (neighbor) {
                        building->register_neighboring_building(neighbor);
                    }
                }

                if (y < grid_size - 1) {
                    Building *neighbor = get_at(x, y + 1);
                    if (neighbor) {
                        building->register_neighboring_building(neighbor);
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
                if (grid[x][y]->get_category() == Building::Category::RESIDENTIAL) {
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

Building* City::get_at(const Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return nullptr;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return nullptr;

    return grid[coordinates.x][coordinates.y];
}

bool City::is_empty_at(const Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    return get_at(coordinates) == nullptr;
}

bool City::can_construct(Building::Type type) const {
    int cost;
    switch (type) {
        case Building::Type::CLINIC:
            cost = Clinic::cost;
            break;
        case Building::Type::HOSPITAL:
            cost = Hospital::cost;
            break;
        case Building::Type::SILVER_MINE:
            cost = SilverMine::cost;
            break;
        case Building::Type::GOLD_MINE:
            cost = GoldMine::cost;
            break;
        case Building::Type::HOUSE:
            cost = House::cost;
            break;
        case Building::Type::APARTMENT:
            cost = Apartment::cost;
            break;
    }

    return (cost <= budget);
}

bool City::can_construct(Building::Type type, const Coordinates &coordinates) const {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (!is_empty_at(coordinates.x, coordinates.y))
        return false;

    return can_construct(type);
}

bool City::construct_at(Building::Type type, const Coordinates &coordinates) {
    if (!can_construct(type, coordinates.x, coordinates.y))
        return false;

    Building *building;
    switch (type) {
        case Building::Type::CLINIC:
            building = new Clinic{*this};
            break;
        case Building::Type::HOSPITAL:
            building = new Hospital{*this};
            break;
        case Building::Type::SILVER_MINE:
            building = new SilverMine{*this};
            break;
        case Building::Type::GOLD_MINE:
            building = new GoldMine{*this};
            break;
        case Building::Type::HOUSE:
            building = new House{*this, 0};
            break;
        case Building::Type::APARTMENT:
            building = new Apartment{*this, 0};
            break;
    }

    grid[coordinates.x][coordinates.y] = building;
    this->budget -= building->get_cost();

    // Set neighboring buildings
    if (coordinates.x > 0) {
        Building *neighbor = get_at(coordinates.x - 1, coordinates.y);
        if (neighbor) {
            neighbor->register_neighboring_building(building);
            building->register_neighboring_building(neighbor);
        }
    }

    if (coordinates.x < grid_size - 1) {
        Building *neighbor = get_at(coordinates.x + 1, coordinates.y);
        if (neighbor) {
            neighbor->register_neighboring_building(building);
            building->register_neighboring_building(neighbor);
        }
    }

    if (coordinates.y > 0) {
        Building *neighbor = get_at(coordinates.x, coordinates.y - 1);
        if (neighbor) {
            neighbor->register_neighboring_building(building);
            building->register_neighboring_building(neighbor);
        }
    }

    if (coordinates.y < grid_size - 1) {
        Building *neighbor = get_at(coordinates.x, coordinates.y + 1);
        if (neighbor) {
            neighbor->register_neighboring_building(building);
            building->register_neighboring_building(neighbor);
        }
    }

    return true;
}

bool City::demolish_at(const Coordinates &coordinates) {
    if (coordinates.x < 0 || coordinates.x >= grid_size)
        return false;
    if (coordinates.y < 0 || coordinates.y >= grid_size)
        return false;

    if (grid[coordinates.x][coordinates.y] == nullptr)
        return false;

    Building *building = grid[coordinates.x][coordinates.y];
    // Set neighboring buildings
    if (coordinates.x > 0) {
        Building *neighbor = get_at(coordinates.x - 1, coordinates.y);
        if (neighbor) {
            neighbor->deregister_neighboring_building(building);
            building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.x < grid_size - 1) {
        Building *neighbor = get_at(coordinates.x + 1, coordinates.y);
        if (neighbor) {
            neighbor->deregister_neighboring_building(building);
            building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.y > 0) {
        Building *neighbor = get_at(coordinates.x, coordinates.y - 1);
        if (neighbor) {
            neighbor->deregister_neighboring_building(building);
            building->deregister_neighboring_building(neighbor);
        }
    }

    if (coordinates.y < grid_size - 1) {
        Building *neighbor = get_at(coordinates.x, coordinates.y + 1);
        if (neighbor) {
            neighbor->deregister_neighboring_building(building);
            building->deregister_neighboring_building(neighbor);
        }
    }

    delete building;
    grid[coordinates.x][coordinates.y] = nullptr;

    return true;
}

void City::move_to_next_turn() {
    turn++;
    /**
        * Compute revenue first
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
