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
   std::current;
   std::getline(numbers,current)
   int num_records = std::stoi(current);

   double to_USD[num_records] = {0};
   string name[num_records] = {""};

   for(int i = 0; i < num_records; ++i)
   {
      std::getline(numbers,current)
      name[i] = current;
      std::getline(numbers,current)
      double[i] = std::stod(current);
   }
}