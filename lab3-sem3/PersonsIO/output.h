#pragma once
#include <iostream>
#include "Person.h"
#include "../Range.h"
#include "../IDictionary.h"
#include "../Sequence.h"
#include "../BarChart.h"

std::ostream &operator<<(std::ostream &os, Range const &range) {
    return os << "( " << range.GetStart() << " , " << range.GetEnd() << " )";
}
template <typename T>
std::ostream &operator<<(std::ostream &os, IDictionary<T, int> &dict) {
    auto keys = dict.GetKeys();
    auto e = keys->GetEnumerator();
    while (e->next()) {
        os << **e << " >==< " << dict[**e] << "\n";
    }
    return os;
}

void printPerson(const Person& person) {
    std::cout << "Name: " << person.name << "\n"
        << "Surname: " << person.surname << "\n"
        << "Height: " << person.height << " cm\n"
        << "Weight: " << person.weight << " kg\n"
        << "Country: " << person.country << "\n"
        << "City: " << person.city << "\n"
        << "Gender: " << person.gender << "\n"
        << "Age: " << person.age << "\n"
        << "Salary: " << person.salary << "\n"
        << "Job: " << person.job << "\n\n";
}
void printPersons(shared_ptr<Sequence<Person>> persons) {
    auto e = persons->GetEnumerator();
    while (e->next())
        printPerson(**e);
}
template <typename T>
void chartOutput(shared_ptr<BarChart<T, Person>> barchart) {
	std::cout << *(barchart->GetChart()) << std::endl;
}