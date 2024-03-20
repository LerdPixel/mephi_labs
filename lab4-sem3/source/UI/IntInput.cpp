#include "IntInput.h"

int intInput() {
    std::string input;
    int number;
    while (true) {
        std::cout << "Enter an integer: ";
        std::getline(std::cin, input);
        std::istringstream iss(input);
        if (iss >> number) {
            char remaining;
            if (iss >> remaining) {
                std::cout << "Invalid input. Please enter only an integer.\n";
            } else {
                return number;
            }
        } else {
            std::cout << "Invalid input. Please enter only an integer.\n";
        }
    }
}