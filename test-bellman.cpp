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
using graph = origin::digraph<std::string,int>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;



int main(int argc, char* argv[])
{  
   //Open the file stream to read the exchange rates and currencies
   std::ifstream numbers("../excrates.txt");
   std::srand(0);

   //This string is to hold the current line from the file as it is processed
   std::string current;

   //Read in the first line of the file. 
   //This will contain the number of currencies in the file
   //This value is stored and used to size the arrays created below
   std::getline(numbers,current);
   int num_records = std::stoi(current);
   
   //Create the graph 
   graph network;

   int path[num_records];
   vertex vertices[num_records];

   for(int i = 1; i <= num_records; ++i)
   {
      std::getline(numbers,current);
      vertices[i] = network.add_vertex(current);
   }

   for(auto u : network.vertices())
      for(auto v : network.vertices())
          if( u != v)
            network.add_edge(u, v, (std::rand()%10)+1);
 
  origin::print_digraph<graph> print(std::cout, network);
  print();
  
  int source = std::rand()%num_records;
  std::cout << "Source: " << source << std::endl;
  auto start = std::chrono::system_clock::now();
  BFSSP<graph> bfsp(network, source);
  auto SSP = bfsp();
  auto stop = std::chrono::system_clock::now();
  origin::print_digraph<graph> print_result(std::cout, SSP);
  print_result();
  std::cout << n << ' ' << (stop - start).count() << std::endl;
}