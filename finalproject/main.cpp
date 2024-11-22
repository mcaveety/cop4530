#include <iostream>
#include "graph.hpp"

int main() {
    AdjList g1;

    // g1.addVertex("v1");
    // g1.addVertex("v2");
    // g1.addVertex("v3");
    // g1.addVertex("v4");

    // g1.addEdge("v1", "v2", 1);
    // g1.addEdge("v1", "v3", 2);
    // g1.addEdge("v2", "v3", 3);
    // g1.addEdge("v3", "v4", 4);

    // // g1.printAll();
    // // std::cout << std::endl;

    // // g1.removeEdge("v1", "v2");

    // g1.printAll();
    // std::cout << std::endl;

    // // g1.~AdjList();

    // g1.printAll();
    // std::cout << std::endl;

    // // g1.removeVertex("v3");

    // // g1.printAll();
    // // std::cout << std::endl;

    // // g1.removeVertex("v1");

    // // g1.printAll();
    // // std::cout << std::endl;

    // std::vector<std::string> vertices1 = {"1","2","3","4","5","6"};
    // std::vector<std::tuple<std::string, std::string, unsigned long>> edges1 = {{"1","2",7}, {"1","3",9}, {"1","6",14}, {"2","3",10}, {"2","4",15}, {"3","4",11}, {"3","6",2}, {"4","5",6}, {"5", "6", 9}};

    g1.addVertex("A");
    g1.addVertex("B");
    g1.addVertex("C");
    g1.addVertex("D");
    g1.addVertex("E");
    g1.addVertex("F");
    g1.addVertex("G");
    g1.addVertex("H");

    g1.addEdge("A", "B", 1);
    g1.addEdge("B", "E", 3);
    g1.addEdge("A", "C", 10);
    g1.addEdge("C", "D", 7);
    g1.addEdge("E", "D", 2);
    g1.addEdge("D", "F", 3);
    g1.addEdge("D", "G", 8);
    g1.addEdge("F", "G", 2);
    g1.addEdge("G", "H", 1);

    std::vector<std::string> path;
    unsigned long shortestDist = g1.shortestPath("A", "C", path);
    std::vector<std::string>::iterator pathIt = path.begin();
    std::cout << "Shortest path to end is: " << shortestDist << "\n";
    while(pathIt != path.end()){
        std::cout << *pathIt << " ";
        pathIt++;
    }

    return 0;
}