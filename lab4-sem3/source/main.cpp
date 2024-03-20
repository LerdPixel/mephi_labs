#include <string>
#include <iostream>
#include "Graph.h"
#include "WeightEdge.h"
#include "ConnectionPoint.h"
#include "containers/SmartPtrLinkedListSequence.h"
#include <string>
#include "UI/GraphOutput.h"
#include "UI/GraphInput.h"
#include "GraphAlgorithms.h"

void EdgeInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, GraphOutput<ConnectionPoint>& out) {
    while(GraphInput(graphPointer)) {
        out.createDotFile();
    }
}


int main() {
    auto graphPointer = shared_ptr<Graph<ConnectionPoint, double >>(new Graph<ConnectionPoint, double>()); // Create a new graph
    GraphOutput out(graphPointer);
    EdgeInput(graphPointer, out);

     EdgeInput(graphPointer, out);
    GraphAlgorithms<ConnectionPoint, double>  algo(*graphPointer);
    while (true) {
        std::string input, vertex1, vertex2;
        std::cout << "Enter vertecies (word1 word2), algorithm calculate distance between them " << std::endl;
        std::getline(std::cin, input);
        if (input.empty())     // Check if input is empty, if so, return false
            break;
        std::istringstream iss(input); // Parse the input string
        if (iss >> vertex1 >> vertex2) {
            PrintPath<ConnectionPoint>(algo.Dijkstra(ConnectionPoint(vertex1), ConnectionPoint(vertex2)));
        } else {
            // If parsing fails, skip the input
            std::cout << "Invalid format. Skipping." << std::endl;
        }
        
    }
    return 0;
}