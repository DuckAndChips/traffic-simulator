/**
* Do not modify
*/

#ifndef CITY_H
#define CITY_H

#include "buildings/Clinic.h"
#include "buildings/Hospital.h"
#include "buildings/SilverMine.h"
#include "buildings/GoldMine.h"
#include "buildings/House.h"
#include "buildings/Apartment.h"
#include <string>
#include <ostream>

class City {
public:
    struct Coordinates {
        int x;
        int y;

        friend std::ostream &operator<<(std::ostream &output, const Coordinates &coordinates) {
            output << "(" << coordinates.x << "," << coordinates.y << ")";
            return output;
        }
    };

    explicit City(int size);
    explicit City(const std::string &filename);
    ~City();
    
    void save(const std::string& filename) const;

    int get_turn() const;
    int get_budget() const;
    int get_grid_size() const;

    int get_revenue() const;
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
    int get_population_growth_rate() const;

    Building *get_at(const Coordinates &coordinates) const;
    bool is_empty_at(const Coordinates &coordinates) const;
    bool can_construct(Building::Type type) const;
    bool can_construct(Building::Type type, const Coordinates &coordinates) const;
    bool construct_at(Building::Type type, const Coordinates &coordinates);
    bool demolish_at(const Coordinates &coordinates);

    void move_to_next_turn();

    inline Building *get_at(int x, int y) const {
        return get_at(Coordinates{x, y});
    };

    inline bool is_empty_at(int x, int y) const {
        return is_empty_at(Coordinates{x, y});
    };

    inline bool can_construct(Building::Type type, int x, int y) const {
        return can_construct(type, Coordinates{x, y});
    };

    inline bool construct_at(Building::Type type, int x, int y) {
        return construct_at(type, Coordinates{x, y});
    };

    inline bool demolish_at(int x, int y) {
        return demolish_at(Coordinates{x, y});
    };

private:
    Building ***grid;
    int grid_size;
    int budget;
    int turn;
};

#endif // CITY_H
