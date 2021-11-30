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
#include "buildings/Street.h"
#include "buildings/Avenue.h"
#include "Trip_Distribution.h"
#include "Trip_Assignment.h"

#include <string>
#include <ostream>
#include <vector>
#include <algorithm>
using namespace std;

class City {
    friend class Trip_Distribution;
    friend class Trip_Assignment;

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
    int get_population() const;
    int get_max_population() const;
    int get_population_growth() const;
    float get_population_growth_rate() const;

    /// Functions that set the three vector data member containing all buildings in specific catagories 
    void set_all_residential();
    void set_all_revenue();
    void set_all_health();

    Node *get_at(const Coordinates &coordinates) const;
    bool is_empty_at(const Coordinates &coordinates) const;
    bool can_construct(Node::Type type) const;
    bool can_construct(Node::Type type, const Coordinates &coordinates) const;
    bool construct_at(Node::Type type, const Coordinates &coordinates);
    bool demolish_at(const Coordinates &coordinates);

    void move_to_next_turn();

    inline Node *get_at(int x, int y) const {
        return get_at(Coordinates{x, y});
    };

    inline bool is_empty_at(int x, int y) const {
        return is_empty_at(Coordinates{x, y});
    };

    inline bool can_construct(Node::Type type, int x, int y) const {
        return can_construct(type, Coordinates{x, y});
    };

    inline bool construct_at(Node::Type type, int x, int y) {
        return construct_at(type, Coordinates{x, y});
    };

    inline bool demolish_at(int x, int y) {
        return demolish_at(Coordinates{x, y});
    };

    /// Functions that deal with regression coefficients and return revenue 
    inline float get_home_work_beta_0 () const {return home_work_beta_0;}
    inline float get_home_work_beta_1 () const{return home_work_beta_1;}
    inline float get_home_health_beta_0 () const{return home_health_beta_0;}
    inline float get_home_health_beta_1 () const {return home_health_beta_1;}
    inline void set_home_work_beta_0 (float beta)  {home_work_beta_0 = beta;}
    inline void set_home_work_beta_1 (float beta)  {home_work_beta_1 = beta;}
    inline void set_home_health_beta_0 (float beta)  {home_health_beta_0 = beta;}
    inline void set_home_health_beta_1 (float beta)  {home_health_beta_1 = beta;}
    inline int  get_revenue() const {return revenue;}
    
    /// God Mode: set the city's budget into newbud
    void set_budget(int newbud);

private:
    Node ***grid;
    int grid_size;
    int budget;
    int turn;
    int revenue; 
    int population_growth;
    float population_growth_rate;

    vector<Residential*> all_residential_buildings;
    vector<Revenue*> all_revenue_buildings;
    vector<Health*> all_health_buildings;

    /// regression coefficients used in computing the formula used in the traffic models
    float home_work_beta_0 = 0.8f;
    float home_work_beta_1 = 0.001f;
    float home_health_beta_0 = 0.1f;
    float home_health_beta_1 = 0.00025f;
};

#endif // CITY_H
