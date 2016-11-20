#include "bellman.hpp"
#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

//These types are in their own namespace, here the using statement
//is used to create aliases for these types to make the code 
//easier to comprehend
using graph = origin::digraph<std::string,double>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;

std::srand(0);

int main(int argc, char* argv[])
{  
   //Open the file stream to read the exchange rates and currencies
   std::ifstream numbers("../excrates.txt");

   //This string is to hold the current line from the file as it is processed
   std::string current;

   //Read in the first line of the file. 
   //This will contain the number of currencies in the file
   //This value is stored and used to size the arrays created below
   std::getline(numbers,current);
   int num_records = std::stoi(current);
   
   //Create the graph 
   graph network;

   double path[num_records];
   vertex vertices[num_records];

   for(int i = 1; i <= num_records; ++i)
   {
      std::getline(numbers,current);
      vertices[i] = network.add_vertex(current);
   }

   for(auto u : network.verts_)
      for(auto v : network.verts_)
          if( u != v)
            network.add_edge(u, v, std::rand()%10);
 
  origin::print_digraph<graph> print(std::cout, network);
  print();


  BFSSP<graph> bfsp(network, 1);
  auto SSP = bfsp();

  origin::print_digraph<graph> print_result(std::cout, SSP);
  print_result();
}