#pragma once

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
};

double GetHeight(Person person) { return person.height; }
std::string GetName(Person person) { return person.name; }
std::string GetCountry(Person person) {return person.country; }
std::string GetGender(Person person) { return person.gender; }
std::string GetJob(Person person) { return person.job; }
std::string GetSurname(Person person) { return person.surname; }
std::string GetCity(Person person) { return person.city; }
double GetWeight(Person person) { return person.weight; }
double GetSalary(Person person) { return person.salary; }
double GetAge(Person person) { return person.age; }