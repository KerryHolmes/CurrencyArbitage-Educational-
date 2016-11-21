#ifndef BELLMAN_HPP
#define BELLMAN_HPP

#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <limits>
#include <cmath>

//An Implementation of Bellman-Ford Algorithm For the directed graph from 
//Dr.Sutton's graph library available at:
//https://github.com/asutton/cxx14-graph.git

template<typename G, typename T = int>
struct BFSSP
{
	//These are defined in the origin namespace. The using statement allows
	//them to be written in a more concise format 
	using vertex = origin::vertex_t;
	using edge = origin::edge_t;

	//This is the only constructor for this class. It requires a graph, a start
	//and a maximum value that is used to simulate infinity. This allows for 
	//the largest value to be specified to avoid the overflow issues that occur
	//when using constructs such as int max and infinity.

	BFSSP(G& g, int s, T max = 1000000) //max defualts to be 1 million 
	:graph(g),
	distances(graph.num_vertices(), max), //All distances begin at max
	parents(graph.num_vertices(), -1), //All parents begin invalid
    s(s)
	{}

    //This function is what runs the algorithm. It uses two lables, distance 
	//and paren. It begins by setting the distance and paren of the starting 
	//vertex to 0 and s respectively. It runs from 1 to number of vertices
	//then iterates over each edge calling the relax function each time. 
	//The run time of this will be O(V*E).

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

    //The relax function compares the distance to vertex v, to the distance to
	//vertex u + the weight of the edge they share. If the current distance of v
	//is greater, the distance gets updated to the smaller value and the parent
	//of v becomes u.

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

    //This function runs after the main path finding has occured. At the time 
	//it runs, there should be no edges to relax. If there are, the function
	//returns false to indicate that there was a negative edge cycle 
	//in the graph.

	template<typename Lable1, typename Lable2>
	bool
	check_negative_cycles(Lable1 distance, Lable2 paren)
	{
		for (auto e : graph.edges())
			if (distance(graph.target(e)) > distance(graph.source(e)) 
                                                   + graph.weight(e))
				return false;
		return true;
	}

	//The overload of the () operator to run the bellman algorithm and check
	//if there are negative cycles in the graph. After which point, it 
	//constructs a graph of the minimum paths and returns that result by value.

	G
	operator()()
	{
		auto distance = origin::vertex_label(distances);
		auto paren = origin::vertex_label(parents);
		G result;

		find_path(s, distance, paren);
        if(!check_negative_cycles(distance, paren))
          return result;
       
        
        for(auto v : graph.verts_)
            result.add_vertex(v.data);

        for(auto v : graph.vertices())
           if(v != s)
            result.add_edge(paren(v), v, graph.edge(paren(v), v));
        
        return result;
	}

	G graph; //The graph itself.
    vertex s; //This is the vertex the search runs from.
	std::vector<T> distances; //This holds the total distance from this vertex
	                          //to the source.
	std::vector<vertex> parents; //This vector has an index for each vertex
	                             //which holds the vertex that is the parent of 
								 //this one.

};

#endif