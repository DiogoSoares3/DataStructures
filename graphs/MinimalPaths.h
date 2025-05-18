#pragma once
#include "WeightedUndirectedGraph.h"
#include <tuple>
#include <vector>
#include <iomanip>
#include <limits>

template<typename Tp>
std::tuple<bool, std::vector<double>, std::vector<double>> BellmanFord(const WeightedUndirectedGraph<Tp>& graph, const size_t& source);

template<typename Tp>
void printBellmanFordResult(const WeightedUndirectedGraph<Tp>& graph, const size_t& source, const std::tuple<bool, std::vector<double>, std::vector<double>>& result);

template<typename Tp>
std::tuple<std::vector<double>, std::vector<double>> Dijkstra(const WeightedUndirectedGraph<Tp>& graph, const Tp& source);

template<typename Tp>
void printDijkstraResult(const WeightedUndirectedGraph<Tp>& graph, const size_t& source, const std::tuple<bool, std::vector<double>, std::vector<double>>& result);

template<typename Tp>
std::tuple<std::vector<std::vector<double>>, std::vector<std::vector<size_t>>> FloydWarshall(const WeightedUndirectedGraph<Tp>& graph);

inline void printDistanceMatrix(const std::vector<std::vector<double>>& D_fw) {
    std::cout << "\nFloyd-Warshall Distance Matrix:" << std::endl;
    for (size_t i = 0; i < D_fw.size(); ++i) {
        std::cout << i + 1 << ":";
        for (size_t j = 0; j < D_fw[i].size(); ++j) {
            if (j > 0) std::cout << ",";
            if (D_fw[i][j] == std::numeric_limits<double>::infinity())
                std::cout << "inf";
            else
                std::cout << D_fw[i][j];
        }
        std::cout << std::endl;
    }
}

inline void printPredecessorMatrix(const std::vector<std::vector<size_t>>& PI) {
    std::cout << "\nFloyd-Warshall Predecessor Matrix:" << std::endl;
    for (const auto& row : PI) {
        for (const auto& p : row) {
            if (p == std::numeric_limits<size_t>::max())
                std::cout << "null ";
            else
                std::cout << (p + 1) << " ";
        }
        std::cout << std::endl;
    }
}

#include "MinimalPaths.cpp"
