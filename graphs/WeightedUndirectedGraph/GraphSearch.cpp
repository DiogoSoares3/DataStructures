#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <optional>
#include <algorithm>
#include <stack>
#include "WeightedUndirectedGraph.h"
#include "GraphSearch.h"


template<typename Tp>
std::vector<size_t> BreadthFirstSearch(const WeightedUndirectedGraph<Tp>& graph, size_t startVertexIndex) {
    // Configuring all vertices
    size_t n {graph.qtdVertices()};

    std::vector<bool> knownVertices(n, false);
    std::vector<size_t> traveledDistance(n, std::numeric_limits<size_t>::max());
    std::vector<std::optional<size_t>> predecessorVertices(n, std::nullopt);

    // Configuring the source vertex (correct the index for 0-based array access)
    knownVertices[startVertexIndex - 1] = true;
    traveledDistance[startVertexIndex - 1] = 0;

    // Preparing the visitor queue
    std::queue<size_t> Q;
    Q.push(startVertexIndex);

    while (!Q.empty()) {
        size_t u = Q.front();  // Gets a 1-based index
        Q.pop();

        // Loop through neighbors, adjust index if needed
        for (auto vertex : graph.vizinhos(graph.getVertex(u))) {
            size_t v = vertex->index - 1;  // Convert to 0-based index for array operations

            if (!knownVertices[v]) {  // If the current vertex is not known
                knownVertices[v] = true;
                traveledDistance[v] = traveledDistance[u - 1] + 1;  // Adjust for 0-based index
                predecessorVertices[v] = u;  // Store predecessor (adjusted index)

                Q.push(v + 1);  // Convert back to 1-based index for the queue
            }
        }
    }

    // A Hash Map for debugging levels
    std::unordered_map<size_t, std::vector<Tp>> levelNodes;

    // Loop through all vertices and store them in corresponding levels based on distance
    for (size_t i = 0; i < n; ++i) {
        if (traveledDistance[i] != std::numeric_limits<size_t>::max()) {
            levelNodes[traveledDistance[i]].push_back(graph.rotulo(graph.getVertex(i + 1)));  // 1-based index for getVertex
        }
    }

    // Print levels and corresponding nodes
    std::vector<size_t> sortedLevels;
    for (const auto& level : levelNodes) {
        sortedLevels.push_back(level.first);
    }

    // Sort the levels in ascending order
    std::sort(sortedLevels.begin(), sortedLevels.end());

    // Now print the nodes for each level in sorted order
    for (size_t level : sortedLevels) {
        std::cout << level << ": ";
        for (size_t i = 0; i < levelNodes[level].size(); ++i) {
            std::cout << levelNodes[level][i];
            if (i < levelNodes[level].size() - 1) std::cout << ",";
        }
        std::cout << std::endl;
    }


    return traveledDistance;
}

template<typename Tp>
std::vector<size_t> DepthFirstSearch(const WeightedUndirectedGraph<Tp>& graph, size_t startVertexIndex) {
    // Configuring all vertices
    size_t n {graph.qtdVertices()};

    std::vector<bool> knownVertices(n, false);
    std::vector<size_t> timeElapsed(n, std::numeric_limits<size_t>::max());
    std::vector<std::optional<size_t>> predecessorVertices(n, std::nullopt);

    // Configuring the source vertex (correct the index for 0-based array access)
    knownVertices[startVertexIndex - 1] = true;
    size_t currentTime {0};

    // Preparing the visitor stack
    std::stack<size_t> S;
    S.push(startVertexIndex);

    while (!S.empty()) {
        currentTime += 1;
        size_t u {S.top()};
        S.pop();
        timeElapsed[u-1] = currentTime;  // Converting to 0-index based

        for (auto vertex : graph.vizinhos(graph.getVertex(u))) {
            size_t v = vertex->index - 1;  // Converting to 0-based index for array operations

            if (!knownVertices[v]) {
                knownVertices[v] = true;
                predecessorVertices[v] = u - 1;  // 'u' is 1-index based, so we are converting to 1-index based
                S.push(v + 1);  // Push back as 1-indexed for consistency in getVertex calls
            }
        }
    }

    return timeElapsed;
}

template std::vector<size_t> BreadthFirstSearch<std::string>(const WeightedUndirectedGraph<std::string>&, size_t);
template std::vector<size_t> DepthFirstSearch<std::string>(const WeightedUndirectedGraph<std::string>&, size_t);