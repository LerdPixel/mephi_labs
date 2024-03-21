#include "WordInput.h"

std::string wordInput() {
    std::string input;
    std::cout << "Input: ";
    getline(std::cin, input);
    return input;
}