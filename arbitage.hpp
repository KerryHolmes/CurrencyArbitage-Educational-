#ifndef ARBITAGE_HPP
#define ARBITAGE_HPP

#include "digraph.hpp"
#include <climits>

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
      auto distance = vertex_label(distance);
      auto paren = vertex_label(parens);

      for(vertex_t v : graph.vertices())
         parent(v) = v;
      
      for(int i = 1; i < graph.num_vertices()-1; ++i)
      {
          
      }
         
   }
   
   template<typename Lable1, typename Lable2>
   void BFSP(vertex u, Lable1 distance, Lable2 paren)
   {
      for(edge e : graph.out_edges(u)) 
        {
           vertex v = graph.target(e);
           relax(u, v, e);
        }
    }
   }

   void relax(vertex u, vertex v, edge e)
   {
     if(distance(v) > distance(u) + graph.weight(e))
     {
         distance(v) =  distance(u) + graph.weight(e);
         paren(v) = u;
     }  
   }
    
   G graph;
   std::vector<int> distances;
   std::vector<origin::vertex_t> parens; //Batman doesn't has any :(
    
}

#endif
