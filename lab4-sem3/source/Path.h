#pragma once

#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/SmartPtrLinkedListSequence.h"
#include "WeightEdge.h"

template <typename TVertex, typename TWeight>
class Path {
private:
    TVertex startVertex;
    shared_ptr<Sequence<WeightEdge<TVertex, TWeight>>> roads;
    size_t length;
public:
    Path() : length(-1) {}
    Path(TVertex startV) : startVertex(startV), roads(new SmartPtrLinkedListSequence<WeightEdge<TVertex, TWeight>>()), length(0) {}
    void Append(WeightEdge<TVertex, TWeight> edge) {
        roads->Append(edge);
        length += edge->GetWeight();
    }
    shared_ptr<IEnumerator<WeightEdge<TVertex, TWeight>>> GetEnumerator() {
        return roads->GetEnumerator();
    }
    TVertex GetFirst() {
        return startVertex;
    }
    void Prepend(WeightEdge<TVertex, TWeight> edge) {
        roads->Prepend(edge);
        length += edge.GetWeight();
    }
    size_t GetLength() {
        return length;
    }
};