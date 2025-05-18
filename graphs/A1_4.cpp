#include <iostream>
#include <string>
#include <stdexcept>
#include "WeightedUndirectedGraph.h"
#include "MinimalPaths.h"
// #include "MinimalPaths.cpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo> <indice_vertice_origem>" << std::endl;
        return 1;
    }

    std::string arquivo = argv[1];
    size_t origem;

    try {
        origem = std::stoul(argv[2]);
    } catch (...) {
        std::cerr << "Erro: índice do vértice de origem inválido." << std::endl;
        return 1;
    }

    try {
        WeightedUndirectedGraph<std::string> grafo(arquivo);

        // =================== Bellman-Ford ===================
        auto resultadoBF = BellmanFord(grafo, origem);
        printBellmanFordResult(grafo, origem, resultadoBF);

        // =================== Dijkstra ===================
        // auto resultadoDijkstra = Dijkstra(grafo, origem);
        // printDijkstraResult(grafo, origem, resultadoDijkstra);

    } catch (const std::exception& e) {
        std::cerr << "Erro ao executar o programa: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
