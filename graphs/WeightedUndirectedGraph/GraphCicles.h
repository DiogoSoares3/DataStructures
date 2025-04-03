#pragma once
#include <vector>
#include <string>
#include <utility>
#include "WeightedUndirectedGraph.h"

template<typename Tp>
class EulerianCycleSolver {
    EulerianCycleSolver(const WeightedUndirectedGraph<Tp>& graph);

    std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*> cycle = {};

    std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> HierholzerAlgorithm() const;

private:
    const WeightedUndirectedGraph<Tp>& graph;

    std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> buscarSubciclo(
         typename WeightedUndirectedGraph<Tp>::Vertex* start,
         std::vector<std::vector<size_t>>& edgeCount
    ) const;

    typename WeightedUndirectedGraph<Tp>::Vertex* findConnectedVertex() const;
};