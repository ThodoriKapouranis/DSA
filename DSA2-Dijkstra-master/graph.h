#ifndef _GRAPH_H
#define _GRAPH_H
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "hash.h"
#include "heap.h"

class graph{
  
  public:
    class vertex;
    struct edge{
      vertex* dest;
      int weight; 
    };

    class vertex{
      public:
        std::string id;
        int dist;
        vertex* path {nullptr};
        std::list<edge> adjacency; // [ [v2*,6], [v3*,2] ] etc
        bool found {false};
    };
    
    graph();
    int addVertex(std::string id, bool forDijkstra = false);
    int addEdge(std::string from, std::string to, int weight);
    int dijkstra(std::string source, std::string fileName);

    //rendering functions
    bool hasPath(vertex cur);
    std::string findPath(std::string source, vertex cur);

  std::list<vertex> data;
  hashTable vertices = hashTable(1000); //to figure out uniqueness
  heap distances = heap(1000); //use deletemin to quickly figure out
};


#endif