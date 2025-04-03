#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "WeightedUndirectedGraph.h"
#include "GraphCicles.h"

template<typename Tp>
EulerianCycleSolver<Tp>::EulerianCycleSolver(const WeightedUndirectedGraph<Tp>& graph) : graph(graph) { }

template<typename Tp>
std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> EulerianCycleSolver<Tp>::HierholzerAlgorithm() const {
    if (this->graph.qtdArestas() == 0) {
        return std::make_pair(true, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>());
    }

    size_t n = graph.qtdVertices();
    edgeCount = std::vector<std::vector<size_t>>(n, std::vector<size_t>(n, 0));

    for (size_t i = 0; i < n; ++i) {
        auto* vertex = graph.getVertex(i+1);  // +1 porque getVertex espera índice base-1
        for (auto* edge : vertex->adj) {
            size_t uIndex = edge->u->index;  // 1-index based
            size_t vIndex = edge->v->index;  // 1-index based

            if (i+1 == edge->u->index) {  // Só conta quando estamos no vértice u da aresta
                edgeCount[uIndex-1][vIndex-1] += 1;
                edgeCount[vIndex-1][uIndex-1] += 1;
            }
        }
    }

    auto* startVertex = findConnectedVertex();
    
    if (startVertex == nullptr) {
        return std::make_pair(false, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>());
    }

    auto result = buscarSubciclo(startVertex, edgeCount);

    if (!result.first) {
        return std::make_pair(false, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>());
    }

    // Verifica se todas as arestas foram usadas
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (edgeCount[i][j] > 0) {
                return std::make_pair(false, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>());
            }
        }
    }

    return result;
}

template<typename Tp>
std::pair<bool, std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*>> 
EulerianCycleSolver<Tp>::buscarSubciclo(
    typename WeightedUndirectedGraph<Tp>::Vertex* start,
    std::vector<std::vector<size_t>>& edgeCount
) const {
    using Vertex = typename WeightedUndirectedGraph<Tp>::Vertex;
    std::vector<Vertex*> ciclo;
    ciclo.push_back(start);  // Ciclo ← (v)
    
    Vertex* t = start;       // t ← v
    Vertex* v = start;
    
    // Constrói o ciclo inicial
    do {
        bool hasUnvisitedEdge = false;
        Vertex* nextVertex = nullptr;
        
        // Procura por um vértice adjacente com aresta não visitada
        for (const auto* edge : v->adj) {
            Vertex* u = (edge->u == v) ? edge->v : edge->u;
            if (edgeCount[v->index-1][u->index-1] > 0) {
                hasUnvisitedEdge = true;
                nextVertex = u;
                break;
            }
        }
        
        if (!hasUnvisitedEdge) {
            return std::make_pair(false, std::vector<Vertex*>());
        }
        
        // Marca a aresta como visitada (nos dois sentidos)
        edgeCount[v->index-1][nextVertex->index-1]--;
        edgeCount[nextVertex->index-1][v->index-1]--;
        
        v = nextVertex;
        ciclo.push_back(v);
        
    } while (v != t);
    
    // Para evitar modificar o vetor enquanto itera, cria-se uma cópia do ciclo
    std::vector<Vertex*> cicloCopy = ciclo;
    
    // Para cada vértice x do ciclo (usando a cópia)
    for (auto* x : cicloCopy) {
        bool hasUnvisitedEdges = false;
        for (const auto* edge : x->adj) {
            Vertex* w = (edge->u == x) ? edge->v : edge->u;
            if (edgeCount[x->index-1][w->index-1] > 0) {
                hasUnvisitedEdges = true;
                break;
            }
        }
        
        if (hasUnvisitedEdges) {
            // Busca recursivamente um subciclo começando em x
            auto [success, subciclo] = buscarSubciclo(x, edgeCount);
            if (!success) {
                return std::make_pair(false, std::vector<Vertex*>());
            }
            
            // Encontra a posição de x no ciclo original
            auto it = std::find(ciclo.begin(), ciclo.end(), x);
            if (it != ciclo.end()) {
                std::vector<Vertex*> newCiclo;
                // Insere os elementos até x
                newCiclo.insert(newCiclo.end(), ciclo.begin(), it);
                // Insere o subciclo encontrado
                newCiclo.insert(newCiclo.end(), subciclo.begin(), subciclo.end());
                // Insere o restante do ciclo original, a partir de depois de x
                newCiclo.insert(newCiclo.end(), std::next(it), ciclo.end());
                ciclo = std::move(newCiclo);
            }
        }
    }
    
    return std::make_pair(true, ciclo);
}


template<typename Tp>
typename WeightedUndirectedGraph<Tp>::Vertex* EulerianCycleSolver<Tp>::findConnectedVertex() const {
    size_t n = this->graph.qtdVertices();

    for (size_t i = 0; i < n; ++i) {
        auto* vertex = this->graph.getVertex(i+1);  // +1 porque getVertex espera índice base-1
        
        if (!vertex->adj.empty()) {
            return vertex;
        }
    }

    return nullptr;
}

template<typename Tp>
void EulerianCycleSolver<Tp>::printEulerianCycle() const {
    // Calls the algorithm to find the Eulerian cycle
    auto result = this->HierholzerAlgorithm();
    
    // If there is no Eulerian cycle, prints 0 and returns
    if (!result.first) {
        std::cout << "0" << std::endl;
        return;
    }
    
    // If there is an Eulerian cycle, prints 1 on the first line
    std::cout << "1" << std::endl;
    
    // Prints the sequence of vertices of the cycle
    // (assuming 'index' or 'label' is the data that identifies the vertex)
    auto cycle = result.second;
    for (size_t i = 0; i < cycle.size(); ++i) {
        // If the graph uses indices (as in the expected example),
        // print cycle[i]->index
        std::cout << cycle[i]->index;
        if (i < cycle.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << std::endl;
}

// Explicit instantiation
template class EulerianCycleSolver<std::string>;