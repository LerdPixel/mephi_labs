#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "../IPrintableVertex.h"
#include "../containers/smart_ptrs/shared_ptr.h"
#include "../Graph.h"

template <typename TVertex, typename TEdge>
class GraphOutput {
private:
    shared_ptr<Graph<TVertex, TEdge>> graph;
    inline static const std::string bond = " -> ";
    inline const std::string VertexName(IPrintableVertex& printableVertex) {
        return  printableVertex.GetName();
    }
    inline const std::string VertexPrinting(IPrintableVertex& printableVertex) {
        return printableVertex.PrintableOutput();
    }
    inline std::string doubleToString(double number) {
        std::string str = std::to_string(number);
        str.erase( str.find_last_not_of('0') + 1, std::string::npos );
        str.erase( str.find_last_not_of('.') + 1, std::string::npos );
        return std::move(str);
    }
    inline std::string EdgePrinting(TVertex vertex, TEdge edge) {
        return std::move( VertexName(vertex) + bond + VertexName(edge->GetDestVertex()) + "[label=\"" + doubleToString(edge->GetWeight()) + "\"]" );
    }
public:
    GraphOutput(const shared_ptr<Graph<TVertex, TEdge>> graph_);
    std::string printEdges();
    std::string printVertices();
    void print();
    virtual void createDotFile(const std::string filename = "./graph.dot");
};
template <typename TVertex, typename TEdge> 
GraphOutput<TVertex, TEdge> :: GraphOutput(const shared_ptr<Graph<TVertex, TEdge>> graph_) { graph = graph_; }


template <typename TVertex, typename TEdge> 
std::string GraphOutput<TVertex, TEdge> :: printVertices() {
    std::string verticesString = "";
    auto vertices = graph->GetVertices();
    auto e = vertices->GetEnumerator();
    while(e->next()) {
        verticesString.append(VertexPrinting(**e) + '\n');
    }
    return std::move(verticesString);
}
template <typename TVertex, typename TEdge> 
std::string GraphOutput<TVertex, TEdge> :: printEdges() {
    std::string edgesString = "";
    auto pairs = graph->GetEdgesAndVertices();
    auto en = pairs->GetEnumerator();
    while(en->next()) {
        auto edgesEn = ((**en).GetValue()).GetEnumerator();
        while (edgesEn->next()) {
            edgesString.append(EdgePrinting((**en).GetKey(), **edgesEn) + '\n');
        }
    }
    return std::move(edgesString);
}
template <typename TVertex, typename TEdge> 
void GraphOutput<TVertex, TEdge> :: print() {
    std::cout << printVertices() << printEdges();
}
template <typename TVertex, typename TEdge> 
void GraphOutput<TVertex, TEdge> :: createDotFile(const std::string filename) {
    std::ofstream outfile;
    outfile.open(filename);
    outfile << "digraph {" << std::endl;
    outfile << printVertices() << printEdges() << "}\n";
    outfile.close();
}
