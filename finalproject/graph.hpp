#ifndef GRAPH_H
#define GRAPH_H

// Include iostream and necessary header files 
#include <iostream>
#include "graphbase.hpp"
#include "HeapQueue.hpp"

// Graph implementation using an Adjacency List structure. Vertices are defined through the Vert class,
// edges are defined through the Neighbor class, and the nodes required for the algorithm's implementation 
// are defined through the HeapNode class. Contains an instance of the AdjList to be accessed by members. 
class AdjList {
private:
    // Graph Edge implementation; contains the destination of an edge, its weight, and a pointer to the next edge in AdjList
    class Neighbor {
    public:
        std::string name;
        int weight;
        Neighbor *next = nullptr;
        Neighbor(std::string name, int weight) { this->name = name, this->weight = weight; }
    };
    // Graph Vertex implementation; contains a name, a boolean determining if an estimate has been given, a boolean determining 
    // if this vertex has been explored, a distance estimate for shortest distance, a pointer back to the Vertex that created the 
    // shortest path to it, and a pointer to the first edge of the Vertex
    class Vert { 
    public:
        Vert(std::string str) { name = str; }
        std::string name;
        bool hasEstimate = false;
        bool explored = false;
        unsigned long distance;
        Vert *lastVisted = nullptr;
        Neighbor* first = nullptr;
    };
    // minHeap node implementation; contains a name, a value for the shortest path to the name, and a class definition for the 
    // comparator used to sort and maintain the minHeap
    class HeapNode {
        public:
        HeapNode(std::string name, unsigned long pathValue) { this->name = name, this->pathValue = pathValue; }
        std::string name; 
        unsigned long pathValue;

        // Comparator implementation for the minHeap; contains a bool to store the result of comparisons and two function 
        // definitions that define how HeapNodes should be compared to each other
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
    
// Function declarations 
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