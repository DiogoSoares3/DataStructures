#include "MinimalPaths.h"
#include "WeightedUndirectedGraph.h"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <tuple>
#include <queue>
#include <functional>
#include <iomanip>
#include <limits>


template<typename Tp>
void printBellmanFordResult(
    const WeightedUndirectedGraph<Tp>& graph,
    const size_t& source,
    const std::tuple<bool, std::vector<double>, std::vector<double>>& result
) {
    bool ok = std::get<0>(result);
    const std::vector<double>& dist = std::get<1>(result);
    const std::vector<double>& pred = std::get<2>(result);

    if (!ok) {
        std::cout << "Graph contains a negative cycle" << std::endl;
        return;
    }

    size_t n = graph.qtdVertices();

    // Para cada vértice (destino 1-based)
    for (size_t i = 0; i < n; ++i) {
        size_t dest = i;
    
        if (dist[dest] == std::numeric_limits<double>::infinity()) {
            std::cout << (dest + 1) << ": No path; d=Infinity" << std::endl;
            continue;
        }
    
        std::vector<size_t> path;
        size_t cur = dest;
    
        std::unordered_set<size_t> visitados;  // Para detectar ciclo
    
        while (true) {
            if (visitados.count(cur)) {
                std::cerr << "Cycle detected in predecessor chain. Aborting path reconstruction for vertex " << (dest + 1) << std::endl;
                break;
            }
            visitados.insert(cur);
            path.push_back(cur + 1);  // Ajuste para 1-based output
    
            if (cur == source - 1) break;
    
            if (pred[cur] == std::numeric_limits<size_t>::max()) {
                std::cerr << "No predecessor. Path not found for vertex " << (dest + 1) << std::endl;
                break;
            }
    
            cur = pred[cur];
        }
    
        std::reverse(path.begin(), path.end());
    
        std::cout << (dest + 1) << ": ";
        for (size_t j = 0; j < path.size(); ++j) {
            std::cout << path[j];
            if (j < path.size() - 1) std::cout << ",";
        }
        std::cout << "; d=" << dist[dest] << std::endl;
    }
}    

template<typename Tp>
std::tuple<bool, std::vector<double>, std::vector<double>> BellmanFord(
    const WeightedUndirectedGraph<Tp>& graph, 
    const size_t& source)
{
    size_t n = graph.qtdVertices();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<double> antecessor(n, std::numeric_limits<double>::infinity());
    
    // Converte o vértice de origem para 0-based
    dist[source - 1] = 0;
    antecessor[source - 1] = -1;  // Origem não tem antecessor

    for (size_t i = 0; i < n - 1; i++) {
        bool updated = false;
        std::vector<double> oldDist = dist; // snapshot
    
        for (auto* edge : graph.getEdges()) {
            size_t u = edge->u->index - 1;
            size_t v = edge->v->index - 1;
            double w = edge->weight;
    
            if (dist[v] > oldDist[u] + w) {
                dist[v] = oldDist[u] + w;
                antecessor[v] = u;
                updated = true;
            }
    
            if (dist[u] > oldDist[v] + w) {
                dist[u] = oldDist[v] + w;
                antecessor[u] = v;
                updated = true;
            }
        }
    
        if (!updated)
            break;
    }

    // Verificação de ciclo negativo: se for possível relaxar alguma aresta, há ciclo negativo.
    for (size_t u = 0; u < n; ++u) {
        auto* vertex = graph.getVertex(u + 1);
        for (auto* edge : vertex->adj) {
            if (edge->u->index > edge->v->index)
                continue;
            size_t uIndex = edge->u->index - 1;
            size_t vIndex = edge->v->index - 1;
            double peso = graph.peso(edge->u, edge->v);
            if (dist[uIndex] != std::numeric_limits<double>::infinity() &&
                dist[uIndex] + peso < dist[vIndex])
            {
                return std::make_tuple(false, std::vector<double>(), std::vector<double>());
            }
        }
    }
    
    return std::make_tuple(true, dist, antecessor);
}

template<typename Tp>
std::tuple<std::vector<double>, std::vector<double>> Dijkstra(
    const WeightedUndirectedGraph<Tp>& graph, 
    const size_t& source)
{
    size_t n = graph.qtdVertices();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<double> pred(n, std::numeric_limits<double>::max());
    
    // Converte a origem (entrada 1-based) para 0-based.
    dist[source - 1] = 0;
    pred[source - 1] = source - 1; // define a origem como seu próprio antecessor

    // Define a min-heap using a priority queue where each element is a pair:
    // (distance to vertex, vertex index)
    typedef std::pair<double, size_t> Node;
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

    // Push the source vertex into the priority queue with distance 0
    // Note: 'source' is assumed to be 1-based, so we subtract 1
    pq.push({0, source - 1});

    // Main loop: runs until all reachable vertices have been processed
    while (!pq.empty()) {
        // Extract the vertex with the smallest known distance (priority)
        auto [d, u] = pq.top();
        pq.pop();

        // Skip if this is an outdated entry (a newer, better distance was already found)
        if (d != dist[u])
            continue;

        // Retrieve the actual vertex object from the graph (graph is 1-based)
        auto* vertexU = graph.getVertex(u + 1);

        // Loop through all edges connected to vertex u
        for (auto* edge : vertexU->adj) {
            // Determine which vertex is the neighbor (other end of the edge)
            size_t neighborIndex;
            if (edge->u->index - 1 == u)
                neighborIndex = edge->v->index - 1;
            else
                neighborIndex = edge->u->index - 1;

            // Get the weight of the edge
            double w = edge->weight;

            // Relaxation step: check if going through u improves the path to neighbor
            if (dist[u] + w < dist[neighborIndex]) {
                // Update distance and predecessor if a better path is found
                dist[neighborIndex] = dist[u] + w;
                pred[neighborIndex] = u;

                // Add the neighbor to the priority queue with updated distance
                // Note: we may add duplicates, but outdated entries will be skipped at the top
                pq.push({dist[neighborIndex], neighborIndex});
            }
        }
    }

    return std::make_tuple(dist, pred);
}

template<typename Tp>
void printDijkstraResult(
    const WeightedUndirectedGraph<Tp>& graph,
    const size_t& source,
    const std::tuple<std::vector<double>, std::vector<double>>& result
) {
    const std::vector<double>& dist = std::get<0>(result);
    const std::vector<double>& pred = std::get<1>(result);
    size_t n = graph.qtdVertices();

    for (size_t i = 0; i < n; ++i) {
        size_t dest = i;

        if (dist[dest] == std::numeric_limits<double>::infinity()) {
            std::cout << (dest + 1) << ": No path; d=Infinity" << std::endl;
            continue;
        }

        std::vector<size_t> path;
        size_t cur = dest;
        std::unordered_set<size_t> visitados;

        while (true) {
            if (visitados.count(cur)) {
                std::cerr << "Cycle detected in predecessor chain. Aborting path reconstruction for vertex " << (dest + 1) << std::endl;
                break;
            }
            visitados.insert(cur);
            path.push_back(cur + 1); // para output 1-based

            if (cur == source - 1) break;

            if (pred[cur] == std::numeric_limits<size_t>::max()) {
                std::cerr << "No predecessor. Path not found for vertex " << (dest + 1) << std::endl;
                break;
            }

            cur = pred[cur];
        }

        std::reverse(path.begin(), path.end());

        std::cout << (dest + 1) << ": ";
        for (size_t j = 0; j < path.size(); ++j) {
            std::cout << path[j];
            if (j < path.size() - 1) std::cout << ",";
        }
        std::cout << "; d=" << dist[dest] << std::endl;
    }
}


template<typename Tp>
std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<size_t>>> FloydWarshall(const WeightedUndirectedGraph<Tp>& graph) {
    size_t n = graph.qtdVertices();
    std::vector<std::vector<double>> D(n, std::vector<double>(n, std::numeric_limits<double>::infinity()));
    
    // Predecessor matrix Π: initialize with "null" 
    std::vector<std::vector<size_t>> Π(n, std::vector<size_t>(n, std::numeric_limits<size_t>::max()));

    // Initialize D(0) and Π(0):
    // For each pair of vertices u, v:
    //   If u == v, set D[u][v] = 0
    //   Else if an edge exists between u and v, set D[u][v] = weight(u,v) and Π[u][v] = u.
    //   Otherwise D[u][v] remains infinity and Π[u][v] remains "null".
    for (size_t u = 0; u < n; u++) {
        for (size_t v = 0; v < n; v++) {
            if (u == v) {
                D[u][v] = 0;
            } else {
                auto* vertexU = graph.getVertex(u + 1);
                auto* vertexV = graph.getVertex(v + 1);
                if (graph.haAresta(vertexU, vertexV)) {
                    double weightUV = graph.peso(vertexU, vertexV);
                    D[u][v] = weightUV;
                    Π[u][v] = u;
                }
            }
        }
    }

    // Floyd-Warshall iterative improvement:
    for (size_t k = 0; k < n; k++) {
        for (size_t u = 0; u < n; u++) {
            for (size_t v = 0; v < n; v++) {
                if (D[u][v] > D[u][k] + D[k][v]) {
                    D[u][v] = D[u][k] + D[k][v];
                    Π[u][v] = Π[k][v];
                }
            }
        }
    }

    return std::make_tuple(D, Π);
}
