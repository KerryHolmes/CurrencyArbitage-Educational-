#include "bellman.hpp"
#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>

//These types are in their own namespace, here the using statement
//is used to create aliases for these types to make the code 
//easier to comprehend
using graph = origin::digraph<int,int>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;



int main(int argc, char* argv[])
{  
   std::srand(0);

   int num_records = 1000;
   
   //Create the graph 
   graph network;

   for(int i = 0; i <= num_records; ++i)
   {
      network.add_vertex(i);
   }

   for(auto u : network.vertices())
      for(auto v : network.vertices())
          if( u != v)
            network.add_edge(u, v, (std::rand()%950)+1);
  
  int source = std::rand()%num_records;
  std::cout << "Source: " << source << std::endl;

  auto start = std::chrono::system_clock::now();

  BFSSP<graph> bfsp(network, source);
  auto SSP = bfsp();

  auto stop = std::chrono::system_clock::now();

  origin::print_digraph<graph> print_result(std::cout, SSP);
  print_result();
  
  std::cout << num_records << ' ' << (stop - start).count() << std::endl;
}