#ifndef ARBITAGE_HPP
#define ARBITAGE_HPP

#include "digraph.hpp"

template<typename G>
struct currency_arbitrage
{
    
    currency_arbitrage(G& g)

    G graph;
    std::vector<int> distance;
    std::vector<origin::vertex_t> parens; //Batman doesn't has any :(
    
}

#endif
