#pragma once
#include <vector>
#include <string>
#include <utility>
#include "WeightedUndirectedGraph.h"

template<typename Tp>
class EulerianCycleSolver {
public:
    EulerianCycleSolver(const WeightedUndirectedGraph<Tp>& graph);
    
    std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> HierholzerAlgorithm() const;

    void printEulerianCycle() const;

private:
    const WeightedUndirectedGraph<Tp>& graph;
    mutable std::vector<std::vector<size_t>> edgeCount;  // Mutable because it needs to be modified in const methods

    std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> buscarSubciclo(
         typename WeightedUndirectedGraph<Tp>::Vertex* start,
         std::vector<std::vector<size_t>>& edgeCount
    ) const;

    typename WeightedUndirectedGraph<Tp>::Vertex* findConnectedVertex() const;
};