#include <string>
#include <iostream>
#include "Graph.h"
#include "WeightEdge.h"
//#include "СonnectionPoint.h"
#include <string>
#include <graphviz/gvc.h>

int main() {
    int  v = 5; // Number of vertices in
    std::string a[] = {"A", "B", "C", "D", "E"};
    auto verts = shared_ptr<Sequence<std::string>>(new ArraySequence<std::string>(a, v));
    auto graph = Graph<std::string, shared_ptr<WeightEdge<std::string>> >(verts); // Create a new graph
    graph.AddEdge("A", make_shared<WeightEdge<std::string>>("B", 4));
    graph.AddEdge("A", make_shared<WeightEdge<std::string>>("C", 8));
    graph.AddEdge("H", make_shared<WeightEdge<std::string>>("C", 8));
    auto vertices = graph.GetVertices();
    auto e = vertices->GetEnumerator();
    while(e->next()) {
        std::cout << **e << '\n';
    }
    auto pairs = graph.GetEdgesAndVertices();
    auto en = pairs->GetEnumerator();
    while(en->next()) {
        auto edgesEn = ((**en).GetValue()).GetEnumerator();
        while (edgesEn->next()) {
            std::cout << (**en).GetKey() << " ---> " << (**edgesEn)->GetDestVertex() << "  " << (**edgesEn)->GetWeight() << '\n';
        }
    }
    return 0;
}