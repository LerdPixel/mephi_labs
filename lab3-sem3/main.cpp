#include <iostream>
#include "ArraySequence.h"
#include "SortedSequence.h"
#include "Range.h"
#include <utility>
#include <type_traits>
#include "smart_ptrs/shared_ptr.h"
#include "PersonsIO/PersonFromFile.h"
#include "PersonsIO/Person.h"
#include "PersonsIO/output.h"
#include "BarChart.h"
#include <fstream>
#include <sstream>
#include <string>


void printPerson(Person person) {
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
shared_ptr<Sequence<Range>> rangesInput() {
    shared_ptr<Sequence<Range>> ranges = shared_ptr<Sequence<Range>>(new ArraySequence<Range>());
    std::optional<Range> range = rangeInput();
    while (range.has_value()) {
        ranges->Append(range.value());
        range = rangeInput();
    }
    return ranges;
}

void actions(shared_ptr<Sequence<Person>> seq) {
    
    int tempCode = 1, len, p1, p2, optionType;
    shared_ptr<BarChart<Range, Person>> personBarChart;
    shared_ptr<BarChart<std::string, Person>> personBarChartGender;
    shared_ptr<Sequence<Range>> ranges;
    while (tempCode) {
        std::cout << "Group by:\n0 - Height; 1 - Weight; 2 - Salary; 3 - Age; 4 - Country; 5 - City ; 6 - Job; 7 - Gender; 8 - Surname; 9 - Name; 10 - exit" << '\n'<< '\n';
        checkInput(&optionType);
        switch (optionType) {
            case 0:
                ranges = rangesInput();
                personBarChart =  make_shared<BarChart<Range, Person>>(seq, ranges, GetHeight);
                break;
            case 1:
                ranges = rangesInput();
                personBarChart =  make_shared<BarChart<Range, Person>>(seq, ranges, GetWeight);
                break;
            case 2:
                ranges = rangesInput();
                personBarChart =  make_shared<BarChart<Range, Person>>(seq, ranges, GetSalary);
                break;
            case 3:
                ranges = rangesInput();
                personBarChart =  make_shared<BarChart<Range, Person>>(seq, ranges, GetAge);
                break;
            case 4:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetCountry));
                break;
            case 5:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetCity));
                break;
            case 6:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetJob));
                break;
            case 7:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetGender));
                break;
            case 8:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetSurname));
                break;
            case 9:
                personBarChartGender =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, GetName));
                break;
            case 10:
                tempCode = 0;
                break;
        }
        if(personBarChart) {
            auto chart = personBarChart->GetChart();
            std::cout << *(chart) << std::endl;
            std::cout << "Group by:\n0 - Detaled barchart; 1 - Build by another value; 2 - exit" << '\n'<< '\n';
            checkInput(&optionType);
            if (optionType == 0) {
                std::cout<<"Input range: ";
                std::optional<Range> range = rangeInput();
                actions(personBarChart->GetSequenceChart()->Get(range.value()));
            } else if (optionType == 2) {
                tempCode = 0;
            }
            else if (optionType == 1) {
                personBarChart = shared_ptr<BarChart<Range, Person>>();
            }
        }
        else if (personBarChartGender) {
            std::cout << *(personBarChartGender->GetChart()) << std::endl;
            std::cout << "Group by:\n0 - Detaled barchart; 1 - Build by another value; 2 - exit" << '\n'<< '\n';
            checkInput(&optionType);
            if (optionType == 0) {
                std::cout<<"Input string: ";
                std::string str;
                std::cin >> str;
                actions(personBarChartGender->GetSequenceChart()->Get(str));
            } else if (optionType == 2) {
                tempCode = 0;
            }
        }

    }
}

void inputPersonData(Person &person) {
    std::cout << "Enter first name: ";
    std::cin >> person.name;

    std::cout << "Enter last name: ";
    std::cin >> person.surname;

    std::cout << "Enter city: ";
    std::cin >> person.city;

    std::cout << "Enter country: ";
    std::cin >> person.country;

    std::cout << "Enter age: ";
    std::cin >> person.age;

    std::cout << "Enter gender: ";
    std::cin.ignore(); // Clear input buffer
    std::cin >> person.gender;

    std::cout << "Enter height (in cm): ";
    std::cin >> person.height;

    std::cout << "Enter weight (in kg): ";
    std::cin >> person.weight;

    std::cout << "Enter job: ";
    std::cin.ignore(); // Clear input buffer
    std::cin >> person.job;

    std::cout << "Enter salary: ";
    std::cin >> person.salary;
}
shared_ptr<Sequence<Person>> keyboardInput() {
    int size;
    std::cout << "Input persons count: ";
    checkInput(&size);
    shared_ptr<Sequence<Person>> persons(new ArraySequence<Person>());
    for (int i = 0; i < size; ++i) {
        Person person;
        inputPersonData(person);
        persons->Append(person);
    }
    return persons;
}

int main() {
    int optionType;
    std::cout << "Data Input:\n<\t0 - From file; 1 - Keybord Input\t>" << '\n'<< '\n';
    checkInput(&optionType);
    if (optionType == 0) {
        actions(personsFromFile("person_list_gender_dependent.txt"));
    }
    else {
        actions(keyboardInput());
    }
   
    return 0;
}
