#include "arbitage.hpp"
#include "digraph.hpp"
#include "output.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cmath>

//Currency A -> Currency B = (USD/Currency A) / (USD/Currency B)

//These types are in their own namespace, here the using statement
//is used to create aliases for these types to make the code 
//easier to comprehend
using graph = origin::digraph<std::string,double>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;

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

   double from_USD[num_records+1] = {0};
   vertex vertices[num_records+1];
   
   vertices[0] = moneyFlow.add_vertex("US Dollars");
   from_USD[0] = 1;

   for(int i = 1; i <= num_records; ++i)
   {
      std::getline(numbers,current);
      vertices[i] = moneyFlow.add_vertex(current);
      std::getline(numbers,current);
      from_USD[i] = 1 / std::stod(current);
   }

   for(int i = 1; i < moneyFlow.num_vertices(); ++i)
       moneyFlow.add_edge(vertices[0], vertices[i], 1 / from_USD[i]);

   for(int i = 1; i < moneyFlow.num_vertices(); ++i)
   {
      for(int j = 0; j < moneyFlow.num_vertices(); ++j)
      {
          if( i != j)
          {
            double exchange = from_USD[j] / from_USD[i];
            moneyFlow.add_edge(vertices[i], vertices[j], exchange);
          }
      }
   }
 
  graph copy(moneyFlow);
  origin::print_digraph<graph> print(std::cout, copy);
  print();


  currency_arbitrage<graph> bbff(moneyFlow);
  auto cycle = bbff();

  double principle = 1.00;
  for(int i = 0; i < cycle.size(); ++i)
   {
       std::cout << principle << std::endl;
       auto e = moneyFlow.edge(cycle[i], cycle[(i+1)%cycle.size()]);
       principle *= moneyFlow.weight(e); 
   }
   std::cout << principle << std::endl;
}