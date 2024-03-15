#include <string>
#include <iostream>
#include "Graph.h"
#include "WeightEdge.h"
#include "ConnectionPoint.h"
#include "containers/SmartPtrLinkedListSequence.h"
#include <string>
#include "UI/GraphOutput.h"
#include "UI/GraphInput.h"

int main() {
    auto graphPointer = shared_ptr<Graph<ConnectionPoint, shared_ptr<WeightEdge<ConnectionPoint>> >>(new Graph<ConnectionPoint, shared_ptr<WeightEdge<ConnectionPoint>> >()); // Create a new graph
    GraphOutput out(graphPointer);
    while(GraphInput(graphPointer)) {
        out.createDotFile();
    }

/*     int  v = 5; // Number of vertices in
    ConnectionPoint cp[] = {ConnectionPoint("A"), ConnectionPoint("B"), ConnectionPoint("C")};
    std::string a[] = {"A", "B", "C", "D", "E"};
    auto verts = shared_ptr<Sequence<std::string>>(new ArraySequence<std::string>(a, v));
    auto graph = shared_ptr<Graph<std::string, shared_ptr<WeightEdge<std::string>> >>(new Graph<std::string, shared_ptr<WeightEdge<std::string>> >(verts)); // Create a new graph
    graph->AddEdge("A", make_shared<WeightEdge<std::string>>("B", 4));
    graph->AddEdge("A", make_shared<WeightEdge<std::string>>("C", 8));
    graph->AddEdge("H", make_shared<WeightEdge<std::string>>("C", 8));
    auto verts2 = shared_ptr<Sequence<ConnectionPoint>>(new SmartPtrLinkedListSequence<ConnectionPoint>(cp, 3));
    auto graph2 = shared_ptr<Graph<ConnectionPoint, shared_ptr<WeightEdge<ConnectionPoint>> >>(new Graph<ConnectionPoint, shared_ptr<WeightEdge<ConnectionPoint>> >(verts2));
    GraphOutput out(graph2);
    graph2->AddEdge(ConnectionPoint("H"), make_shared<WeightEdge<ConnectionPoint>>(ConnectionPoint("C"), 8));
    graph2->AddEdge(ConnectionPoint("C"), make_shared<WeightEdge<ConnectionPoint>>(ConnectionPoint("A"), 4));
    graph2->AddEdge(ConnectionPoint("B"), make_shared<WeightEdge<ConnectionPoint>>(ConnectionPoint("A"), 3));
    graph2->AddEdge(ConnectionPoint("B"), make_shared<WeightEdge<ConnectionPoint>>(ConnectionPoint("A"), 2));

    out.createDotFile(); */
    return 0;
}