#include "bellman.hpp"
#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <random>

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
   graph moneyFlow;

   double path[num_records];
   vertex vertices[num_records];

   for(int i = 1; i <= num_records; ++i)
   {
      std::getline(numbers,current);
      vertices[i] = moneyFlow.add_vertex(current);
   }

   for(auto u : graph.verts_)
      for(auto v : graph.verts_)
          if( u != v)
            moneyFlow.add_edge(u, v, std::rand()%10);
 
  origin::print_digraph<graph> print(std::cout, moneyFlow);
  print();


  BFSSP<graph> bfsp(moneyFlow);
  auto SSP = bfsp();

  origin::print_digraph<graph> print_result(std::cout, cycle);
  print_result();
}