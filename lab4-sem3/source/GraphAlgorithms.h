#pragma once

#include <limits>
#include <vector>
#include <cstdio>

#include "containers/smart_ptrs/shared_ptr.h"
#include "containers/SmartPtrLinkedListSequence.h"
#include "containers/HashTable.h"
#include "containers/IDictionary.h"
#include "Edges.h"
#include "Path.h"
#include "containers/SortedSequence.h"
#include "Graph.h"
#include "VertexComparators.h"


template <typename TVertex, typename TWeight>
class GraphAlgorithms : public Graph<TVertex, TWeight> {
private:
    template <typename Callable>
    void AbstructDFS(TVertex& vertex, shared_ptr<IDictionary<TVertex, bool>> table, Callable GetEdges) {
        (*table)[vertex] = true;
        auto eEdge = GetEdges(vertex).GetEnumerator();
        while (eEdge->next()) {
            TVertex adjacentVertex = (**eEdge).GetDestVertex();
            if (!(*table)[adjacentVertex])
               AbstructDFS(adjacentVertex, table, GetEdges);
        }
    }
    void Intersection(shared_ptr<IDictionary<TVertex, bool>> note, shared_ptr<IDictionary<TVertex, bool>> comp) {
        auto keys = this->GetVertices();
        for (int i = 0; i < keys->GetLength(); ++i) {
            (*note)[keys->Get(i)] = (*note)[keys->Get(i)] && (*comp)[keys->Get(i)];
        }
    }
    Edges<TVertex, TWeight> GetOutgoingEdges(TVertex vertex) {
        return this->dictionary[vertex].GetKey();
    }
    Edges<TVertex, TWeight> GetIncomingEdges(TVertex vertex) {
        return this->dictionary[vertex].GetValue();
    }
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
            visited->Append(minVert);
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
    shared_ptr<IDictionary<TVertex, int>> Coloring() {
		shared_ptr<IDictionary<TVertex, int>> coloredVertices = shared_ptr<IDictionary<TVertex, int>>(new HashTable<TVertex, int>(this->dictionary.GetCapacity()));
		std::vector<bool> usedColors;
        auto verticies = this->GetVertices();
        auto currentVertex = verticies->GetEnumerator();
		for (int i = 0; i < verticies->GetLength(); ++i) {
			usedColors.push_back(false);
		}

		while (currentVertex->next()) {
			auto eInternal = this->dictionary.Get(**currentVertex).GetKey().GetEnumerator(), eExternal = this->dictionary.Get(**currentVertex).GetValue().GetEnumerator();
			while (eInternal->next()) {
				if (coloredVertices->ContainsKey((**eInternal).GetDestVertex()))
					usedColors[coloredVertices->Get((**eInternal).GetDestVertex())] = true;
			}
            while (eExternal->next()) {
				if (coloredVertices->ContainsKey((**eExternal).GetDestVertex()))
					usedColors[coloredVertices->Get((**eExternal).GetDestVertex())] = true;
			}
			int currentColor = 0;
			for (int i = 0; i < usedColors.size(); ++i) {
				if (!usedColors[i]) {
					currentColor = i;
					break;
				}
			}
			coloredVertices->Add(**currentVertex, currentColor);
			for (std::size_t i = 0; i < verticies->GetLength(); ++i) {
				usedColors[i] = false;
			}
		}
		return coloredVertices;
	}
    shared_ptr<IDictionary<TVertex, bool>> DFS(TVertex vertex) {
        if (!this->ContainsVertex(vertex))
            throw std::runtime_error("Given vertex is absent");
        shared_ptr<IDictionary<TVertex, bool>> table = shared_ptr<IDictionary<TVertex, bool>>(new HashTable<TVertex, bool>(this->GetVertices(), false));
        AbstructDFS(vertex, table, std::bind(&GraphAlgorithms<TVertex, TWeight>::GetOutgoingEdges, *this, std::placeholders::_1));
        return table;
    }
    shared_ptr<IDictionary<TVertex, bool>> ReverseDFS(TVertex vertex) {
        if (!this->ContainsVertex(vertex))
            throw std::runtime_error("Given vertex is absent");
        shared_ptr<IDictionary<TVertex, bool>> table = shared_ptr<IDictionary<TVertex, bool>>(new HashTable<TVertex, bool>(this->GetVertices(), false));
        AbstructDFS(vertex, table, std::bind(&GraphAlgorithms<TVertex, TWeight>::GetIncomingEdges, *this, std::placeholders::_1));
        return table;
    }
    shared_ptr<IDictionary<TVertex, int>> StronglyConnectedComponents() { // Kosaraju's Algorithm
        shared_ptr<Sequence<TVertex>> vertecies = this->GetVertices();
        shared_ptr<IDictionary<TVertex, int>> table = shared_ptr<IDictionary<TVertex, int>>(new HashTable<TVertex, int>(vertecies, -1));
        int currentGroup = 0;
        auto eVertex = vertecies->GetEnumerator();
        while(eVertex->next()) {
            if (table->Get(**eVertex) != -1) continue;
            shared_ptr<IDictionary<TVertex, bool>> straight = DFS(**eVertex);
            shared_ptr<IDictionary<TVertex, bool>> reversed = ReverseDFS(**eVertex);
            Intersection(straight, reversed);
            auto eGroup = vertecies->GetEnumerator();
            while (eGroup->next()) {
                if ((*straight)[**eGroup]) {
                    (*table)[**eGroup] = currentGroup;
                }
            }
            ++currentGroup;
        }
        return table;
    }
};