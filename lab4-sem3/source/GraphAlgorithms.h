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


template <typename TVertex, typename TWeight>
class GraphAlgorithms : public Graph<TVertex, TWeight> {
public:
    GraphAlgorithms() : Graph<TVertex, TWeight>() {}
    GraphAlgorithms(shared_ptr<Sequence<TVertex>> vertices) : Graph<TVertex, TWeight>(vertices) {}
    GraphAlgorithms(const Graph<TVertex, TWeight>& graph) : Graph<TVertex, TWeight>(graph) {}
    void operator=(Graph<TVertex, TWeight> const &) = delete; // Assignment operator
    ~GraphAlgorithms() {}
    Path<TVertex, TWeight> Dijkstra(TVertex startVertex, TVertex finishVertex) {
        if ( !(this->ContainsVertex(startVertex) && this->ContainsVertex(finishVertex))) 
            return Path<TVertex, TWeight>();
        if (startVertex == finishVertex)
            return Path<TVertex, TWeight>(startVertex);
        auto vertices = this->GetVertices();
        auto unvisited = shared_ptr<SmartPtrLinkedListSequence<TVertex>>(new SmartPtrLinkedListSequence<TVertex>(vertices.get()));
        auto visited = shared_ptr<SmartPtrLinkedListSequence<TVertex>>(new SmartPtrLinkedListSequence<TVertex>());
        HashTable<TVertex, Pair<TWeight, Pair<TVertex, WeightEdge<TVertex, TWeight>>>> table(this->dictionary.GetCapacity());

        auto e = vertices->GetEnumerator();
        while (e->next()) {
            table.Add(**e, Pair<TWeight, Pair<TVertex, WeightEdge<TVertex, TWeight>>>(std::numeric_limits<TWeight>::max()-1));
        }

        table[startVertex].SetKey(0); // set first vertex
        while(unvisited->GetLength() > 0) { // while unvisited vertecies left
            auto u = unvisited->GetEnumerator(); 
            TWeight min = std::numeric_limits<TWeight>::max();
            TVertex minVert; // min unvisited
            int index = 0, minIndex = 0;
            while(u->next()) {
                TWeight pathLen = table[**u].GetKey();
                if (pathLen <= min) {
                    min = pathLen;
                    minVert = **u;
                    minIndex = index;
                }
                ++index;
            }

            auto dIter = this->dictionary[minVert].GetKey().GetEnumerator(); // minVert's neighbour vertecies
            while(dIter->next()) {
                int index = unvisited->findByValue((**dIter).GetDestVertex());
                if (unvisited->findByValue((**dIter).GetDestVertex()) != -1) { // if unvisited
                    TWeight newLength = min + (**dIter).GetWeight();
                    if (newLength < table[(**dIter).GetDestVertex()].GetKey()) {
                        table[(**dIter).GetDestVertex()] = Pair<TWeight, Pair<TVertex, WeightEdge<TVertex, TWeight>>>(newLength, Pair<TVertex, WeightEdge<TVertex, TWeight>>(minVert, **dIter));
                    }
                }
            }
            //std::cout << unvisited->GetLength() << '\n';            
            visited->Append(minVert);
            //std::cout << "minIndex" << minIndex << "\n";
            unvisited->Remove(minIndex);
        }
        // finding path
        TVertex LastVertex = finishVertex;
        Path<TVertex, TWeight> path(startVertex);
        if (table[LastVertex].GetKey() >= std::numeric_limits<TWeight>::max() - 1000) {
            return Path<TVertex, TWeight>();
        }
        while(true) {
            path.Prepend(table[LastVertex].GetValue().GetValue());
            LastVertex = table[LastVertex].GetValue().GetKey();
            if (LastVertex == startVertex)
                break;
        }
        return path;
    }
 /*    IDictionary<TVertex, int>* Color() {
		IDictionary<TVertex, int>* coloredVertices = HashTable<TVertex, int>(this->dictionary.GetCapacity());
		std::vector<bool> usedColors;

		for (std::size_t i = 0; i < vertices.size(); i++)
		{
			usedColors.push_back(false);
		}

		for (std::size_t j = 0; j < vertices.size(); j++)
		{
			TVertex currentVertex = vertices[j];
			std::vector<Edge>adjVertices = container->Get(currentVertex);
			for (std::size_t i = 0; i < adjVertices.size(); i++)
			{
				if (coloredVertices->ContainsKey(adjVertices[i].second()))
					usedColors[coloredVertices->Get(adjVertices[i].second())] = true;
			}

			int currentColor = 0;

			for (std::size_t i = 0; i < usedColors.size(); i++)
			{
				if (!usedColors[i])
				{
					currentColor = i;
					break;
				}
			}

			coloredVertices->Add(currentVertex, currentColor);

			for (std::size_t i = 0; i < vertices.size(); i++)
			{
				usedColors[i] = false;
			}
		}

		return coloredVertices;
	} */
};