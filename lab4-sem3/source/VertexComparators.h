#pragma once

template <typename TVertex>
bool VertexComparator(Pair<TVertex, double> a, Pair<TVertex, double> b) {
    return (a.GetValue < b.GetValue);
}

template <typename TVertex>
bool VertexIsEqual(Pair<TVertex, double> a, Pair<TVertex, double> b) {
    return (a.GetKey == b.GetKey);
}