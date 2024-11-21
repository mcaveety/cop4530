#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    class Vert temp(label);
    graph.push_back(temp);
}

void AdjList::addEdge(std::string label1, std::string label2, unsigned long weight) {
    std::vector<Vert>::iterator it1;
    std::vector<Vert>::iterator it2;
    it1 = graph.begin();
    it2 = graph.begin();

    // Puts iterators at Vertex or end
    while (it1 != graph.end() && it1->name != label1) {
        it1++;
    }
    while (it2 != graph.end() && it2->name != label2) {
        it2++;
    }

    // Returns if either Vertex not found
    if (it1 == graph.end() || it2 == graph.end()) {
        return;
    }

    // First neighbor of both Vertices
    Neighbor *temp1 = it1->first;
    Neighbor *temp2 = it2->first;

    // Puts temp1 and temp2 at last Neighbor or at nullptr (if no neighbors)
    if (temp1 != nullptr) {
        while (temp1->next != nullptr) {
            if (temp1->name == label2) {
                return;
            }
            temp1 = temp1->next;
        }
        if (temp1->name == label2) {
            return;
        }
    }
    if (temp2 != nullptr) {
        while (temp2->next != nullptr) {
            if (temp2->name == label1) {
                return;
            }
            temp2 = temp2->next;
        }
        if (temp2->name == label1) {
            return;
        }
    }

    // Creates Neighbor class objects for edges
    Neighbor newEdge1(label2, weight);
    Neighbor newEdge2(label1, weight);

    // Places edges in AdjList
    if (temp1 != nullptr) {
        temp1->next = &newEdge1;
    }
    else {
        it1->first = &newEdge1;
    }
    if (temp2 != nullptr) {
        temp2->next = &newEdge2;
    }
    else {
        it2->first = &newEdge2;
    }

//     // Find first Vertex or go to end of the AdjList
//     while (it != graph.end() && it->name != label1) {
//         it++;
//     }

//     std::cout << "gets through finding vert" << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//     std::cout << "this is vert: " << it->name << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//     // If first Vertex found, add edge
//     if (it != graph.end()) {
//         // First neighbor
//         Neighbor *temp = it->first;

//         std::cout << "does this print?" << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//         // Go to end of neighbors
//         while (temp != nullptr && temp->next != nullptr) {
//             // Ensures edge does not already exist

//             std::cout << "this is a neighbor: " << temp->name << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//             if (temp->name == label2) {
//                 return;
//             }
//             temp = temp->next;
//         }

//         // Ensures last neighbor does not hold edge being added
//         if (temp != nullptr && temp->name == label2) {
//                 return;
//             }

//         // newEdge goes to end of neighbors
//         Neighbor newEdge;
//         if (temp != nullptr) {
//             temp->next = &newEdge;
//         }
//         else {
//             it->first = &newEdge;
//         }

//         newEdge.name = label2;
//         newEdge.weight = weight;
//     }
//     else {
//         return; // FIX CASE WHERE ONE EDGE ADDED AND OTHER RETURNS 
//     }

// it = graph.begin();

//     // Find first Vertex or go to end of the AdjList
//     while (it != graph.end() && it->name != label2) {
//         it++;
//     }

//     // If first Vertex found, add edge
//     if (it != graph.end()) {
//         // First neighbor
//         Neighbor *temp = it->first;

//                 // Go to end of neighbors
//         while (temp != nullptr && temp->next != nullptr) {
//             // Ensures edge does not already exist

//             std::cout << "this is a neighbor: " << temp->name << std::endl; // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//             if (temp->name == label1) {
//                 return;
//             }
//             temp = temp->next;
//         }

//         // Ensures last neighbor does not hold edge being added
//         if (temp != nullptr && temp->name == label1) {
//                 return;
//             }

//         // newEdge goes to end of neighbors
//         Neighbor newEdge;
//         if (temp != nullptr) {
//             temp->next = &newEdge;
//         }
//         else {
//             it->first = &newEdge;
//         }

//         newEdge.name = label1;
//         newEdge.weight = weight;
//     }
//     else {
//         return;
//     }
}

void AdjList::removeEdge(std::string label, std::string label2) {
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

void AdjList::printAllVert() {
    std::vector<Vert>::iterator it;
    it = graph.begin();

    while (it != graph.end()) {
        std::cout << it->name << std::endl;
        it++;
    }
}

void AdjList::printAll() {
    std::vector<Vert>::iterator it;
    it = graph.begin();

    while (it != graph.end()) {
        std::cout << it->name << ": ";

        Neighbor *temp = it->first;
        while (temp != nullptr) {
            std::cout << temp->name << " ";
            temp = temp->next;
        }
        std::cout << std::endl;

        it++;
    }
}