#include <iostream>
#include <fstream>
#include "WeightedUndirectedGraph.h"
#include "GraphSearch.h"

int main() {
    // Reading the input file
    std::string filename = "./entry_files/WeightedUndirectedGraph.txt";
    WeightedUndirectedGraph<std::string> graph(filename);

    // Testing the number of vertices and edges
    std::cout << "Number of vertices: " << graph.qtdVertices() << std::endl;
    std::cout << "Number of edges: " << graph.qtdArestas() << std::endl;

    // Testing the degree of vertices
    std::cout << "Degree of vertex 1: " << graph.grau(graph.getVertex(1)) << std::endl;
    std::cout << "Degree of vertex 2: " << graph.grau(graph.getVertex(2)) << std::endl;

    // Testing if edges exist
    std::cout << "Is there an edge between 1 and 2? " << (graph.haAresta(graph.getVertex(1), graph.getVertex(2)) ? "Yes" : "No") << std::endl;
    std::cout << "Is there an edge between 1 and 4? " << (graph.haAresta(graph.getVertex(1), graph.getVertex(4)) ? "Yes" : "No") << std::endl;

    // Testing the weight of edges
    std::cout << "Weight of the edge between 1 and 2: " << graph.peso(graph.getVertex(1), graph.getVertex(2)) << std::endl;
    std::cout << "Weight of the edge between 2 and 3: " << graph.peso(graph.getVertex(2), graph.getVertex(3)) << std::endl;
    std::cout << "Weight of the edge between 3 and 4: " << graph.peso(graph.getVertex(3), graph.getVertex(4)) << std::endl;

    // Testing neighbors of vertices
    std::cout << "Neighbors of vertex 1: ";
    for (auto v : graph.vizinhos(graph.getVertex(1))) {
        std::cout << v->label << " ";
    }
    std::cout << std::endl;

    std::cout << "Neighbors of vertex 2: ";
    for (auto v : graph.vizinhos(graph.getVertex(2))) {
        std::cout << v->label << " ";
    }
    std::cout << std::endl;

    std::cout << "#### Testing BFS ####" <<  std::endl;

    size_t startVertex;
    std::cout << "Enter the starting vertex index for BFS: ";
    std::cin >> startVertex;

    if (startVertex < 1 || startVertex > graph.qtdVertices()) {
        std::cerr << "Invalid vertex index! Exiting BFS test." << std::endl;
    } else {
        std::cout << "BFS traversal starting from vertex " << startVertex << ":\n";
        std::vector<size_t> distances = BreadthFirstSearch(graph, startVertex);
    }

        // ====== Testing Depth-First Search ======
        size_t startVertex2;
        std::cout << "\nEnter the starting vertex index for DFS: ";
        std::cin >> startVertex2;
        if (startVertex2 < 1 || startVertex2 > graph.qtdVertices()) {
            std::cerr << "Invalid vertex index! Exiting DFS test." << std::endl;
        } else {
            std::cout << "DFS traversal starting from vertex " << startVertex2 << ":\n";
            std::vector<size_t> discoveryTimes = DepthFirstSearch(graph, startVertex2);
            
            // Print discovery times for each vertex.
            std::cout << "Discovery times (0-indexed positions):\n";
            for (size_t i = 0; i < discoveryTimes.size(); ++i) {
                if (discoveryTimes[i] != std::numeric_limits<size_t>::max()) {
                    std::cout << "Vertex " << i + 1 << ": " << discoveryTimes[i] << std::endl;
                } else {
                    std::cout << "Vertex " << i + 1 << ": Not reached" << std::endl;
                }
            }
        }

    // Testing the graph clear function
    std::cout << "Clearing the graph..." <<  std::endl;
    graph.clear();
    std::cout << "Number of vertices after clearing: " << graph.qtdVertices() <<  std::endl;
    std::cout << "Number of edges after clearing: " << graph.qtdArestas() <<  std::endl;

    return 0;
}



// int main() {
//     try {
//         // Reading the input file for the graph.
//         std::string filename = "./entry_files/WeightedUndirectedGraph.txt";
//         WeightedUndirectedGraph<std::string> graph(filename);

//         // Test graph basic properties.
//         std::cout << "Number of vertices: " << graph.qtdVertices() << std::endl;
//         std::cout << "Number of edges: " << graph.qtdArestas() << std::endl;

//         // Test vertex properties.
//         std::cout << "Degree of vertex 1: " << graph.grau(graph.getVertex(1)) << std::endl;
//         std::cout << "Degree of vertex 2: " << graph.grau(graph.getVertex(2)) << std::endl;

//         // Test edge existence.
//         std::cout << "Is there an edge between 1 and 2? " 
//                   << (graph.haAresta(graph.getVertex(1), graph.getVertex(2)) ? "Yes" : "No") 
//                   << std::endl;
//         std::cout << "Is there an edge between 1 and 4? " 
//                   << (graph.haAresta(graph.getVertex(1), graph.getVertex(4)) ? "Yes" : "No") 
//                   << std::endl;

//         // Test edge weights.
//         std::cout << "Weight of the edge between 1 and 2: " 
//                   << graph.peso(graph.getVertex(1), graph.getVertex(2)) << std::endl;
//         std::cout << "Weight of the edge between 2 and 3: " 
//                   << graph.peso(graph.getVertex(2), graph.getVertex(3)) << std::endl;
//         std::cout << "Weight of the edge between 3 and 4: " 
//                   << graph.peso(graph.getVertex(3), graph.getVertex(4)) << std::endl;

//         // Test neighbors.
//         std::cout << "Neighbors of vertex 1: ";
//         for (auto v : graph.vizinhos(graph.getVertex(1))) {
//             std::cout << v->label << " ";
//         }
//         std::cout << std::endl;

//         std::cout << "Neighbors of vertex 2: ";
//         for (auto v : graph.vizinhos(graph.getVertex(2))) {
//             std::cout << v->label << " ";
//         }
//         std::cout << std::endl;

//         // ====== Testing Depth-First Search ======
//         size_t startVertex;
//         std::cout << "\nEnter the starting vertex index for DFS: ";
//         std::cin >> startVertex;
//         if (startVertex < 1 || startVertex > graph.qtdVertices()) {
//             std::cerr << "Invalid vertex index! Exiting DFS test." << std::endl;
//         } else {
//             std::cout << "DFS traversal starting from vertex " << startVertex << ":\n";
//             std::vector<size_t> discoveryTimes = DepthFirstSearch(graph, startVertex);
            
//             // Print discovery times for each vertex.
//             std::cout << "Discovery times (0-indexed positions):\n";
//             for (size_t i = 0; i < discoveryTimes.size(); ++i) {
//                 if (discoveryTimes[i] != std::numeric_limits<size_t>::max()) {
//                     std::cout << "Vertex " << i + 1 << ": " << discoveryTimes[i] << std::endl;
//                 } else {
//                     std::cout << "Vertex " << i + 1 << ": Not reached" << std::endl;
//                 }
//             }
//         }

//         // Testing the graph clear function.
//         std::cout << "\nClearing the graph..." << std::endl;
//         graph.clear();
//         std::cout << "Number of vertices after clearing: " << graph.qtdVertices() << std::endl;
//         std::cout << "Number of edges after clearing: " << graph.qtdArestas() << std::endl;
//     }
//     catch (const std::exception& ex) {
//         std::cerr << "Exception: " << ex.what() << std::endl;
//     }
//     return 0;
// }