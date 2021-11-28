#include "trip_distribution.h"

Trip_distribution::Trip_distribution(City &city):city(city){
    Trip_distribution::set_all_residential();
    Trip_distribution::set_all_revenue();
    Trip_distribution::set_all_health();


}

void Trip_distribution::set_all_residential(){
    for(int i=0; i<city.get_grid_size(); i++){
        for(int j=0; j<city.get_grid_size(); j++){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::RESIDENTIAL){
                    all_residential_building.push_back(static_cast<Residential*>(city.grid[i][j]));
                }
            }
        }
    }
}

void Trip_distribution::set_all_revenue(){
    for(int i=0; i<city.get_grid_size(); i++){
        for(int j=0; j<city.get_grid_size(); j++){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::REVENUE){
                    all_destination_building.push_back(static_cast<Revenue*>(city.grid[i][j]));
                }
            }
        }
    }
}

void Trip_distribution::set_all_health(){
    for(int i=0; i<city.get_grid_size(); i++){
        for(int j=0; j<city.get_grid_size(); j++){
            if(city.grid[i][j] != nullptr){
                if(city.grid[i][j]->get_category() == Node::Category::HEALTH){
                    all_destination_building.push_back(static_cast<Health*>(city.grid[i][j]));
                }
            }
        }
    }
}

void Trip_distribution::set_origin(){
    for(std::vector<Residential*>::iterator i = all_residential_building.begin(); i != all_residential_building.end(); i++){
        Residential* residential = static_cast<Residential*>(*i);
        if(residential->is_neighbor_road(Node::Direction::NORTH) == true){
            origin.push_back(static_cast<Road*>(residential->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(residential->is_neighbor_road(Node::Direction::EAST) == true){
            origin.push_back(static_cast<Road*>(residential->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(residential->is_neighbor_road(Node::Direction::SOUTH) == true){
            origin.push_back(static_cast<Road*>(residential->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(residential->is_neighbor_road(Node::Direction::WEST) == true){
            origin.push_back(static_cast<Road*>(residential->get_neighboring_node(Node::Direction::WEST)));
        }
    }
}

void Trip_distribution::set_work_destination(){
    all_destination_building = static_cast<std::vector<Node*>>(all_revenue_building);
    for(std::vector<Revenue*>::iterator i = all_revenue_building.begin(); i != all_revenue_building.end(); i++){
        Revenue* revenue = static_cast<Revenue*>(*i);
        if(revenue->is_neighbor_road(Node::Direction::NORTH) == true){
            destination.push_back(static_cast<Road*>(revenue->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::EAST) == true){
            destination.push_back(static_cast<Road*>(revenue->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::SOUTH) == true){
            destination.push_back(static_cast<Road*>(revenue->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(revenue->is_neighbor_road(Node::Direction::WEST) == true){
            destination.push_back(static_cast<Road*>(revenue->get_neighboring_node(Node::Direction::WEST)));
        }
    }
}

void Trip_distribution::set_health_destination(){
    for(std::vector<Health*>::iterator i = all_health_building.begin(); i != all_health_building.end(); i++){
        Health* health = static_cast<Health*>(*i);
        if(health->is_neighbor_road(Node::Direction::NORTH) == true){
            destination.push_back(static_cast<Road*>(health->get_neighboring_node(Node::Direction::NORTH)));
        }
        else if(health->is_neighbor_road(Node::Direction::EAST) == true){
            destination.push_back(static_cast<Road*>(health->get_neighboring_node(Node::Direction::EAST)));
        }
        else if(health->is_neighbor_road(Node::Direction::SOUTH) == true){
            destination.push_back(static_cast<Road*>(health->get_neighboring_node(Node::Direction::SOUTH)));
        }
        else if(health->is_neighbor_road(Node::Direction::WEST) == true){
            destination.push_back(static_cast<Road*>(health->get_neighboring_node(Node::Direction::WEST)));
        }
    }
}


void Trip_distribution::OD_matrix_travel_time(){
    for(int i=0; i<all_residential_building.size(); i++){
        travel_time.push_back(std::vector<int>());
        for(int j=0; j<destination.size(); j++){
            std::vector<Road*>paths;
            travel_time[i].push_back(find_shortest_path(origin[i],destination[j],paths));
        }
    }
}

void Trip_distribution::OD_matrix_traffic(Node::Category category){
    for(int i1=0; i1< all_residential_building.size(); i1++){
        OD_matrix_number_of_trips.push_back(std::vector<int>());

        float sum_travel_time = 0;
        for(int j1=0; j1<all_destination_building.size(); j1++){
            sum_travel_time += 1/(travel_time[i1][j1]);
        }

        for(int j=0; j<destination.size(); j++){
            float this_travel_time = 1/(travel_time[i1][j]);
            if(this_travel_time != max_path){
                if(category == Node::Category::REVENUE){
                    OD_matrix_number_of_trips[i1].push_back(all_residential_building[i1]->get_work_trips()*this_travel_time/sum_travel_time);
                }
                else{
                    OD_matrix_number_of_trips[i1].push_back(all_residential_building[i1]->get_health_trips()*this_travel_time/sum_travel_time);
                }
            }
            else{
                OD_matrix_number_of_trips[i1].push_back(0);
            }
        }
    }
}