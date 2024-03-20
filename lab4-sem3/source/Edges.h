#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/ArraySequence.h"
#include "WeightEdge.h"

template <typename TVertex, typename TWeight>
class Edges {
public:
    shared_ptr<Sequence<WeightEdge<TVertex, TWeight>>> edges;
    // Constructors
    Edges() : edges(shared_ptr<Sequence<WeightEdge<TVertex, TWeight>>>(new ArraySequence<WeightEdge<TVertex, TWeight>>())) {}
    Edges(shared_ptr<Sequence<WeightEdge<TVertex, TWeight>>> _edges) : edges(_edges) {}
    Edges(const Edges &other) : edges(other.edges) {}
    void Add(WeightEdge<TVertex, TWeight> edge) {
        edges->Append(edge);
    }
    size_t GetLength() const {
        return edges->GetLength();
    }
    shared_ptr<IEnumerator<WeightEdge<TVertex, TWeight>>> GetEnumerator() {
        return edges->GetEnumerator();
    }
    bool Remove(WeightEdge<TVertex, TWeight> edge) {
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