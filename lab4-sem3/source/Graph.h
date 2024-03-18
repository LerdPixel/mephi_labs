#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/HashTable.h"
#include "Edges.h"
#include "Path.h"

template <typename TVertex, typename TEdge>
class Graph {
protected:
    HashTable<TVertex, Edges<TEdge>> dictionary;
public:
    Graph() : dictionary(10) {}
    Graph(shared_ptr<Sequence<TVertex>> vertices);
    Graph(const Graph& other); // Copy constructor
    //void operator=(Graph const &) = delete; // Assignment operator
    ~Graph() {}    // Destruct
    bool ContainsVertex(TVertex vertex);
    void AddEdge(TVertex vertex, TEdge edge);
    void AddVertex(TVertex vertex);
    bool DeleteEdge(TVertex vertex, TEdge edge);
    shared_ptr<Sequence<TVertex>> GetVertices() const;
    shared_ptr<Sequence<Pair<TVertex, Edges<TEdge>>>> GetEdgesAndVertices() const;
};
template <typename TVertex, typename TEdge>
Graph<TVertex, TEdge> :: Graph(shared_ptr<Sequence<TVertex>> vertices) {
    auto e = vertices->GetEnumerator();
    while (e->next()) {
        dictionary.Add(**e, Edges<TEdge>());
    }
}
template <typename TVertex, typename TEdge>
Graph<TVertex, TEdge> :: Graph(const Graph& other) {
    auto pairs = other.GetEdgesAndVertices();
    auto e = pairs->GetEnumerator();
    while (e->next()) {
        dictionary.Add((**e).GetKey(), (**e).GetValue());
    }
}
template <typename TVertex, typename TEdge>
bool Graph<TVertex, TEdge> :: ContainsVertex(TVertex vertex) {
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
    AddVertex(edge->GetDestVertex());
    dictionary[vertex].Add(edge);
}
template <typename TVertex, typename TEdge>
bool Graph<TVertex, TEdge> :: DeleteEdge(TVertex vertex, TEdge edge) {
    if (dictionary.ContainsKey(vertex)) {
        return dictionary.Get(vertex).Remove(edge);
    }
    return false;
}

template <typename TVertex, typename TEdge>
shared_ptr<Sequence<TVertex>> Graph<TVertex, TEdge> :: GetVertices() const {
    return dictionary.GetKeys();
}
template <typename TVertex, typename TEdge>
shared_ptr<Sequence<Pair<TVertex, Edges<TEdge>>>> Graph<TVertex, TEdge> :: GetEdgesAndVertices() const {
    return dictionary.GetPairs();
}