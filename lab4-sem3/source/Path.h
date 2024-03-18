#pragma once

#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/SmartPtrLinkedListSequence.h"

template <typename TVertex, typename TEdge>
class Path {
private:
    TVertex startVertex;
    shared_ptr<Sequence<TEdge>> roads;
    size_t length;
public:
    Path() : length(-1) {}
    Path(TVertex startV) : startVertex(startV), roads(new SmartPtrLinkedListSequence<TEdge>()), length(0) {}
    void Append(TEdge edge) {
        roads->Append(edge);
        length += edge->GetWeight();
    }
    shared_ptr<IEnumerator<TEdge>> GetEnumerator() {
        return roads->GetEnumerator();
    }
    TVertex GetFirst() {
        return startVertex;
    }
    void Prepend(TEdge edge) {
        roads->Prepend(edge);
        length += edge->GetWeight();
    }
    size_t GetLength() {
        return length;
    }
};