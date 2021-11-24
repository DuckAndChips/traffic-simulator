#include "Traffic_Model.h"

#include <iostream>
using namespace std;

void Traffic_Model::trip_assignment(){
    
    /// Error checking
    if(error_checking()){
        return;
        //cerr<< "Error in Traffic Model Data Member"<<endl;
        //exit(-1);
    }

    /// loops
    std::vector<Node*>::const_iterator p;
    int i = 0;
    for(p = origin.begin(); p != origin.end(); ++p, ++i){
        std::vector<Node*>::const_iterator q;
        int j = 0;
        for(q = destination.begin(); q != destination.end(); ++q, ++j){
            int trips = OD_Matrix[i][j];
            std::vector<std::vector<Node::Direction>> paths = get_all_paths(*p, *q);
            for(int k = 0; k < trips; ++k){
                load_traffic(*p,paths);  
            }                    
        }
    }
}

std::vector<std::vector<Node::Direction>> Traffic_Model::get_all_paths(Node* start_pt, Node* end_pt){

}

void Traffic_Model::load_traffic(Node* start_pt, const std::vector<std::vector<Node::Direction>> &paths){

}

double Traffic_Model::get_travel_time(Node* start_pt, const std::vector<Node::Direction> &path){

}

bool Traffic_Model::error_checking() const{
    int origin_size = origin.size();
    int destination_size = destination.size();

    /// check if the OD info are empty or not
    if(origin_size == 0 || destination_size == 0) return true;
    if(origin_size != OD_Matrix.size()) return true;

    /// check the no of rows and columns matches with origin's size and destination's size or not
    for(int i = 0; i<origin_size ; ++i){
        if(OD_Matrix[i].size() != destination_size) return true;
    }

    return false;
}

bool Traffic_Model::error_checking(Node* start_pt, const Node* end_pt, const std::vector<std::vector<Node::Direction>> &paths) const{
    for(std::vector<std::vector<Node::Direction>>::const_iterator p = paths.begin();
        p != paths.end(); ++p){
        Node* temp = start_pt;
        for(std::vector<Node::Direction>::const_iterator q = p->begin();
            q != p->end(); ++q){
            temp = temp->get_neighboring_building(*q);        
        }
        if(temp != end_pt) {
            cerr<< "Error in Traffic Model Data Member"<<endl;
            exit(-1);
            return true;
        }
    }
    return false;
}

