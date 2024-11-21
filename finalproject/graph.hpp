#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "graphbase.hpp"
#include "HeapQueue.hpp"

class AdjList {
private:
    class Neighbor {
    public:
        std::string name;
        int weight;
        Neighbor *next = nullptr;
        Neighbor(std::string name, int weight) { this->name = name, this->weight = weight; }
    };
    class Vert { 
    public:
        Vert(std::string str) { name = str; }
        std::string name;
        bool explored = false;
        int distance = -1;
        Vert *lastVisted = nullptr;
        Neighbor* first = nullptr;
    };
    class HeapNode {
        public:
        HeapNode(std::string name, unsigned long pathValue) { this->name = name, this->pathValue = pathValue; }
        std::string name; 
        unsigned long pathValue;

        class Compare {
            public:
            Compare(bool lessThan = true) : lessThan(lessThan) {};
            bool operator()(const HeapNode &n1, const HeapNode &n2) const;
            bool operator()(const HeapNode *n1, const HeapNode *n2) const;
            private:
            bool lessThan;
        };

    };
    std::vector<Vert> graph;
    

public:
    void addVertex(std::string label);

    void removeVertex(std::string label);

    void addEdge(std::string label1, std::string label2, unsigned long weight);

    void removeEdge(std::string label1, std::string label2);

    unsigned long shortestPath(std::string startLabel, std::string endLabel,
    std::vector<std::string> &path);

    void printAllVert();

    void printAll();

    ~AdjList();
};

#endif