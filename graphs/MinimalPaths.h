#pragma once
#include "WeightedUndirectedGraph.h"
#include <tuple>
#include <vector>

template<typename Tp>
std::tuple<bool, std::vector<double>, std::vector<double>> BellmanFord(const WeightedUndirectedGraph<Tp>& graph, const size_t& source);

template<typename Tp>
void printBellmanFordResult(const WeightedUndirectedGraph<Tp>& graph, const size_t& source, const std::tuple<bool, std::vector<double>, std::vector<double>>& result);

template<typename Tp>
std::tuple<std::vector<double>, std::vector<double>> Dijkstra(const WeightedUndirectedGraph<Tp>& graph, const Tp& source);

template<typename Tp>
void printDijkstraResult(const WeightedUndirectedGraph<Tp>& graph, const size_t& source, const std::tuple<bool, std::vector<double>, std::vector<double>>& result);


template<typename Tp>
void FloydWarshall(const WeightedUndirectedGraph<Tp>& graph);   