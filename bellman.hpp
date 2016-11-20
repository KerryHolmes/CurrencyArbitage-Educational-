#ifndef BELLMAN_HPP
#define BELLMAN_HPP

#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <limits>
#include <cmath>

template<typename G>
struct BFSSP
{
	using vertex = origin::vertex_t;
	using edge = origin::edge_t;

	BFSSP(G& g, int s)
	:graph(g),
	distances(graph.num_vertices(), std::numeric_limits<double>::infinity()),
	parents(graph.num_vertices()),
    s(s)
	{}

	template<typename Lable1, typename Lable2>
	void
	find_path(vertex s, Lable1 distance, Lable2 paren)
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

	template<typename Lable1, typename Lable2>
	bool
	check_negative_cycles(Lable1 distance, Lable2 paren)
	{
		for (auto e : graph.edges())
			if (distance(graph.target(e)) < distance(graph.source(e)) 
                                             + graph.weight(e))
				return false;
		return true;
	}

	G
	operator()()
	{
		auto distance = origin::vertex_label(distances);
		auto paren = origin::vertex_label(parents);
		G result;

		find_path(s, distance, paren);
        if(check_negative_cycles(distance, paren))
          return result;
       
        
        for(auto v : graph.verts_)
            result.add_vertex(v.data);

        for(auto v : graph.vertices())
           if(v != s)
            result.add_edge(paren(v), v, distance(v)-distance(paren(v)));
        
        return result;
	}

	G graph;
    vertex s;
	std::vector<double> distances;
	std::vector<vertex> parents; //Batman doesn't has any :(

};

#endif