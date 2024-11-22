#include <iostream>
#include "graph.hpp"
#include "priorityQueue.hpp"

int main() {
    // AdjList g1;

    // g1.addVertex("v1");
    // g1.addVertex("v2");
    // g1.addVertex("v3");
    // g1.addVertex("v4");

    // g1.addEdge("v1", "v2", 1);
    // g1.addEdge("v1", "v3", 2);
    // g1.addEdge("v2", "v3", 3);
    // g1.addEdge("v3", "v4", 4);

    // g1.printAll();
    // std::cout << std::endl;

    // g1.removeEdge("v1", "v2");

    // g1.printAll();
    // std::cout << std::endl;

    // g1.removeVertex("v3");

    // g1.printAll();
    // std::cout << std::endl;

    // g1.removeVertex("v1");

    // g1.printAll();
    // std::cout << std::endl;

    priorityQueue PQ;

    PQ.addElement("hello", 125);
    PQ.addElement("bye", 25);
    PQ.addElement("greetings", 200);

    std::cout << PQ.getFrontStr() << " " << PQ.getFrontVal() << std::endl;

    PQ.removeFront();

    std::cout << PQ.getFrontStr() << " " << PQ.getFrontVal() << std::endl;

    PQ.removeFront();

    std::cout << PQ.getFrontStr() << " " << PQ.getFrontVal() << std::endl;

    PQ.removeFront();

    return 0;
}