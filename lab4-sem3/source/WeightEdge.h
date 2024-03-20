#pragma once

template <typename TVertex, typename TWeight> 
class WeightEdge {
protected:
    TVertex destinationVertex;
    TWeight weight;
public:
    WeightEdge() {}
    WeightEdge(TVertex _destinationVertex, TWeight _weight) : destinationVertex(_destinationVertex), weight(_weight) {}
    TWeight GetWeight() {
        return weight;
    }
    TVertex& GetDestVertex() {
        return destinationVertex;
    }
    bool operator==(const WeightEdge<TVertex, TWeight>& edge) {
        return destinationVertex == edge.destinationVertex && weight == edge.weight;
    }
};
