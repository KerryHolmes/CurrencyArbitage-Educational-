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
void 
BFSP(vertex s, Lable1 distance, Lable2 paren)
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
void 
relax(vertex u, vertex v, edge e, Lable1 distance, Lable2 paren)
{
	if (distance(v) > distance(u) + graph.weight(e))
	{
		distance(v) = distance(u) + graph.weight(e);
		paren(v) = u;
	}
}

template<typename Label>
bool
check_negative_cycles(Label distance)
{
	for(auto e : graph.edges())
	 if(distance(graph.target(e)) > distance(graph.source(e)) + graph.weight(e))
		 return true;
	return false; 
}

template<typename Lable1, typename Lable2>
std::vector<vertex>
trace_cycle(vertex s, Lable1 color, Lable2 paren)
{
   std::vector<vertex> cycle;
   while(!color(s))
	   {
		   cycle.push_back(s);
		   color(s) = 1;
		   s = paren(s);
	   }
	   cycle.push_back(s);
	   return cycle;
}

std::vector<vertex>
operator()()
{
   auto distance = origin::vertex_label(distances);
   auto paren = origin::vertex_label(parens);
   auto s = graph.add_vertex("Source");

	for(auto v : graph.vertices())
	 if(v != s)
	   graph.add_edge(s, v, 0);

    for(auto e : graph.edges())
	   graph.weight(e) = -1 * (std::log(graph.weight(e)));

    BFSP(s, distance, paren);
    
	if(check_negative_cycles(distance))
	{
       std::cout << "Arbitrage opportunity found!" << std::endl;
	   std::vector<int> visited(graph.num_vertices(), 0);
	   auto color = origin::vertex_label(visited);

	   auto cycle = trace_cycle(s, color, paren);

	   std::cout << "The cycle is: " << std::endl;
	   for(int i = 0; i < cycle.size() ; ++i)
	     std::cout << cycle[i] << std::endl;
	   std::cout << cycle[0] << std::endl;

	   return cycle;
	}
	else
	{
		std::cout << "There is no opportunity for arbitrage." << std::endl;
		return std::vector<vertex>();
	}
    

}

G graph;
std::vector<double> distances;
std::vector<vertex> parens; //Batman doesn't has any :(

};

#endif