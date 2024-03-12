#pragma once
#include "smart_ptrs/shared_ptr.h"
#include "ArraySequence.h"

template <typename TEdge>
class Edges {
public:
    shared_ptr<Sequence<TEdge>> edges;
    // Constructors
    Edges() : edges(shared_ptr<Sequence<TEdge>>(new ArraySequence<TEdge>())) {}
    Edges(shared_ptr<Sequence<TEdge>> _edges) : edges(_edges) {}
    Edges(const Edges &other) : edges(other.edges) {}
    ~Edges() {}
};