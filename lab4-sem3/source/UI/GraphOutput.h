#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include "../IPrintableVertex.h"
#include "../additional/Colors.h"
#include "../containers/smart_ptrs/shared_ptr.h"
#include "../Graph.h"
#include "../Path.h"

template <typename TVertex>
class GraphOutput {
private:
    shared_ptr<Graph<TVertex, double>> graph;
    inline static const std::string bond = " -> ";
    inline const std::string VertexName(IPrintableVertex& printableVertex) {
        return  printableVertex.GetName();
    }
    inline std::string VertexPrinting(IPrintableVertex& printableVertex) {
        return std::move(printableVertex.PrintableOutput());
    }
    std::string VertexColoredPrinting(shared_ptr<IDictionary<TVertex, int>> colors);
    inline std::string doubleToString(double number) {
        std::string str = std::to_string(number);
        str.erase( str.find_last_not_of('0') + 1, std::string::npos );
        str.erase( str.find_last_not_of('.') + 1, std::string::npos );
        return std::move(str);
    }
    inline std::string EdgePrinting(TVertex vertex1, TVertex vertex2, double weight) {
        return std::move( VertexName(vertex1) + bond + VertexName(vertex2) + "[label=\"" + doubleToString(weight) + "\"]" );
    }
public:
    GraphOutput(const shared_ptr<Graph<TVertex, double>> graph_);
    std::string printEdges();
    std::string printVertices();
    std::string printColoredVertices(std::string printVertices());
    void print();
    virtual void createDotFile(const std::string filename = "./graph.dot");
    void createColoredDotFile(shared_ptr<IDictionary<TVertex, int>> colors, const std::string filename = "./graph.dot");
};
template <typename TVertex> 
GraphOutput<TVertex>  :: GraphOutput(const shared_ptr<Graph<TVertex, double>> graph_) { graph = graph_; }


template <typename TVertex> 
std::string GraphOutput<TVertex> :: printVertices() {
    std::string verticesString = "";
    auto vertices = graph->GetVertices();
    auto e = vertices->GetEnumerator();
    while(e->next()) {
        verticesString.append(VertexPrinting(**e) + '\n');
    }
    return std::move(verticesString);
}
template <typename TVertex>
std::string GraphOutput<TVertex> :: VertexColoredPrinting(shared_ptr<IDictionary<TVertex, int>> colorsNums) {
    std::string verticesString = "";
    auto vertices = graph->GetVertices();
    auto e = vertices->GetEnumerator();
    while(e->next()) {
        verticesString.append(VertexPrinting(**e) + " [color=" + colors[colorsNums->Get(**e)] + "]\n");
    }
    return std::move(verticesString);
}

template <typename TVertex>
std::string GraphOutput<TVertex> :: printEdges() {
    std::string edgesString = "";
    auto pairs = graph->GetEdgesAndVertices();
    auto en = pairs->GetEnumerator();
    while(en->next()) {
        auto edgesEn = ((**en).GetValue()).GetEnumerator();
        while (edgesEn->next()) {
            edgesString.append(EdgePrinting((**en).GetKey(), (**edgesEn).GetDestVertex(), (**edgesEn).GetWeight()) + '\n');
        }
    }
    return std::move(edgesString);
}
template <typename TVertex> 
void GraphOutput<TVertex> :: print() {
    std::cout << printVertices() << printEdges();
}
template <typename TVertex> 
void GraphOutput<TVertex> :: createColoredDotFile(shared_ptr<IDictionary<TVertex, int>> colors, const std::string filename) {
    std::ofstream outfile;
    outfile.open(filename);
    outfile << "digraph {" << std::endl;
    outfile << VertexColoredPrinting(colors) << printEdges() << "}\n";
    outfile.close();
}
template <typename TVertex> 
void GraphOutput<TVertex> :: createDotFile(const std::string filename) {
    std::ofstream outfile;
    outfile.open(filename);
    outfile << "digraph {" << std::endl;
    outfile << printVertices() << printEdges() << "}\n";
    outfile.close();
}

template <typename TVertex>
void PrintPath(Path<TVertex, double> path) {
    if(path.GetLength() == -1) {
        std::cout << "There is no path\n";
        return;
    }
    std::cout << path.GetFirst().PrintableOutput();
    auto e = path.GetEnumerator();
    while(e->next()) {
        std::cout << " -- " << (**e).GetWeight() << " --> " << (**e).GetDestVertex().PrintableOutput();
    }
    std::cout << "\n";   
}