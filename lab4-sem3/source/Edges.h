#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/ArraySequence.h"

template <typename TEdge>
class Edges {
public:
    shared_ptr<Sequence<TEdge>> edges;
    // Constructors
    Edges() : edges(shared_ptr<Sequence<TEdge>>(new ArraySequence<TEdge>())) {}
    Edges(shared_ptr<Sequence<TEdge>> _edges) : edges(_edges) {}
    Edges(const Edges &other) : edges(other.edges) {}
    void Add(TEdge edge) {
        edges->Append(edge);
    }
    size_t GetLength() const {
        return edges->GetLength();
    }
    shared_ptr<IEnumerator<TEdge>> GetEnumerator() {
        return edges->GetEnumerator();
    }
    bool Remove(TEdge edge) {
        auto e = edges->GetEnumerator();
        int i = 0;
        while(e->next()) {
            if (**e == edge) {
                edges->Remove(i);
                return true;
            }
            ++i;
        }
        return false;
    }
    ~Edges() {}
};