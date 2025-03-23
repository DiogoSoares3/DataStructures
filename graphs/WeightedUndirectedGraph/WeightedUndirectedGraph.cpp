#include <vector>
#include <string>
#include <limits>
#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include "WeightedUndirectedGraph.h"


template class WeightedUndirectedGraph<std::string>;

template<typename Tp>
WeightedUndirectedGraph<Tp>::Vertex::Vertex(const Tp& labelValue, const size_t& indexValue) : label(labelValue), adj(), degree(0), index(indexValue) { }

template<typename Tp>
WeightedUndirectedGraph<Tp>::Edge::Edge(const double& weightValue) : u(nullptr), v(nullptr), weight(weightValue) { } 

template<typename Tp>
WeightedUndirectedGraph<Tp>::WeightedUndirectedGraph(const std::string& filename) : numEdges(0) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        throw std::runtime_error("Error opening file: " + filename);
    }
    
    std::string token;

    // Expecting a line starting with "*vertices"
    infile >> token;
    if (token != "*vertices") {
        throw std::runtime_error("Invalid file format: Missing '*vertices' header");
    }
    
    // Read number of vertices
    size_t n;
    infile >> n;

    this->vertices.resize(n, nullptr);

    for (size_t i = 0; i < n; i++) {
        size_t vertexIndex;
        Tp vertexLabel;

        infile >> vertexIndex;
        infile >> vertexLabel;

        this->vertices[vertexIndex-1] = new Vertex(vertexLabel, vertexIndex);
    }

    // Expecting the "*edges" marker next
    infile >> token;
    if (token != "*edges") {
        throw std::runtime_error("Invalid file format: Missing '*edges' header");
    }

    size_t uIndex, vIndex;
    double weight;

    // Read edge definitions until end-of-file
    while (infile >> uIndex >> vIndex >> weight) {
        Vertex* u = this->vertices[uIndex-1];
        Vertex* v = this->vertices[vIndex-1];

        Edge* uniqueEdge = new Edge(weight);
        uniqueEdge->u = u;
        uniqueEdge->v = v;

        u->adj.push_back(uniqueEdge);
        u->degree++;

        v->adj.push_back(uniqueEdge);
        v->degree++;

        this->numEdges++;
    }

    infile.close();
}

template<typename Tp>
WeightedUndirectedGraph<Tp>::~WeightedUndirectedGraph() {
    this->clear();
}

// Returns the number of vertices in the graph.
template<typename Tp>
size_t WeightedUndirectedGraph<Tp>::qtdVertices() const {
    return this->vertices.size();
}

// Returns the number of edges in the graph.
template<typename Tp>
size_t WeightedUndirectedGraph<Tp>::qtdArestas() const {
    return this->numEdges;
}

// Returns the degree (number of incident edges) of vertex v.
template<typename Tp>
size_t WeightedUndirectedGraph<Tp>::grau(Vertex* v) const {
    return v->degree;
}

// Returns the label of vertex v
template<typename Tp>
Tp WeightedUndirectedGraph<Tp>::rotulo(Vertex* v) const {
    return v->label;
}

// Returns a vector containing the indices of the neighbors of vertex v.
template<typename Tp>
std::vector<typename WeightedUndirectedGraph<Tp>::Vertex*> WeightedUndirectedGraph<Tp>::vizinhos(Vertex* v) const {
    if (!(v->degree)) {
        throw std::out_of_range("This vertex doesn't have neighbors");  
    }

    std::vector<Vertex*> neighbors;
    for (Edge* edge : v->adj) {
        if (edge->v == v) {
            neighbors.push_back(edge->u);
        } else {
            neighbors.push_back(edge->v);
        }
    }

    return neighbors;
}

// Returns true if an edge exists between vertices u and v, false otherwise.
template<typename Tp>
bool WeightedUndirectedGraph<Tp>::haAresta(Vertex* u, Vertex* v) const {
    for (Edge* edge : u->adj) {
        if (edge->v == v) {
            return true;
        }
    }
    return false;
}

// Returns the weight of the edge between u and v.
// If the edge does not exist, returns positive infinity.
template<typename Tp>
double WeightedUndirectedGraph<Tp>::peso(Vertex* u, Vertex* v) const {
    for (Edge* edge : u->adj) {
        if (edge->v == v) {
            return edge->weight;
        }
    }
    return std::numeric_limits<double>::infinity();
}


// Returns a pointer to the vertex (node) at the given index
template<typename Tp>
typename WeightedUndirectedGraph<Tp>::Vertex* WeightedUndirectedGraph<Tp>::getVertex(size_t index) const {
    if (index == 0 || index > this->vertices.size()) {  // Verifying if 'index <= 0' because we are using index 1 as the first index on the entry files
        throw std::out_of_range("Invalid vertex index");
    }

    return this->vertices[index-1];
}

template<typename Tp>
void WeightedUndirectedGraph<Tp>::clear() {
    std::unordered_set<Edge*> deletedEdges;  // Using a hash set to avoid deleting the same edge twice

    for (Vertex* node : this->vertices) {
        for (Edge*& edge : node->adj) {  // Reference to modify directly
            if (deletedEdges.find(edge) == deletedEdges.end()) {  // If the iterator didn't find the edge
                delete edge;  
                deletedEdges.insert(edge);
            }
        }
        node->adj.clear();
        delete node;
    }

    this->vertices.clear();
    this->numEdges = 0;
}