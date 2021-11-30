#include "Trip_Assignment.h"

#include <cmath>
using namespace std;

/** Setup the trip assignment object. 
 * 
 * This function setup all data members for the trip assignment object for it to work with.
 * 
 * @param origins A reference to a vector storing all pointers to the origins (Road objects)
 * @param destinations A reference to a vector storing all pointers to the destinations (Road objects)
 * @param OD A reference to a 2D vector storing the number of trips from origins to destinations (OD matrix)
 */
void Trip_Assignment::set_Traffic_Model(std::vector<Road*> &origins, std::vector<Road*> &destinations, std::vector<std::vector<int>> &OD){
    this->origin = origins;
    this->destination = destinations;
    this->OD_Matrix = OD;
}

/** The main function to perform trip assignments from the OD matrix to the given road networks
 * 
 * The following steps are performed in this functions:
 * Step 1:  Check the size consistency of the data members. If their size are not consistent, exit this function directly.
 *          Also check are the data members empty. If there exits data member not been set, exit this function directly.
 * Step 2:  For each pair of origin and destination,
 *          (i)     Get the number of trips from OD matrix. If the number of trips is zero, continue with the next set directly.
 *          (ii)    Get all possible paths from the origin to the destination using the get_all_paths helper function.
 *          (iii)   Load all number of trips to the road networks by incremental assignent using load_traffic helper function.
 *                  The incremental assignment involve the following steps:
 *                  1.  Set up the incremental portion. Here, we use 1 as default in this class.
 *                      In case this model is used to run a complicated network, set it to a higher number to reduce run-time. 
 *                  2.  Load the incremental portion of traffic to the road with the shortest travel time.
 *                  3.  Update the travel time based on the loaded traffic.
 *                  4.  Repeat the above steps until all traffic trips are loaded to the road network.                 
 */
void Trip_Assignment::trip_assignment_main(){ 
    /// Step 1: Error checking
    if(size_checking()){
        return;
    }

    /// Step 2:Loops through all OD pairs
    for(unsigned int i = 0; i < origin.size(); ++i){
        if(origin[i] == nullptr) continue;
        for(unsigned int j = 0; j < destination.size(); ++j){
            if(destination[j] == nullptr) continue;
            int trips = OD_Matrix[i][j];
            if(trips == 0) continue;

            /// This line of code should be used if incremental loading (default model) is used.
            std::vector<std::vector<Road*>> paths = get_all_paths(origin[i], destination[j]);

            /** 
             * Alternatively, trip assignment can be done by assigning all traffic to the shortest path (which is less accurate).
             * The remaining line of codes can be used to replace the get_all_paths function to implement the above trip assignment
             * model.
             */
//            // Model (all-or-nothing) start
//            std::vector<std::vector<Road*>> paths;
//            std::vector<Road*> path;
//            find_shortest_path(origin[i], destination[j], path);
//            paths.push_back(path);
//            // Model (all-or-nothing) end
            for(int k = 0; k < trips; k+= incremental_amount){
                load_traffic(paths);
            }
        }
    }
}

/** A helper function that return all possible paths from a starting point of road object to the end point of the road object.
 * 
 * It helps probably set up the parameters that passed to the overloading function for recursive function calls.
 * 
 * @param start_pt A pointer to the origins (Road objects)
 * @param end_pt A pointer to the destination (Road objects)
 * @return a vector containing all possible paths (a vector of all pointers to road objects alone the path)
 */
std::vector<std::vector<Road*>> Trip_Assignment::get_all_paths(Road* start_pt, Road* end_pt){
    std::vector<std::vector<Road*>> paths;
    std::vector<Road*> path_zero;
    path_zero.push_back(start_pt);
    paths.push_back(path_zero);
    get_all_paths(start_pt,end_pt,paths,path_zero);
    return paths;
}

/** A recursive function that return all possible paths from a starting point of road object to the end point of the road object.
 * 
 * @param start_pt A pointer to the origins (Road objects)
 * @param end_pt A pointer to the destination (Road objects)
 * @param paths used to store and return the possible paths by reference
 * @param path used to pass the walked path to the next recursive call
 * @return true if it is possible to reach the end_pt and false if it is not possible 
 */

bool Trip_Assignment::get_all_paths(Road* start_pt, Road* end_pt,std::vector<std::vector<Road*>>& paths, std::vector<Road*>& path){
    
    /// source of error: index handling
    if (paths.size() == 0) return false;
    
    /// end case: reach destination
    if(start_pt == end_pt) return true;

    /// check available road options (north, east, south, west)
    /// a road option is available only when their is a road exists in that direction and that road has not been passed

    std::vector<Road*> road_options;
    if(start_pt->get_neighboring_road(Node::Direction::NORTH)){
        bool check = true;
        for(unsigned int i = 0; i<path.size(); i++){
            if(path[i] == start_pt->get_neighboring_road(Node::Direction::NORTH)){
                 check = false;
                 break;
            }
        }
        if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::NORTH));
    }
    if(start_pt->get_neighboring_road(Node::Direction::EAST)){
        bool check = true;
        for(unsigned int i = 0; i<path.size(); i++){
            if(path[i] == start_pt->get_neighboring_road(Node::Direction::EAST)){
                 check = false;
                 break;
            }
        }
        if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::EAST));
    }
    if(start_pt->get_neighboring_road(Node::Direction::SOUTH)){
        bool check = true;
        for(unsigned int i = 0; i<path.size(); i++){
            if(path[i] == start_pt->get_neighboring_road(Node::Direction::SOUTH)){
                 check = false;
                 break;
            }
        }
        if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::SOUTH));
    }

    if(start_pt->get_neighboring_road(Node::Direction::WEST)){
        bool check = true;
        for(unsigned int i = 0; i<path.size(); i++){
            if(path[i] == start_pt->get_neighboring_road(Node::Direction::WEST)){
                 check = false;
                 break;
            }
        }
        if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::WEST));
    }


    /// end case: reach termination (no more road options)
    if(road_options.empty()) return false;

    /// recursive part
    std::vector<std::vector<Road*>> add_paths;

    for(unsigned int i=0; i < road_options.size(); ++i){
        std::vector<std::vector<Road*>> temp_paths;
            std::vector<Road*> path_zero;
            path_zero.push_back(road_options[i]);
            std::vector<Road*> temp_path;
            temp_path = path;
            temp_path.push_back(road_options[i]);
        temp_paths.push_back(path_zero);
        if(get_all_paths(road_options[i],end_pt,temp_paths,temp_path)){
            for(unsigned int j = 0; j < temp_paths.size(); ++j){
                add_paths.push_back(temp_paths[j]);
            }
        }
    }

    /// end case: reach termination (all avaiable road options are unable to reach destination)
    if(add_paths.size()==0) return false;

    /// add the path back to paths and return true to indicate this is a possible path
    paths[0].insert(paths[0].end(),add_paths[0].begin(),add_paths[0].end());

    for(unsigned int i = 1; i <add_paths.size(); ++i){
        std::vector<Road*> temp = path;
        temp.insert(temp.end(),add_paths[i].begin(),add_paths[i].end());
        paths.push_back(temp);
    }

    return true;
}

/** A helper function to load the incremental amount of traffic to the road network
 * 
 * The following steps are performed in this functions:
 * Step 1:  Set the first path be the paths with the shortest travel time.
 * Step 2:  Loop through all possible paths and update the shortest travel time and the index of the path with the shortest travel time
 * Step 3:  Load the incremental amount of traffic to the paths with shortest travel time
 * 
 * @param paths a vector containing all possible paths (a vector of all pointers to road objects alone the path)         
 */
void Trip_Assignment::load_traffic(std::vector<std::vector<Road*>> &paths){
    int index = 0;
    double shortest_time = get_travel_time(paths[0]);
    for(unsigned int i = 1; i<paths.size(); ++i){
        double time = get_travel_time(paths[i]);
        if(time < shortest_time){
            index = i;
            shortest_time = time;
        }
    }
    for(unsigned int j=0; j<paths[index].size(); ++j){
        paths[index][j]->traffic_flow_incremental(incremental_amount);
    }
}

/** A function to get the travel time of a given path.
 * 
 * It sums up all the travel time from the road networks. 
 * 
 * @param path a vector of all pointers to road objects alone the path
 * @return the total travel time of the path        
 */
double Trip_Assignment::get_travel_time(std::vector<Road*> &path){
    double time = 0;
    for(unsigned int i = 0; i < path.size(); ++i){
        time += path[i]->get_travel_time();
    }
    return time;
}

/** A helper function to check whether the data members of the Trip_Assignment class are probably set
 * 
 * @return true if: (1) any data members are empty or (2) the size of the data members are not consistent        
 */
bool Trip_Assignment::size_checking() const{
    unsigned int origin_size = origin.size();
    unsigned int destination_size = destination.size();

    /// check if the OD info are empty or not
    if(origin_size == 0 || destination_size == 0)    return true;
    if(origin_size != OD_Matrix.size()) return true;

    /// check the no of rows and columns matches with origin's size and destination's size or not
    for(unsigned int i = 0; i<origin_size ; ++i){
        if(OD_Matrix[i].size() != destination_size) return true;
    }

    return false;
}

/** A helper function to get the shortest path from an origin to a destination
 * 
 * Same implementation as the find_shortest_path function in Trip_Distribution class. Refer to the 
 * documentation there.
 * 
 * This function is included for all-or-nothing traffic assignment only.
 * Since our default model is the incremental loading, this function will never be called unless the code
 * in trip_assignment_main() is modified.        
 */
int Trip_Assignment::find_shortest_path(Road* start_pt, Road* end_pt, std::vector<Road*>& path){

    /// handling path to make sure it contains the current road*
    if(path.size() == 0){
        path.push_back(start_pt);
    }else{
        if(path.back() != start_pt)
            path.push_back(start_pt);
    }

    /// end cases
    /// case 1: reach destination
    if(start_pt == end_pt) return 1;

    /// case 2: all road options have been walked
        std::vector<Road*> road_options;
        if(start_pt->get_neighboring_road(Node::Direction::NORTH)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::NORTH)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::NORTH));
        }
        if(start_pt->get_neighboring_road(Node::Direction::EAST)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::EAST)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::EAST));
        }
        if(start_pt->get_neighboring_road(Node::Direction::SOUTH)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::SOUTH)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::SOUTH));
        }
        if(start_pt->get_neighboring_road(Node::Direction::WEST)){
            bool check = true;
            for(unsigned int i = 0; i<path.size(); i++){
                if(path[i] == start_pt->get_neighboring_road(Node::Direction::WEST)){
                     check = false;
                     break;
                }
            }
            if(check) road_options.push_back(start_pt->get_neighboring_road(Node::Direction::WEST));
        }
    if(road_options.empty()) return 999; /// case 3 return statement

    /// recursive part
    int path_dist = 999;
    std::vector<Road*> new_path = path;
    std::vector<Road*>::iterator q;
    for(q = road_options.begin(); q != road_options.end(); ++q){
        std::vector<Road*> temp = path;
        int dist = 1 + find_shortest_path(*q,end_pt,temp);
        if(dist < path_dist){
            path_dist = dist;
            new_path = temp;
        }
    }
    path = new_path;
    return path_dist;
}


