#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/HashTable.h"
#include "WeightEdge.h"
#include "Edges.h"
#include "Path.h"

template <typename TVertex, typename TWeight>
class Graph {
protected:
    HashTable<TVertex, Pair<Edges<TVertex, TWeight>, Edges<TVertex, TWeight>>> dictionary;
public:
    Graph() : dictionary(10) {}
    Graph(shared_ptr<Sequence<TVertex>> vertices);
    //Graph(const Graph& other); // Copy constructor
    ~Graph() {} // Destruct
    bool ContainsVertex(TVertex vertex);
    void AddEdge(TVertex vertex1, TVertex vertex2, TWeight weight);
    void AddVertex(TVertex vertex);
    bool DeleteEdge(TVertex vertex1, TVertex vertex2, TWeight weight);
    shared_ptr<Sequence<TVertex>> GetVertices() const;
    shared_ptr<Sequence<Pair<TVertex, Edges<TVertex, TWeight>>>> GetEdgesAndVertices() const;
};
template <typename TVertex, typename TWeight>
Graph<TVertex, TWeight> :: Graph(shared_ptr<Sequence<TVertex>> vertices) {
    auto e = vertices->GetEnumerator();
    while (e->next()) {
        dictionary.Add(**e, Pair<Edges<TVertex, TWeight>, Edges<TVertex, TWeight>>(Edges<TVertex, TWeight>(), Edges<TVertex, TWeight>()));
    }
}
/* template <typename TVertex, typename TWeight>
Graph<TVertex, TWeight> :: Graph(const Graph& other) {
    auto pairs = other.GetEdgesAndVertices();
    auto e = pairs->GetEnumerator();
    while (e->next()) {
        dictionary.Add((**e).GetKey(), (**e).GetValue());
    }
} */
template <typename TVertex, typename TWeight>
bool Graph<TVertex, TWeight> :: ContainsVertex(TVertex vertex) {
    return dictionary.ContainsKey(vertex);
}
template <typename TVertex, typename TWeight>
void Graph<TVertex, TWeight> :: AddVertex(TVertex vertex) {
    if (!dictionary.ContainsKey(vertex)) {
        dictionary.Add(vertex, Pair<Edges<TVertex, TWeight>, Edges<TVertex, TWeight>>(Edges<TVertex, TWeight>(), Edges<TVertex, TWeight>()));
    }
}

template <typename TVertex, typename TWeight>
void Graph<TVertex, TWeight> :: AddEdge(TVertex vertex1, TVertex vertex2, TWeight weight) {
    AddVertex(vertex1);
    AddVertex(vertex2);
    dictionary[vertex1].GetKey().Add(WeightEdge<TVertex, TWeight>(vertex2, weight));
    dictionary[vertex2].GetValue().Add(WeightEdge<TVertex, TWeight>(vertex1, weight));
}
template <typename TVertex, typename TWeight>
bool Graph<TVertex, TWeight> :: DeleteEdge(TVertex vertex1, TVertex vertex2, TWeight weight) {
    if (dictionary.ContainsKey(vertex1) && dictionary.ContainsKey(vertex2)) {
        return dictionary.Get(vertex1).GetKey().Remove(WeightEdge<TVertex, TWeight>(vertex2, weight)) && dictionary.Get(vertex2).GetValue().Remove(WeightEdge<TVertex, TWeight>(vertex1, weight));
    }
    return false;
}

template <typename TVertex, typename TWeight>
shared_ptr<Sequence<TVertex>> Graph<TVertex, TWeight> :: GetVertices() const {
    return dictionary.GetKeys();
}
template <typename TVertex, typename TWeight>
shared_ptr<Sequence<Pair<TVertex, Edges<TVertex, TWeight>>>> Graph<TVertex, TWeight> :: GetEdgesAndVertices() const {
    auto roughPairs = dictionary.GetPairs();
    auto pairs = shared_ptr<Sequence<Pair<TVertex, Edges<TVertex, TWeight>>>>(new SmartPtrLinkedListSequence<Pair<TVertex, Edges<TVertex, TWeight>>>());
    auto e = roughPairs->GetEnumerator();
    while (e->next()) {
        pairs->Prepend(Pair<TVertex, Edges<TVertex, TWeight>>((**e).GetKey(), (**e).GetValue().GetKey()));
    }
    return pairs;
}