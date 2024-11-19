#include <iostream>
#include "graph.hpp"

void AdjList::addVertex(std::string label) {
    class Vert temp(label);
    graph.push_back(temp);
}

void AdjList::removeVertex(std::string label) {
    std::vector<Vert>::iterator it;
    it = graph.begin();
    
    while (it != graph.end()) {
        if (it->name == label) {
            graph.erase(it);
        }
    }
}