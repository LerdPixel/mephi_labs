#pragma once
#include "Person.h"
#include "../ArraySequence.h"
#include <utility>
#include <type_traits>
#include <fstream>
#include <string>

shared_ptr<Sequence<Person>> personsFromFile(std::string fileName) {
    shared_ptr<Sequence<Person>> persons(new ArraySequence<Person>());

    // Open the file
    std::ifstream file("person_list_gender_dependent.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file.\n";
        return persons;
    }

    std::string line;
    Person person;
    while (std::getline(file, line)) {
        if (line.empty()) {
            // Empty line indicates the end of a person's record
            persons->Append(person);
            person = Person(); // Reset person for the next record
        } else {
            // Split each line by colon and extract data
            size_t colon_pos = line.find(':');
            if (colon_pos != std::string::npos) {
                std::string key = line.substr(0, colon_pos);
                std::string value = line.substr(colon_pos + 2); // Skip ': ' after key
                if (key == "Name") {
                    person.name = value;
                } else if (key == "Surname") {
                    person.surname = value;
                } else if (key == "Height") {
                    person.height = std::stod(value.substr(0, value.find(' '))); // Extract height value
                } else if (key == "Weight") {
                    person.weight = std::stod(value.substr(0, value.find(' '))); // Extract weight value
                } else if (key == "Country") {
                    person.country = value;
                } else if (key == "City") {
                    person.city = value;
                } else if (key == "Region") {
                    person.region = value;
                } else if (key == "Gender") {
                    person.gender = value;
                } else if (key == "Hobby") {
                    person.hobby = value;
                }
            }
        }
    }
    return persons;

}