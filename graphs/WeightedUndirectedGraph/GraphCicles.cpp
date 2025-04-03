#include <vector>
#include <string>
#include <utility>
#include "WeightedUndirectedGraph.h"
#include "GraphCicles.h"

template<typename Tp>
EulerianCycleSolver<Tp>::EulerianCycleSolver(const WeightedUndirectedGraph<Tp>& graph) : graph(graph) { }

template<typename Tp>
std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> EulerianCycleSolver<Tp>::HierholzerAlgorithm() const {
    // std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*> cycle = {};

    if (this->graph.qtdArestas() == 0) {
        return (true, {});
    }

    size_t n = graph.qtdVertices();
    edgeCount = std::vector<std::vector<size_t>>(n, std::vector<size_t>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        auto* vertex = graph.getVertex(i);
        for (auto* edge : vertex->adj) {
            size_t uIndex = edge->u->index;  // 1-index based
            size_t vIndex = edge->v->index;  // 1-index based

            edgeCount[uIndex-1][vIndex-1] += 1;
            edgeCount[vIndex-1][uIndex-1] += 1;
        }
    }

    auto* startVertex = findConnectedVertex();
    
    if (startVertex == nullptr) {
        return {false, {}};
    }

    auto result = buscarSubciclo(startVertex, edgeCount);

    
}

template<typename Tp>
std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> EulerianCycleSolver<Tp>::buscarSubciclo(
    typename WeightedUndirectedGraph<Tp>::Vertex* start,
    std::vector<std::vector<size_t>>& edgeCount
) const {

}

template<typename Tp>
typename WeightedUndirectedGraph<Tp>::Vertex* EulerianCycleSolver<Tp>::findConnectedVertex() const {
    size_t n = this->graph.qtdVertices();

    for (size_t i = 0; i < n; ++i) {
        auto* vertex = this->graph.getVertex(i);
        
        if (!vertex->adj.empty()) {
            return vertex;
        }
    }

    return nullptr;
}