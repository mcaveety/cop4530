#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    class Vert temp(label);
    graph.push_back(temp);
}

void AdjList::addEdge(std::string label1, std::string label2, unsigned long weight) {
    std::vector<Vert>::iterator it;
    it = graph.begin();

    // Find first Vertex or go to end of the AdjList
    while (it != graph.end() && it->name != label1) {
        it++;
    }

    // If first Vertex found, add edge
    if (it != graph.end()) {
        // First neighbor
        Neighbor *temp = it->first;

        // Go to end of neighbors
        while (temp->next != nullptr) {
            if (temp->name == label2) {
                return;
            }
            temp = temp->next;
        }

        if (temp->name == label2) {
                return;
            }

        // newEdge goes to end of neighbors
        Neighbor newEdge;
        temp->next = &newEdge;

        newEdge.name = label2;
        newEdge.weight = weight;
    }
    else {
        return;
    }

it = graph.begin();

    // Find first Vertex or go to end of the AdjList
    while (it != graph.end() && it->name != label2) {
        it++;
    }

    // If first Vertex found, add edge
    if (it != graph.end()) {
        // First neighbor
        class Neighbor *temp = it->first;

        // Go to end of neighbors
        while (temp->next != nullptr) {
            if (temp->name == label1) {
                return;
            }
            temp = temp->next;
        }

        if (temp->name == label1) {
                return;
            }

        // newEdge goes to end of neighbors
        Neighbor newEdge;
        temp->next = &newEdge;

        newEdge.name = label1;
        newEdge.weight = weight;
    }
    else {
        return;
    }
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