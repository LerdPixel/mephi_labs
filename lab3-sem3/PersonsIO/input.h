#pragma once
#include "../Range.h"
#include "../IDictionary.h"
#include "../Sequence.h"

int checkInput(int *n) {
	int sres = scanf("%d", n);
	while (sres != 1) {
		if (sres == EOF)
			throw std::invalid_argument("End of file");
		if (sres != 1) {
			scanf("%*[^\n]");
			puts("Wrong integer input format\n");
		}
		sres = scanf("%d", n);
	}
	return 0;
}
int checkInput(double *n) {
	int sres = scanf("%lf", n);
	while (sres != 1) {
		if (sres == EOF)
			throw std::invalid_argument("End of file");
		if (sres != 1) {
			scanf("%*[^\n]");
            return 1;
			puts("Wrong double input format\n");
		}
		sres = scanf("%lf", n);
	}
	return 0;
}
std::optional<Range> rangeInput() {
    double st, end;
    if (checkInput(&st))
        return {};
    if (checkInput(&end))
        return {};
    return Range(st, end);
}


std::istream &operator>> (std::istream& is, Range &range) {
    double start, end;
    is >> range.GetStartRef() >> range.GetEndRef();
    return is;
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
shared_ptr<ISortedSequence<Range>> sortedRangesInput() {
    return shared_ptr<ISortedSequence<Range>>(new SortedSequence<Range>(rangesInput(), Range::comparator, Range::related));
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