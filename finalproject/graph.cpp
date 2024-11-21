#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    class Vert temp(label);
    graph.push_back(temp);
}

void AdjList::removeEdge(std::string label, std::string label2){

}

void AdjList::removeVertex(std::string label) {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    
    while (it != graph.end()) {
        /*if (it->name == label) {
            graph.erase(it);
            return;
        }*/
        AdjList::Neighbor *next_neighbor = it->first;
        AdjList::Neighbor *prev_neighbor = nullptr;
        while (next_neighbor != nullptr){
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
            prev_neighbor = next_neighbor;
            next_neighbor = next_neighbor->next;
        }

        if (it->name == label){
            while (it->first != nullptr){
                AdjList::Neighbor* temp = it->first; // A -> B -> C -> D
                it->first = it->first->next;
                delete temp;
            }
            graph.erase(it);
        }

        it++;
    }
}