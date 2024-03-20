#include "WordInput.h"

std::string wordInput() {
    std::string input;
    std::cout << "Enter a word (without spaces): ";
    std::cin >> input;
    return input;
}