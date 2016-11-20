#ifndef ARBITAGE_HPP
#define ARBITAGE_HPP

#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <limits>
#include <cmath>

template<typename G, typename T = double>
struct currency_arbitrage
{
	using vertex = origin::vertex_t;
	using edge = origin::edge_t;

	currency_arbitrage(G& g, T max = 1000000)
	:graph(g),
	distances(graph.num_vertices() + 1, max),
	parens(graph.num_vertices() + 1, -1)
	{}

	template<typename Lable1, typename Lable2>
	void
		BFSP(vertex s, Lable1 distance, Lable2 paren)
	{
		distance(s) = 0;
		paren(s) = s;
		for (int i = 1; i < graph.num_vertices(); ++i)
		{
			for (auto e : graph.edges())
			{
				relax(graph.source(e), graph.target(e), e, distance, paren);
			}
		}
	}

	template<typename Lable1, typename Lable2>
	void
		relax(vertex u, vertex v, edge e, Lable1 distance, Lable2 paren)
	{
		if (distance(v) > distance(u) + graph.weight(e))
		{
			distance(v) = distance(u) + graph.weight(e);
			paren(v) = u;
		}
	}

	template<typename Lable1, typename Lable2, typename Lable3>
	std::vector<vertex>
		check_negative_cycles(Lable1 distance, Lable2 color, Lable3 paren)
	{
		for (auto e : graph.edges())
			if (distance(graph.target(e)) > distance(graph.source(e)) + graph.weight(e))
				return trace_cycle(graph.target(e), color, paren);
		return std::vector<vertex>();
	}

	template<typename Lable1, typename Lable2>
	std::vector<vertex>
		trace_cycle(vertex s, Lable1 color, Lable2 paren)
	{
		std::vector<vertex> cycle;
		while (!color(s))
		{
			cycle.push_back(s);
			color(s) = 1;
			s = paren(s);
		}
		return cycle;
	}

	std::vector<vertex>
		operator()()
	{
		auto distance = origin::vertex_label(distances);
		auto paren = origin::vertex_label(parens);
		auto s = graph.add_vertex("Source");

		for (auto e : graph.edges())
			graph.weight(e) = -1 * (std::log10(graph.weight(e)));

		for (auto v : graph.vertices())
			if (v != s)
				graph.add_edge(s, v, 0);

		BFSP(s, distance, paren);

		std::vector<int> visited(graph.num_vertices(), 0);
		auto color = origin::vertex_label(visited);

		auto cycle = check_negative_cycles(distance, color, paren);

		if (cycle.size() > 0)
		{
			std::cout << "The cycle is: " << std::endl;
			for (int i = 0; i < cycle.size(); ++i)
				std::cout << cycle[i] << std::endl;
			std::cout << cycle[0] << std::endl;

			return cycle;
		}
		else
		{
			std::cout << "There is no opportunity for arbitrage." << std::endl;
			return cycle;
		}


	}

	G graph;
	std::vector<T> distances;
	std::vector<vertex> parens; //Batman doesn't has any :(

};

#endif