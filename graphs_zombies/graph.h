/*
 * graph.h
 *
 *  Created on: Jul 9, 2020
 *      Author: zeil
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>




typedef boost::adjacency_list<boost::listS, // store edges in lists
		                      boost::vecS, // store vertices in a vector
							  boost::bidirectionalS // a directed graph, with in_edges
							  // no bundled properties on vertices & edges
							  >
                                Graph;
typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;


#endif /* GRAPH_H_ */
