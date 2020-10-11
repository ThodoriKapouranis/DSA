#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include "hash.h"
#include "heap.h"
#include "graph.h"

graph::graph(){
}

// If ID not in hashtable yet, going to create a vertex class. adds the vertex id to our hashtable so we do not repeat it. if forDijkstra==true, then the distance is set to 1,000,000,000 approx inf. Add to heap.
//
//ERROR CODES
//100         ALREADY EXISTS
//0           COMPLETE
int graph::addVertex(std::string id, bool forDijkstra){
  if (vertices.contains(id)){
    return 100;
  }
  
  else{
    vertex temp;
    vertex* tempPointer;
    int tempDist;
    if (forDijkstra)
      tempDist=1000000000;
    else 
      tempDist=0;
    
    temp.id=id;
    temp.dist=tempDist;
    data.push_back(temp);
    tempPointer=&data.back();
    vertices.insert(id,tempPointer);
    distances.insert(id,tempDist,tempPointer);
    return 0;
  }
};

// If ID is present in hashtable, add the edge to the adjacency list of the former vector.
int graph::addEdge(std::string from, std::string to, int weight){
  for (std::list<vertex>::iterator it=data.begin(); it != data.end(); ++it){
    if ( it->id == from ){
      struct edge tempEdge;
      bool found;
      tempEdge.dest = static_cast<vertex *>(vertices.getPointer(to, &found));
      tempEdge.weight=weight;
      it->adjacency.push_back(tempEdge);
      return 0;
    }
  }
  return 1;
};

bool graph::hasPath(graph::vertex cur){
  if(cur.dist==1000000000) return false;
  else return true;
}

std::string graph::findPath(std::string source, graph::vertex cur){
  std::string toReturn="]";
  if (cur.id!=source) toReturn= ", " + cur.id + toReturn;
  while(cur.path->id!=source){
    toReturn = ", "+cur.path->id + toReturn;
    cur=*(cur.path);
  }
  toReturn = "["+source+toReturn;
  return toReturn;
}

int graph::dijkstra(std::string source, std::string fileName){
  distances.setKey(source,0);
  bool found;
  vertex* srcP =static_cast<vertex *>(vertices.getPointer(source,&found));
  srcP->dist=0;
  srcP->path=srcP;

  while (distances.returnFilled()!=0){
    void* tmpP;
    int tempKey;
    distances.deleteMin(nullptr,&tempKey,&tmpP);
    vertex* curVP = static_cast<vertex *>(tmpP); //current vector pointer
    curVP->found=true;
    for (auto i: curVP->adjacency){
      int newDistance = curVP->dist + i.weight;
      if (i.dest->found==false && (i.dest->dist >= newDistance)){
        i.dest->dist = newDistance;
        i.dest->path = curVP;
        distances.setKey(i.dest->id,newDistance);
      }
    }
  }

  std::ofstream outputFile;
  outputFile.open(fileName);
  for (auto i: data){
    if (hasPath(i))
      outputFile<<i.id<<": "<<i.dist<<" "<< findPath(source,i) <<std::endl;
    else
      outputFile<<i.id<<": "<<"NO PATH"<<std::endl;

  }
  return 0;
};