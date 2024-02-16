#pragma once

// Define the Person structure
struct Person {
    std::string name;
    std::string surname;
    double height;
    double weight;
    std::string country;
    std::string city;
    std::string region;
    std::string gender;
    std::string hobby;
};

double GetHeight(Person  person) { return person.height; }
std::string GetName(const Person &person) { return person.name; }
