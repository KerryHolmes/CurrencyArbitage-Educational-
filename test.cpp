#include "digraph.hpp"
#include <iostream>
#include <string>
#include <cassert>

using graph = digraph<std::string,double>;
using vertex = vertex_t;
using edge = edge_t;

int main(int argc, char* argv[])
{

   graph exchanges;
   vertext currency[]{
       exchanges.add_vertex("currency1"),
       exchanges.add_vertex("currency2"),
       exchanges.add_vertex("currency3"),
       exchanges.add_vertex("currency4"),
       exchanges.add_vertex("currency5"),
       exchanges.add_vertex("currency6")
   };

   edge rate[]{
       exchanges.add_edge(exchanges[0],exchanges[1],0.197),
       exchanges.add_edge(exchanges[0],exchanges[2],0.197),
       exchanges.add_edge(exchanges[0],exchanges[3],0.197),
       exchanges.add_edge(exchanges[0],exchanges[4],0.197),
       exchanges.add_edge(exchanges[0],exchanges[5],0.197),
       exchanges.add_edge(exchanges[0],exchanges[6],0.197),
       exchanges.add_edge(exchanges[1],exchanges[0],0.197),
       exchanges.add_edge(exchanges[1],exchanges[2],0.197),
       exchanges.add_edge(exchanges[1],exchanges[3],0.197),
       exchanges.add_edge(exchanges[1],exchanges[4],0.197),
       exchanges.add_edge(exchanges[1],exchanges[5],0.197),
       exchanges.add_edge(exchanges[1],exchanges[6],0.197),

   }

}