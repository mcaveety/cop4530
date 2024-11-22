#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    Vert *temp = new Vert(label);
    graph.push_back(*temp);
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

    // Creates Neighbor class objects for edges
    Neighbor *newEdge1 = new Neighbor(label2, weight);
    Neighbor *newEdge2 = new Neighbor(label1, weight);

    newEdge1->next = it1->first;
    newEdge2->next = it2->first;
    it1->first = newEdge1;
    it2->first = newEdge2;
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
            it--;
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
    if (graph.empty()) 
        return;

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

AdjList::~AdjList() {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    while (it != graph.end()) {
        while (it->first != nullptr) {
            Neighbor *temp = it->first;
            removeEdge(it->name, temp->name);
        }
        it++;
    }
    graph.clear();
}

bool AdjList::HeapNode::Compare::operator()(const HeapNode &n1, const HeapNode &n2) const
{
    return lessThan ? n1.pathValue < n2.pathValue : n1.pathValue >= n2.pathValue;
}

bool AdjList::HeapNode::Compare::operator()(const HeapNode *n1, const HeapNode *n2) const
{
  return operator()(*n1, *n2);
}

unsigned long AdjList::shortestPath(std::string startLabel, std::string endLabel, std::vector<std::string> &path){
    // If graph does not have any nodes in it, return a -1 for shortest path 
    if (graph.size() == 0){
        return -1;

    // If graph only has one node in it, return a 0 for shortest path 
    } else if (graph.size() == 1){
        return 0;
    }

    // Find the starting vertex in the adjacency list and set the shortest distance to it to 0 
    std::vector<Vert>::iterator curr = graph.begin();
    while (curr->name != startLabel){
        curr++;
    }
    curr->distance = 0;
    
    // Create the minHeap and insert the current shortest path into it with the name of the vertex 
    HeapQueue<HeapNode*, HeapNode::Compare> minHeap;

    // Loop until we reach the destination (endLabel) 
    while (curr->name != endLabel){
        curr->explored = true;

        // Update distance estimates to neighbors and put them on the minHeap
        Neighbor* currNeighbor = curr->first;
        unsigned long estimate = curr->distance + currNeighbor->weight;

        while (currNeighbor != nullptr){
            estimate = curr->distance + currNeighbor->weight;

            // Find the neighbor's vertex equivalent in AdjList 
            std::vector<Vert>::iterator neighborVert = graph.begin();
            while(neighborVert->name != currNeighbor->name){
                neighborVert++;
            }
            
            // If neighbor's best estimate is -1 or higher than our estimate, give it a new best estimate 
            if ((neighborVert->distance == -1) || (estimate < neighborVert->distance)){
                neighborVert->distance = estimate; 
                neighborVert->lastVisted = &(*curr);
            } 

            // Place estimate, whether best or not, in the minHeap
            HeapNode* newEntry = new HeapNode(currNeighbor->name, estimate);
            minHeap.insert(newEntry);

            currNeighbor = currNeighbor->next;
        }

        // Take the next shortest, unexplored distance estimate and name from the minHeap, remove it, and find the corresponding vertex
        bool notExplored = false;
        HeapNode* nextNode = minHeap.min();
        std::string nextName = nextNode->name;
        std::vector<Vert>::iterator findIt;

        // Assume that the corresponding vertex has already been explored until proven otherwise
        while (!notExplored){
            nextNode = minHeap.min();
            nextName = nextNode->name;
            findIt = graph.begin();

            while (findIt->name != nextName){
                findIt++;
            }
            if(findIt->explored){
                minHeap.removeMin();
                continue;
            } else{
                notExplored = true;
            }
        }

        // unsigned long nextValue = nextNode->pathValue;
        minHeap.removeMin();
        curr = findIt;
    }

    unsigned long totalDist = curr->distance;
    Vert* walkingPointer = &(*curr);
    std::vector<std::string> stack;
    while(walkingPointer != nullptr){
        stack.push_back(walkingPointer->name);
        walkingPointer = walkingPointer->lastVisted;
    }

    while(!stack.empty()){
        path.push_back(stack.back());
        stack.pop_back();
    }

    return totalDist;
}