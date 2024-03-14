#pragma once

template <typename TVertex> 
class WeightEdge {
    TVertex destinationVertex;
    double weight;
public:
    WeightEdge(TVertex _destinationVertex) : destinationVertex(_destinationVertex), weight(1) {}
    WeightEdge(TVertex _destinationVertex, double _weight) : destinationVertex(_destinationVertex), weight(_weight) {}
    double GetWeight() {
        return weight;
    }
    TVertex GetDestVertex() {
        return destinationVertex;
    }
};
