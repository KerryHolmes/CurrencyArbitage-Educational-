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
   //Seed the random values with 0
   std::srand(0);
   
   //Explicitly set the number of records to test the BFSSP
   int num_records = 1000;
   
   //Create the graph, it begins null
   graph network;

   //Generate the vertices in the graph from 0 to the number specified above
   for(int i = 0; i <= num_records; ++i)
   {
      network.add_vertex(i);
   }

   //Fully connect the graph by generating an edge with a random weight from 
   //this vertex to every other one in the graph.

   for(auto u : network.vertices())
      for(auto v : network.vertices())
          if( u != v)
            network.add_edge(u, v, (std::rand()%950)+1);

  //Select the starting point at random from the graph and display it.
  int source = std::rand()%num_records;
  std::cout << "Source: " << source << std::endl;

  //Start timing the runtime of the algorithm
  auto start = std::chrono::system_clock::now();

  //Construct the bellman object and invoke its () operator to perform the 
  //Shortest path search and return the result into SSP.

  BFSSP<graph> bfsp(network, source);
  auto SSP = bfsp();

  //Stop timing the runtime of the algorithm
  auto stop = std::chrono::system_clock::now();

  //Construct the printer utility and invoke it to display the shortest
  //path graph that was constructed previously.
  origin::print_digraph<graph> print_result(std::cout, SSP);
  print_result();
  
  //Display the number of elements and the runtime of the algorithm
  std::cout << num_records << ' ' << (stop - start).count() << std::endl;
}