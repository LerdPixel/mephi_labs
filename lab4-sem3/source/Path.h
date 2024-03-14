#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/ArraySequence.h"

template <typename TVertex, typename TEdge>
class Path {
private:
    TVertex startVertex;
    shared_ptr<Sequence<TEdge>> roads;
public:
    Path(TVertex startV) : startVertex(startV), roads(new ArraySequence<TEdge>()) {}
    void Add(TEdge edge) {
        roads.Append(edge);
    }
};