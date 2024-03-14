#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
//#include "containers/ArraySequence.h"
#include "containers/HashTable.h"
#include "Edges.h"
#include "Path.h"

template <typename TVertex, typename TEdge>
class Graph {
private:
    HashTable<TVertex, Edges<TEdge>> dictionary;
public:
    Graph() : dictionary(10) {}
    Graph(shared_ptr<Sequence<TVertex>> vertices);
    Graph(const Graph&) = delete; // Copy constructor
    void operator=(Graph const &) = delete; // Assignment operator
    ~Graph() {}    // Destruct
    bool ContainsVertex(TVertex vertex) const;
    void AddEdge(TVertex vertex, TEdge edge);
    void AddVertex(TVertex vertex);
    shared_ptr<Sequence<TVertex>> GetVertices() const;
    shared_ptr<Sequence<Pair<TVertex, Edges<TEdge>>>> GetEdgesAndVertices() const;
    Path<TVertex, TEdge> ShortestPath(TVertex startVertex, TVertex finishVertex) const {
        
    }
};
template <typename TVertex, typename TEdge>
Graph<TVertex, TEdge> :: Graph(shared_ptr<Sequence<TVertex>> vertices) {
    auto e = vertices->GetEnumerator();
    while (e->next()) {
        dictionary.Add(**e, Edges<TEdge>());
    }
}
template <typename TVertex, typename TEdge>
bool Graph<TVertex, TEdge> :: ContainsVertex(TVertex vertex) const {
    return dictionary.ContainsKey(vertex);
}
template <typename TVertex, typename TEdge>
void Graph<TVertex, TEdge> :: AddVertex(TVertex vertex) {
    if (!dictionary.ContainsKey(vertex)) {
        dictionary.Add(vertex, Edges<TEdge>());
    }
}

template <typename TVertex, typename TEdge>
void Graph<TVertex, TEdge> :: AddEdge(TVertex vertex, TEdge edge) {
    AddVertex(vertex);
    dictionary[vertex].Add(edge);
}
template <typename TVertex, typename TEdge>
shared_ptr<Sequence<TVertex>> Graph<TVertex, TEdge> :: GetVertices() const {
    return dictionary.GetKeys();
}
template <typename TVertex, typename TEdge>
shared_ptr<Sequence<Pair<TVertex, Edges<TEdge>>>> Graph<TVertex, TEdge> :: GetEdgesAndVertices() const {
    return dictionary.GetPairs();
}