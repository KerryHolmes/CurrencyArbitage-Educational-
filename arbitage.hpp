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

template<typename Lable>
bool
check_negative_cycles()
{
	for(auto e : graph.edges())
	 if(distance(graph.target(e)) > distance(graph.source(e)) + graph.weight(e))
		 return true;
	return false; 
}

void operator()()
{
   auto distance = origin::vertex_label(distances);
   auto paren = origin::vertex_label(parens);
   vertex s = 0;

    for(auto e : graph.edges())
	   graph.weight(e) = -1 * (std::log(graph.weight(e)));

    BFSP(s, distance, paren);
    
	if(check_negative_cycles())
	{
       std::cout << "Arbitrage opportunity found!" << std::endl;
	   std::vector<vertex> cycle;
	   std::vector<bool> rainbow(graph.num_vertices(), false);
	   auto color = vertex_label(rainbow);

	   while(!color(s))
	   {
		   cycle.push_back(s);
		   s = paren(s);
		   color(s) = true;
	   }
	   for(int i = 0; i < cycle.size() ; ++i)
	     std::cout << cycle[i] << std::endl;
	}
	else
	{
		std::cout << "There is no opportunity for arbitrage." << std::endl;
		return;
	}
    

}

G graph;
std::vector<double> distances;
std::vector<vertex> parens; //Batman doesn't has any :(

};

#endif