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

    g1.addVertex("1");
    g1.addVertex("2");
    g1.addVertex("3");
    g1.addVertex("4");
    g1.addVertex("5");
    g1.addVertex("6");

    g1.addEdge("1", "2", 7);
    g1.addEdge("1", "3", 9);
    g1.addEdge("1", "6", 14);
    g1.addEdge("2", "3", 10);
    g1.addEdge("2", "4", 15);
    g1.addEdge("3", "4", 11);
    g1.addEdge("3", "6", 2);
    g1.addEdge("4", "5", 6);
    g1.addEdge("5", "6", 9);

    std::vector<std::string> path;
    unsigned long shortestDist = g1.shortestPath("1", "5", path);
    std::vector<std::string>::iterator pathIt = path.begin();
    std::cout << "Shortest path to end is: " << shortestDist << "\n";
    while(pathIt != path.end()){
        std::cout << *pathIt << " ";
        pathIt++;
    }

    return 0;
}