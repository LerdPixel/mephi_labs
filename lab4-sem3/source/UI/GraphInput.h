#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "../Graph.h"

bool GraphInput(shared_ptr<Graph<ConnectionPoint, shared_ptr<WeightEdge<ConnectionPoint>>>> graphPointer) {
    std::string input, vertex1, vertex2;
    double weight;
    std::cout << "Enter edges (word1 word2 number), press Enter for each. Enter an empty string to stop." << std::endl;
    std::getline(std::cin, input);
    if (input.empty())     // Check if input is empty, if so, return false
        return false;
    std::istringstream iss(input); // Parse the input string
    if (iss >> vertex1 >> vertex2 >> weight) {
        graphPointer->AddEdge(ConnectionPoint(vertex1), make_shared<WeightEdge<ConnectionPoint>>(ConnectionPoint(vertex2), weight));
    } else {
        // If parsing fails, skip the input
        std::cout << "Invalid format. Skipping." << std::endl;
    }
    return true;
}