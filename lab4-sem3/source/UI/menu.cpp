#include "menu.h"

void EdgesInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out) {
    while(EdgeInput(graphPointer, std::bind(&Graph<ConnectionPoint, double>::AddEdge, *graphPointer, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))) {
        out.createDotFile();
    }
}
void EdgeRemoving(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out) {
    while(EdgeInput(graphPointer, std::bind(&Graph<ConnectionPoint, double>::DeleteEdge, *graphPointer, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))) {
        out.createDotFile();
    }
}
void VerteciesInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out) {}

int graphOptionInput() {
    std::cout << "Choose an action:\n0 - Add edges; 1 - Add vertex; 2 - Delete Edge; 3 - Delete Vertex;\n";
    return intInput();
}
void graphEdit(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out) {
    graphOptionInput();
    switch (intInput()) {
        case 0:
            EdgesInput(graphPointer, out);
            break;
        case 1:
            while(VertexInput(graphPointer, std::bind(&Graph<ConnectionPoint, double>::AddVertex, *graphPointer, std::placeholders::_1))) {
                out.createDotFile();
            }
            break;
        case 2:
            EdgeRemoving(graphPointer, out);
            break;
        case 3:
            break;
    }
}


int menu() {
    auto graphPointer = shared_ptr<Graph<ConnectionPoint, double >>(new Graph<ConnectionPoint, double>()); // a new graph

    GraphAlgorithms<ConnectionPoint, double>  algo(*graphPointer);
    GraphOutput out(graphPointer); // output
    EdgesInput(graphPointer, out);
    bool continueCode = true;
    while (continueCode) {
        std::cout << "Choose an option:\n0 - exit; 1 - Edit graph; 2 - Finding shortest paths; 3 - Graph coloring; 4 - Finding Strongly Connected Components;\n\n";
        switch (intInput()) {
            case 0:
                continueCode = false;
                break;
            case 1:
                graphEdit(graphPointer, out);
                break;
            case 2:
                std::cout << "Enter vertecies (word1 word2), algorithm calculate distance between them " << std::endl;
                PrintPath<ConnectionPoint>(algo.Dijkstra(ConnectionPoint(wordInput()), ConnectionPoint(wordInput())));
                break;
            case 3:
                out.createColoredDotFile(algo.Coloring());
                break;
            case 4:
                out.createColoredDotFile(algo.StronglyConnectedComponents());
                break;
        }
    }
    return 0;
}
