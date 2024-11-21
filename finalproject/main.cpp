#include <iostream>
#include "graph.hpp"

int main() {
    AdjList g1;

    g1.addVertex("v1");
    g1.addVertex("v2");
    g1.addVertex("v3");
    g1.addVertex("v4");

    g1.addEdge("v1", "v2", 1);
    g1.addEdge("v1", "v3", 2);
    g1.addEdge("v2", "v3", 3);
    g1.addEdge("v3", "v4", 4);

    // g1.printAll();
    // std::cout << std::endl;

    // g1.removeEdge("v1", "v2");

    g1.printAll();
    std::cout << std::endl;

    g1.~AdjList();

    g1.printAll();
    std::cout << std::endl;

    // g1.removeVertex("v3");

    // g1.printAll();
    // std::cout << std::endl;

    // g1.removeVertex("v1");

    // g1.printAll();
    // std::cout << std::endl;

    return 0;
}