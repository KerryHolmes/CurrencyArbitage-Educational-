#ifndef ARBITAGE_HPP
#define ARBITAGE_HPP

#include "digraph.hpp"
#include <iostream>
#include <climits>
#include <cmath>

#define inf = std::numeric_limits<double>::infinity();

template<typename G>
struct currency_arbitrage
{
	using vertex = origin::vertex_t;
	using edge = origin::edge_t;

	currency_arbitrage(G& g)
	:graph(g), distance(graph.num_vertices(), inf), parens(graph.num_vertices())
	{}

	void operator()()
	{
		auto distance = origin::vertex_label(distances);
		auto paren = origin::vertex_label(parens);

		for(vertex_t v : graph.vertices())
			parent(v) = v;

    for(edge e : graph.edges_)
			graph.weight(e) = -1 * (std::log(graph.weight(e)));

    BFSP(distance, paren);

    origin::print_digraph<G> print(std::cout, graph);
    print();

    for(auto elem : distances)
     std::cout << elem << std::endl;

    for(auto elem : parens)
     std::cout << elem << std::endl;

	}

template<typename Lable1, typename Lable2>
void BFSP(Lable1 distance, Lable2 paren)
{
	for (int i = 1; i < graph.num_vertices(); ++i)
	{
		for (edge e : graph.edges_())
		{
			relax(graph.source(e), graph.target(e), e);
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

G graph;
std::vector<int> distances;
std::vector<vertex> parens; //Batman doesn't has any :(

}

#endif
