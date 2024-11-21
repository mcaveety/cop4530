#include <iostream>
#include "graph.hpp"

int main() {
    AdjList g1;

    g1.addVertex("v1");
    g1.addVertex("v2");

    g1.addEdge("v1", "v2", 1);

    g1.printAll();

    return 0;
}