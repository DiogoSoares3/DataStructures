#include <iostream>
#include <string>
#include <stdexcept>
#include "WeightedUndirectedGraph.h"
#include "GraphCicles.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <arquivo_do_grafo>" << std::endl;
        return 1;
    }

    std::string arquivo = argv[1];

    try {
        // Lê o grafo a partir do arquivo fornecido
        WeightedUndirectedGraph<std::string> grafo(arquivo);

        // Executa o algoritmo do ciclo euleriano
        EulerianCycleSolver<std::string> solver(grafo);
        solver.printEulerianCycle();

    } catch (const std::exception& e) {
        std::cerr << "Erro ao executar o programa: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}