#pragma once

#include <limits>

#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/SmartPtrLinkedListSequence.h"
#include "containers/HashTable.h"
#include "Edges.h"
#include "Path.h"
#include "containers/SortedSequence.h"
#include "Graph.h"
#include "VertexComparators.h"


template <typename TVertex, typename TEdge>
class GraphAlgorithms : public Graph<TVertex, TEdge> {
public:
    GraphAlgorithms() : Graph<TVertex, TEdge>() {}
    GraphAlgorithms(shared_ptr<Sequence<TVertex>> vertices) : Graph<TVertex, TEdge>(vertices) {}
    GraphAlgorithms(const Graph<TVertex, TEdge>& graph) : Graph<TVertex, TEdge>(graph) {}
    void operator=(Graph<TVertex, TEdge> const &) = delete; // Assignment operator
    ~GraphAlgorithms() {}
    Path<TVertex, TEdge> Dijkstra(TVertex startVertex, TVertex finishVertex) {
        if ( !(this->ContainsVertex(startVertex) && this->ContainsVertex(finishVertex))) 
            return Path<TVertex, TEdge>();
        if (startVertex == finishVertex)
            return Path<TVertex, TEdge>(startVertex);
        auto vertices = this->GetVertices();
        auto unvisited = shared_ptr<SmartPtrLinkedListSequence<TVertex>>(new SmartPtrLinkedListSequence<TVertex>(vertices.get()));
        auto visited = shared_ptr<SmartPtrLinkedListSequence<TVertex>>(new SmartPtrLinkedListSequence<TVertex>());
        HashTable<TVertex, Pair<double, Pair<TVertex, TEdge>>> table(this->dictionary.GetCapacity());

        auto e = vertices->GetEnumerator();
        while (e->next()) {
            table.Add(**e, Pair<double, Pair<TVertex, TEdge>>(std::numeric_limits<double>::max()));
        }

        table[startVertex].SetKey(0); // set first vertex
        while(unvisited->GetLength() > 0) { // while unvisited vertecies left
            auto u = unvisited->GetEnumerator(); 
            double min = std::numeric_limits<double>::max();
            TVertex minVert; // min unvisited
            int index = 0, minIndex = 0;
            while(u->next()) {
                double pathLen = table[**u].GetKey();
                if (pathLen <= min) {
                    min = pathLen;
                    minVert = **u;
                    minIndex = index;
                }
                ++index;
            }

            auto dIter = this->dictionary[minVert].GetEnumerator(); // minVert's neighbour vertecies
            while(dIter->next()) {
                int index = unvisited->findByValue((**dIter)->GetDestVertex());
                if (unvisited->findByValue((**dIter)->GetDestVertex()) != -1) { // if unvisited
                    double newLength = min + (**dIter)->GetWeight();
                    if (newLength < table[(**dIter)->GetDestVertex()].GetKey()) {
                        table[(**dIter)->GetDestVertex()] = Pair<double, Pair<TVertex, TEdge>>(newLength, Pair<TVertex, TEdge>(minVert, **dIter));
                    }
                }
            }
            std::cout << unvisited->GetLength() << '\n';            
            visited->Append(minVert);
            std::cout << "minIndex" << minIndex << "\n";
            unvisited->Remove(minIndex);
        }
        // finding path
        TVertex LastVertex = finishVertex;
        Path<TVertex, TEdge> path(startVertex);
        if (table[LastVertex].GetKey() > std::numeric_limits<double>::max() - 1000) {
            return Path<TVertex, TEdge>();
        }
        while(true) {
            path.Prepend(table[LastVertex].GetValue().GetValue());
            LastVertex = table[LastVertex].GetValue().GetKey();
            if (LastVertex == startVertex)
                break;
        }
        return path;
    }
};