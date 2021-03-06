
#ifndef NODE_H
#define NODE_H

#include <string>

class City;

/**
 * Node class
 * 
 * A node can be a building or a road on the grid.
 * Every element in the grid in City::city will point to either a nullptr or a Node object.
 * This class holds information and methods for Nodes in the city grid.
 * 
 */
class Node {
public:
    enum class Type {
        CLINIC = 1,
        HOSPITAL = 2,
        SILVER_MINE = 3,
        GOLD_MINE = 4,
        HOUSE = 5,
        APARTMENT = 6,
        STREET = 7,
        AVENUE = 8        
    };

    enum class Category {
        HEALTH,
        REVENUE,
        RESIDENTIAL,
        ROAD
    };

    enum class Direction{
            NORTH = 0,
            EAST = 1,
            SOUTH = 2,
            WEST = 3
        };

    virtual ~Node() = default;

    /// Functions that return node informations
    /// (A) Information regarding the nature of the node 
    virtual Node::Type get_type() const = 0;
    virtual Node::Category get_category() const = 0;
    virtual std::string get_long_information() const = 0;
    virtual std::string get_short_information() const = 0;

    /// (B) Information regarding the gaming mechanism of SimpleCity
    virtual int get_cost() const = 0;
    virtual int get_revenue() const;
    virtual int get_population() const;
    virtual int get_max_population() const;
    virtual int get_population_growth() const;
    virtual int get_population_growth_rate_contribution() const;
    virtual int get_work_trips(); /// This functions also update the work_trips data member for a Residential object
    virtual int get_health_trips(); /// This functions also update the health_trips data member for a Residential object
    virtual int get_attractiveness() const; 
    virtual int get_revenue_per_worker() const; 
    virtual int get_working_population() const; 

    /// Functions that implement the gaming mechanism 
    virtual void increase_population(int population);
    virtual void set_working_population(int population);

    /// Functions that handle the Node pointers array used in this 2D doubly linked list data structure
    Node* get_neighboring_node(Direction direction) const;
    void set_neighboring_node(Direction direcion, Node* n);
    bool is_neighbor_empty(Direction direction);
    bool is_neighbor_road(Direction direcion) const; 

    // Functions that return information about neighboring buildings that will be useful for the game mechanics
    int number_neighboring_residential_buildings() const;
    int number_neighboring_health_buildings() const;
    int number_neighboring_gold_mines() const;
    int number_neighboring_population() const;
    

protected:
    explicit Node(City &city);

    City &city;

private:
    Node* neighboring_nodes[4];
};

#endif // NODE_H
