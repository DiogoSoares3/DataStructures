#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>
#include "WeightedUndirectedGraph.h"
#include "MinimalPaths.h"
#include "MinimalPaths.cpp"


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << std::endl;
        return 1;
    }

    std::string arquivo = argv[1];

    try {
        // Carrega o grafo
        WeightedUndirectedGraph<std::string> grafo(arquivo);

        // Executa Floyd–Warshall
        auto [D, PI] = FloydWarshall(grafo);

        size_t n = grafo.qtdVertices();
        // Imprime as distâncias, uma linha por vértice de origem
        for (size_t i = 0; i < n; ++i) {
            std::cout << (i + 1) << ":";
            for (size_t j = 0; j < n; ++j) {
                if (j > 0) std::cout << ",";
                if (D[i][j] == std::numeric_limits<double>::infinity()) {
                    std::cout << "inf";
                } else {
                    std::cout << D[i][j];
                }
            }
            std::cout << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Erro ao executar o programa: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
