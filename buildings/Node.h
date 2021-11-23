/** 
 * This class is used to store the game map as a data structure like a doubly linked list, but in two dimensional.
 * Such a class is established for better programming logic.
*/
#include <iostream>
using namespace std;

class Node{
    private:
        /// These four pointers are used to point at the four neighbouring building/road objects
        Node* east;
        Node* south;
        Node* west;
        Node* north;

    public:  
        enum class NodeType {
            BUILDING,
            ROAD
        };

        /// ABC functions that access to the building/road information 
        // virtual Node::NodeType get_node_type() const = 0;
        virtual int get_cost() const = 0;
        virtual std::string get_long_information() const = 0;
        virtual std::string get_short_information() const = 0;
    
        /// functions that access the four neighbouring building/road object
        Node* get_east_pointer() const;
        Node* get_south_pointer() const;
        Node* get_west_pointer() const;
        Node* get_north_pointer() const;

        /// functions that set the four neighbouring building/road object
        void set_east_pointer(Node* n);
        void set_south_pointer(Node* n);
        void set_west_pointer(Node* n);
        void set_north_pointer(Node* n);
        
        /// functions that return whether the neighouring pointers are registered or not
        bool is_east_empty() const;
        bool is_south_empty() const;
        bool is_west_empty() const;
        bool is_north_empty() const;

        /// functions that return whether the itself and neighouring pointers are road object or not
        virtual bool is_east_road() const;
        virtual bool is_south_road() const;
        virtual bool is_west_road() const;
        virtual bool is_north_road() const;
        

    
};
