#include "digraph.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using graph = origin::digraph<std::string,double>;
using vertex = origin::vertex_t;
using edge = origin::edge_t;

int main(int argc, char* argv[])
{
   std::ifstream numbers("../excrates.txt");
   std::string current;
   std::getline(numbers,current);
   int num_records = std::stoi(current);

   double to_USD[num_records] = {0};
   std::string name[num_records] = {""};

   for(int i = 0; i < num_records; ++i)
   {
      std::getline(numbers,current);
      name[i] = current;
      std::getline(numbers,current);
      to_USD[i] = std::stod(current);
   }

   graph moneyFlow;
   vertex verticies[num_records];

   for(int i = 0; i < num_records; ++i)
   {
      verticies[i] = moneyFlow.add_vertex(name[i]);
   }

   for(int i = 0; i < moneyFlow.num_verticies(); ++i)
   {
       for(int j = 0; j < moneyFloe.num_verticies(); ++j)
       {
           if(j != i)
           {
               moneyFlow.add_edge(verticies[i], verticies[j], to_USD[i]);
           }
       }
   }
}