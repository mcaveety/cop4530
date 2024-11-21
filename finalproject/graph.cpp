#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    class Vert temp(label);
    graph.push_back(temp);
}

void AdjList::removeEdge(std::string label, std::string label2){
    std::vector<Vert>::iterator it;
    it = graph.begin();

    // Look through AdjList for both labels 
    while (it != graph.end()){
        
        // If name of iterator is first label, delete the connection to the other label 
        if (it->name == label){
            AdjList::Neighbor *next_neighbor = it->first;
            AdjList::Neighbor *prev_neighbor = nullptr;

            // Iterate over the Neighbors to find the connection 
            while(next_neighbor != nullptr){

                // If Neighbor's name matches the other label, get rid of it and re-link other neighbors 
                if (next_neighbor->name == label2){
                    if (next_neighbor == it->first){
                        it->first = next_neighbor->next;
                        delete next_neighbor;
                        break;
                    }

                    prev_neighbor->next = next_neighbor->next; 
                    delete next_neighbor;
                    break;
                }

                // If label has not been found yet, move to next neighbor
                prev_neighbor = next_neighbor;
                next_neighbor = next_neighbor->next;
            }

        // If name of iterator iss the second label, delete the connection to the other label 
        } else if (it->name == label2){
            AdjList::Neighbor *next_neighbor = it->first;
            AdjList::Neighbor *prev_neighbor = nullptr;

            // Iterate over the Neighbors to find the connection 
            while(next_neighbor != nullptr){

                // If Neighbor's name matches the other label, get rid of it and re-link other neighbors 
                if (next_neighbor->name == label){
                    if (next_neighbor == it->first){
                        it->first = next_neighbor->next;
                        delete next_neighbor;
                        break;
                    }

                    prev_neighbor->next = next_neighbor->next; 
                    delete next_neighbor;
                    break;
                }

                // If label has not been found yet, move to next neighbor
                prev_neighbor = next_neighbor;
                next_neighbor = next_neighbor->next;
            }
        }

        it++;
    }
}

void AdjList::removeVertex(std::string label) {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    
    // Look through AdjList for label 
    while (it != graph.end()) {

        // If label's found, delete all of its neighbors (if any) and then delete the Vertex
        if (it->name == label){
            while (it->first != nullptr){
                AdjList::Neighbor* temp = it->first; 
                it->first = it->first->next;
                delete temp;
            }
            graph.erase(it);

        // If label is not found, delete this Vertex's connection to the target
        } else {
            AdjList::removeEdge(it->name, label);
        }

        it++;
    }
}