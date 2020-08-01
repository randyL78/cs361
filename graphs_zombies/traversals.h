#ifndef TRAVERSALS
#define TRAVERSALS


#include "graph.h"
#include <algorithm>
#include <queue>


template <typename Action>
void depthFirstTraversal (Graph& dg, const Vertex& start,
		Action doSomethingWith)
{
	auto allVertices = vertices(dg);
	unsigned n = std::distance(allVertices.first, allVertices.second);
	bool* visited = new bool[n];
	std::fill_n (visited, n, false);
	depthFirstTraversal (dg, start, visited, doSomethingWith);
	delete [] visited;
}



template <typename Action>
void breadthFirstTraversal (const Graph& g,
		const Vertex& start,
		Action doSomethingWith)
{
	using namespace std;

	queue<Vertex, list<Vertex> > q;

	auto allVertices = vertices(g);
	unsigned n = distance(allVertices.first, allVertices.second);
	bool* visited = new bool[n];
	fill_n (visited, n, false);

	q.push (start);
	visited[start] = true;;
	while (!q.empty())
	{
		Vertex v = q.front();
		q.pop();
		doSomethingWith(v);
		auto outgoing = out_edges(v,g);
		for (auto e = outgoing.first; e != outgoing.second; ++e)
		{
			Vertex w = target(*e, g);
			if (!visited[w])
			{
				q.push (w);
				visited[w] = true;
			}
		}
	}
	delete [] visited;
}


template <typename Action>
void depthFirstTraversal (Graph& dg, Vertex v, bool* visited, Action doSomethingTo)
{
	using namespace boost;

	visited[v] = true;
	doSomethingTo(v);
	auto edgeRange = out_edges(v, dg);
	for (auto e = edgeRange.first;
			e != edgeRange.second; ++e)
	{
		Vertex w = target(*e, dg);
		if (!visited[w])
			depthFirstTraversal (dg, w, visited, doSomethingTo);
	}
}

#endif
