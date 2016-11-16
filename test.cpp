#include "digraph.hpp"
#include <iostream>
#include <string>
#include <cassert>

using graph = origin::digraph<std::string,double>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;

int main(int argc, char* argv[])
{

   graph exchanges;
   vertex currency[]{
       exchanges.add_vertex("currency1"),
       exchanges.add_vertex("currency2"),
       exchanges.add_vertex("currency3"),
       exchanges.add_vertex("currency4"),
       exchanges.add_vertex("currency5"),
       exchanges.add_vertex("currency6")
   };

   edge rate[]{
       exchanges.add_edge(currency[0],currency[1],0.197),
       exchanges.add_edge(currency[0],currency[2],0.197),
       exchanges.add_edge(currency[0],currency[3],0.197),
       exchanges.add_edge(currency[0],currency[4],0.197),
       exchanges.add_edge(currency[0],currency[5],0.197),
       exchanges.add_edge(currency[1],currency[0],0.197),
       exchanges.add_edge(currency[1],currency[2],0.197),
       exchanges.add_edge(currency[1],currency[3],0.197),
       exchanges.add_edge(currency[1],currency[4],0.197),
       exchanges.add_edge(currency[1],currency[5],0.197)

   };

}