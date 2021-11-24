
/**
 * The following code should remained here
 * This source code should be involving all global functions that handle the OD Matrix
 * The initialisation of the OD_Maxtrix should be handled outside this source code
 */ 

#include <vector>
#include <algorithm>
using namespace std;

#include "City.h"
#include "Node.h"
#include "buildings/Clinic.h"
#include "buildings/Hospital.h"
#include "buildings/SilverMine.h"
#include "buildings/GoldMine.h"
#include "buildings/House.h"
#include "buildings/Apartment.h"

class Traffic_Model {
    private:
        std::vector<Node*> origin;
        std::vector<Node*> destination;
        std::vector<std::vector<int>> OD_Matrix;
        City &city;
    public:
        
        explicit Traffic_Model();
        explicit Traffic_Model(std::vector<Node*> origin, std::vector<Node*> destination, std::vector<std::vector<int>> OD_Matrix);
        void set_Traffic_Model(std::vector<Node*> origin, std::vector<Node*> destination, std::vector<std::vector<int>> OD_Matrix);
        void set_Traffic_Model(int** testing2Darray, int num_origin, int num_destination);

        void trip_assignment();

        /// used for checking whether the origin, destination, OD_matrix are probably set
        /// return true whenever there is an inconsistency in the size of them or they are empty 
        bool error_checking() const;
        /// return true when the paths does not go from starting point to ending point
        bool error_checking(Node* start_pt, const Node* end_pt, const std::vector<std::vector<Node::Direction>> &paths) const;

        /// remaining are some helper functions that needed for trip assignment 
        std::vector<std::vector<Node::Direction>> get_all_paths(Node* start_pt, Node* end_pt); 
        void load_traffic(Node* start_pt, const std::vector<std::vector<Node::Direction>> &paths);
        double get_travel_time(Node* start_pt, const std::vector<Node::Direction> &path);
};








/**
 * The following code should be incorperatred into the city's class, probably
 */ 


vector<Residential*> all_residential_buildings;
vector<Revenue*> all_revenue_buildings;
vector<Health*> all_health_buildings;


