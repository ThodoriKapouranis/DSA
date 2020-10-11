#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include "graph.h"

using namespace std;

int main(){
  graph dirGraph;
  string INPUT_FILE;
  cout << "Enter input file name: ";
  cin >> INPUT_FILE;

  string source;
  cout << "Which source vertex?: ";
  cin >> source;

  string OUTPUT_FILE;
  cout << "Enter output file name: ";
  cin >> OUTPUT_FILE;

  string line, vfrom, vto;
  int dist;     // xx xx 30

  ifstream file;
  ofstream outputFile;

  file.open(INPUT_FILE);
  while (getline(file, line)){
    istringstream iss(line);
    iss >> vfrom >> vto >> dist;
    dirGraph.addVertex(vfrom, true);
    dirGraph.addVertex(vto, true);
    dirGraph.addEdge(vfrom,vto,dist);
  };
  
  clock_t t0=clock();
  dirGraph.dijkstra(source,OUTPUT_FILE);
  clock_t t1=clock();
  double timeDiff = ((double) (t1 - t0)) ;
  cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;
}