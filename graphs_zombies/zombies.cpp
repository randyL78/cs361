#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.h"
#include "graphUtils.h"
#include "traversals.h"


using namespace std;

int nV;
int nE;
int delay;

std::unordered_map<Edge, int, boost::hash<Edge> > distances;

/**
 * Finds the total weight to travel the shortest weighted path
 * @tparam Graph
 * @tparam WeightMap
 * @param g
 * @param start
 * @param finish
 * @param weight
 * @return
 */
template <typename Graph, typename WeightMap>
int findWeightedShortestDistance(
        const Graph& g,
        Vertex start,
        Vertex finish,
        WeightMap& weight)
{
  int distance = 0;
  vector<Vertex> shortestPath = findWeightedShortestPath(g, start, finish, weight);
  int size = shortestPath.size();

  for(int i = 0; i < size - 1; ++i)
  {
    auto e = boost::edge(shortestPath[i], shortestPath[i + 1], g).first;
    distance += weight[e];
  }

  return distance;
}

void readGraph(istream& in, Graph& g)
{
  // read the first line of input to set global variables
  in >> nV >> nE >> delay;

  /* create the actual graph */
  // add the edges. Per the Boost::Graph docs, vertices will be added
  // automatically if they don't exist.
  for (int i = 0; i < nE; ++i)
  {
    int v1;
    int v2;
    int minutes;

    in >> v1 >> v2 >> minutes;

    Edge e = boost::add_edge(v1, v2, g).first;
    distances.insert({e, minutes});
  }
}


void solve (const Graph& g)
{
//	int longestDelay = 0;
  //*** Compute and print the longest amount of time we can delay the
  //*** zombies with a single barrier.
  auto vertexRange = vertices(g);

  // find the shortest path with no barricade. Using findWeightedShortestPath
  // instead of findWeightedShortestDistance because we will use this to find
  // best places to add barricades.
  vector<Vertex> baseShortestPath = findWeightedShortestPath(
          g,
          *vertexRange.first,
          *vertexRange.second - 1,
          distances);

  // track the current shortest distance. Setting it impossibly high
  // to guarantee first pass changes it.
  int shortestDistanceSoFar = INT_MAX;
  int longestDistanceSoFar = 0;

  // We know that the barricade is going to do its best
  // by being on the best path so loop through best path
  // and place barricade at each edge in turn.
  int size = baseShortestPath.size();
  for(int i = 0; i < size - 1; ++i)
  {
    // get the edge to add barricade to
    auto edge = boost::edge(baseShortestPath[i],
            baseShortestPath[i + 1],
            g).first;


    // add the barricade delay
    distances[edge] += delay;

    int tempBestBath = findWeightedShortestDistance(
            g,
            *vertexRange.first,
            *vertexRange.second - 1,
            distances);

    cout << tempBestBath << endl;

    if (tempBestBath > longestDistanceSoFar)
      longestDistanceSoFar = tempBestBath;

    if(tempBestBath < shortestDistanceSoFar)
      shortestDistanceSoFar = tempBestBath;

    // remove the barricade delay
    distances[edge] -= delay;
  }

  cout << longestDistanceSoFar - shortestDistanceSoFar << endl;
// // All edges attempt
//  auto edgeRange = boost::edges(g);
//  for(auto edge = edgeRange.first; edge != edgeRange.second; ++edge)
//  {
//    // add the barricade delay
//    distances[*edge] += delay;
//
//    int tempBestBath = findWeightedShortestDistance(
//            g,
//            *vertexRange.first,
//            *vertexRange.second - 1,
//            distances);
//
//    cout << tempBestBath << endl;
//
//    if (tempBestBath > longestDistanceSoFar)
//      longestDistanceSoFar = tempBestBath;
//
//    if(tempBestBath < shortestDistanceSoFar)
//      shortestDistanceSoFar = tempBestBath;
//
//    // remove the barricade delay
//    distances[*edge] -= delay;
//  }
//  // calculate distance of shortest path
//  int baseShortestDistance = 0;
//  int size = baseShortestPath.size();
//
//  for (int i = 0; i < size - 1; ++i)
//  {
//    auto e = boost::edge(baseShortestPath[i],
//            baseShortestPath[i + 1],
//            g).first;
//    baseShortestDistance += distances[e];
//  }
//
//  // second loop through shortest path to place barricades.
//  for (int i = 0; i < size - 1; ++i)
//  {
//    auto edge = boost::edge(baseShortestPath[i],
//                         baseShortestPath[i + 1],
//                         g).first;
//
//    distances[edge] += delay;
//
//    int newShortestDistance =
//            findWeightedShortestDistance(
//                    g,
//                    *vertexRange.first,
//                    *vertexRange.second - 1,
//                    distances);
//
//    if(newShortestDistance - baseShortestDistance > longestDelay)
//      longestDelay = newShortestDistance - baseShortestDistance;
//
//    distances[edge] -= delay;
//  }
//	cout << longestDelay << endl;
}

int main (int argc, char** argv)
{
	Graph citymap;
	if (argc > 1)
	{
		ifstream in (argv[1]);
		readGraph (in, citymap);
	}
	else
	{
		readGraph (cin, citymap);
	}
	solve (citymap);
	return 0;

}
