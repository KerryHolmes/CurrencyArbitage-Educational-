#ifndef ARBITAGE_HPP
#define ARBITAGE_HPP

#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <limits>
#include <cmath>

template<typename G>
struct currency_arbitrage
{
	using vertex = origin::vertex_t;
	using edge = origin::edge_t;

	currency_arbitrage(G& g)
	:graph(g), 
	distances(graph.num_vertices(), std::numeric_limits<double>::infinity()), 
	parens(graph.num_vertices(), -1)
	{}

template<typename Lable1, typename Lable2>
void BFSP(vertex s, Lable1 distance, Lable2 paren)
{
    distance(s) = 0;
	for (int i = 1; i < graph.num_vertices(); ++i)
	{
		for (auto e : graph.edges())
		{
			relax(graph.source(e), graph.target(e), e, distance, paren);
		}
	}
}

template<typename Lable1, typename Lable2>
void relax(vertex u, vertex v, edge e, Lable1 distance, Lable2 paren)
{
	if (distance(v) > distance(u) + graph.weight(e))
	{
		distance(v) = distance(u) + graph.weight(e);
		paren(v) = u;
	}
}

void operator()()
{
   auto distance = origin::vertex_label(distances);
   auto paren = origin::vertex_label(parens);

    for(auto e : graph.edges())
			graph.weight(e) = -1 * (std::log(graph.weight(e)));

	auto s = g.add_vertex("Source");
	for(auto v : graph.vertices())
	   graph.add_edge(s, v, 0);

    BFSP(s, distance, paren);
    
    origin::print_digraph<G> print(std::cout, graph);
    print();

    for(auto elem : distances)
     std::cout << elem << std::endl;

    for(auto elem : parens)
     std::cout << elem << std::endl;

	}

G graph;
std::vector<double> distances;
std::vector<vertex> parens; //Batman doesn't has any :(

};

#endif