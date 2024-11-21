#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "graphbase.hpp"

class AdjList {
private:
    /*class Vert {
    public:
        Vert(std::string str) { name = str; }
        std::string name;
        bool explored = false;
        int distance = 999999;
        Vert *lastVisted = nullptr;
        Neighbor* first;
    };*/

    class Neighbor {
    public:
        std::string name;
        int weight;
        Neighbor *next = nullptr;
        Neighbor();
    };
    class Vert { 
    public:
        Vert(std::string str) { name = str; }
        std::string name;
        bool explored = false;
        int distance = 999999;
        Vert *lastVisted = nullptr;
        Neighbor* first = nullptr;
    };

    std::vector<Vert> graph;
    int nextVertIndex = 0;

public:
    void addVertex(std::string label);

    void removeVertex(std::string label);

    void addEdge(std::string label1, std::string label2, unsigned long weight);

    void removeEdge(std::string label1, std::string label2);

    unsigned long shortestPath(std::string startLabel, std::string endLabel,
    std::vector<std::string> &path);
};

#endif