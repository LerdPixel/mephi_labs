#pragma once
#include "../Range.h"
// Define the Person structure
struct Person {
    std::string name;
    std::string surname;
    double height;
    double weight;
    std::string country;
    std::string city;
    std::string gender;
    std::string job;
    double salary;
    double age;
    static Range GetHeightRange(const Person& person) { return Range(person.height, person.height); }
    static const std::string& GetName(const Person& person) { return person.name; }
    static const std::string& GetCountry(const Person& person) {return person.country; }
    static const std::string& GetGender(const Person& person) { return person.gender; }
    static const std::string& GetJob(const Person& person) { return person.job; }
    static const std::string& GetSurname(const Person& person) { return person.surname; }
    static const std::string& GetCity(const Person& person) { return person.city; }
    static Range GetWeightRange(const Person& person) { return Range(person.weight, person.weight); }
    static Range GetSalaryRange(const Person& person) { return Range(person.salary, person.salary); }
    static Range GetAgeRange(const Person& person) { return Range(person.age, person.age); }
};

