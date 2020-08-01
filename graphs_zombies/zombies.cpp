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

void readGraph(istream& in, Graph& g)
{
  //*** Insert your code here to read and set up the graph.
}


void solve (const Graph& g)
{
	int longestDelay = 0;
  //*** Compute and print the longest amount of time we can delay the
  //*** zombies with a single barrier.
	cout << longestDelay << endl;
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
