#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "../Graph.h"

template <typename Callable>
bool EdgeInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, Callable EdgeAction) {
    std::string input, vertex1, vertex2;
    double weight;
    std::cout << "Enter edges (word1 word2 number), press Enter for each. Enter an empty string to stop." << std::endl;
    std::getline(std::cin, input);
    if (input.empty())     // Check if input is empty, if so, return false
        return false;
    std::istringstream iss(input); // Parse the input string
    if (iss >> vertex1 >> vertex2 >> weight) {
        EdgeAction(ConnectionPoint(vertex1), ConnectionPoint(vertex2), weight);
    } else {
        // If parsing fails, skip the input
        std::cout << "Invalid format. Skipping." << std::endl;
    }
    return true;
}
template <typename Callable>
bool VertexInput(shared_ptr<Graph<ConnectionPoint, double>> graphPointer, Callable VertexAction) {
    std::string input, vertex;
    double weight;
    while (true) {
        std::cout << "Enter vertex name, Enter a word (without spaces): ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (input.empty())     // Check if input is empty, if so, return false
            return false;
        if (iss >> vertex) {
            VertexAction(ConnectionPoint(vertex));
            return true;
        } else {
            std::cout << "Invalid format. Skipping." << std::endl;
        }
    }
}
