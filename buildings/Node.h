/** 
 * This class is used to store the game map as a data structure like a doubly linked list, but in two dimensional.
 * Such a class is established for better programming logic.
*/
#include <iostream>
using namespace std;

class Node{
    private:
        /// These four pointers are used to point at the four neighbouring building/road objects
        Node* neighboring_nodes[4]{};

    public:  
        // enum class NodeType {
        //     BUILDING,
        //     ROAD
        // };

        enum class Direction{
            NORTH,
            EAST,
            SOUTH,
            WEST
        };

        /// ABC functions that access to the building/road information 
        // virtual Node::NodeType get_node_type() const = 0;
        virtual int get_cost() const = 0;
        virtual std::string get_long_information() const = 0;
        virtual std::string get_short_information() const = 0;
    
        /// functions that access the four neighbouring building/road object
        Node* get_neighboring_building(Direction direction) const;

        /// functions that set the four neighbouring building/road object        
        void set_neighboring_building(Direction direcion, Node* n);

        /// functions that return whether the neighouring pointers are registered or not
        bool is_neighbor_empty(Direction direction) const;

        /// functions that return whether the itself and neighouring pointers are road object or not
        virtual bool is_neighbor_road(Direction direcion);
        

    
};
