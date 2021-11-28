/**
* Notes by Jacky:
* I attempted to change the file name of this file but it led to linkage error that I do not know how to solve
* If you guys also don't know how to solve then I'll just handle it using some stupid method (recreate a new file) later
*/

#ifndef NODE_H
#define NODE_H

#include <string>

class City;

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

    /// Functions that implement the gaming mechanism 
    virtual void increase_population(int population);

    /// Functions that handle the Node pointers array used in this 2D doubly linked list data structure
    Node* get_neighboring_node(Direction direction) const;
    void set_neighboring_node(Direction direcion, Node* n);
    bool is_neighbor_empty(Direction direction);
    bool is_neighbor_road(Direction direcion) const; 

    /** 
     * original neighboring buildings functions in PA3/4
     * should be modified after the implementation of the new gaming algorithm
     */
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
