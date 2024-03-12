#pragma once
#include "smart_ptrs/shared_ptr.h"
#include "ArraySequence.h"
#include "HashTable.h"
#include "Edges.h"

template <typename TVertex, typename TEdge>
class Graph {
private:
    HashTable<TVertex, Edges<TEdge>> dictionary;
public:
    Graph(shared_ptr<Sequence<TVertex>> vertices) {
        auto e = vertices->GetEnumerator();
        while (e->next()) {
            dictionary.Add(**e, Edges<TEdge>());
        }
    }
    Graph(const Graph&) = delete; // Copy constructor
    void operator=(Graph const &) = delete; // Assignment operator
    ~Graph() {}    // Destruct
    bool ContainsVertex(TVertex vertex) const {
        return dictionary.ContainsKey(vertex);
    }
    void AddEdge(TEdge edge) {}
    void AddVertex(TVertex vertex) {
        if (!dictionary.ContainsKey(vertex)) {
            
        }
    }
};