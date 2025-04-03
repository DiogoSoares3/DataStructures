#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <list>

template<typename Tp>
class WeightedUndirectedGraph {
private:
    struct Edge;

    struct Vertex {
        Tp label;              // Vertex label
        std::list<Edge*> adj;  // Adjacency list (edges connected to this vertex)
        size_t degree;
        size_t index;

        Vertex(const Tp& labelValue, const size_t& indexValue);
    };

    struct Edge {
        Vertex* u, *v;  // The two endpoints of the edge
        double weight;  // Weight of the edge

        Edge(const double& weightValue);
    };

    std::vector<Vertex*> vertices;   // Vector of vertices
    size_t numEdges;            // Total number of unique edges

public:
    WeightedUndirectedGraph(const std::string&);

    ~WeightedUndirectedGraph();

    // Returns the number of vertices in the graph.
    size_t qtdVertices() const;

    // Returns the number of edges in the graph.
    size_t qtdArestas() const;

    // Returns the degree (number of incident edges) of vertex v.
    size_t grau(Vertex* v) const;

    // Returns the label of vertex v.
    Tp rotulo(Vertex* v) const;

    // Returns a vector containing the indices of the neighbors of vertex v.
    std::vector<Vertex*> vizinhos(Vertex* v) const;

    // Returns true if an edge exists between vertices u and v, false otherwise.
    bool haAresta(Vertex* u, Vertex* v) const;

    // Returns the weight of the edge between u and v.
    // If the edge does not exist, returns positive infinity.
    double peso(Vertex* u, Vertex* v) const;

    // Return the Vertex pointer given a certain index
    Vertex* getVertex(size_t index) const;

    void clear();
};