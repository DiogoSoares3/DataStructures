#pragma once
#include "WeightedUndirectedGraph.h"

template<typename Tp>
std::vector<size_t> BreadthFirstSearch(const WeightedUndirectedGraph<Tp>& graph, size_t startVertexIndex);

template<typename Tp>
std::vector<size_t> DepthFirstSearch(const WeightedUndirectedGraph<Tp>& graph, size_t startVertexIndex);
