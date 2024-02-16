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

#include <string>

void printPerson(Person person) {
    std::cout << "Name: " << person.name << "\n"
        << "Surname: " << person.surname << "\n"
        << "Height: " << person.height << " cm\n"
        << "Weight: " << person.weight << " kg\n"
        << "Country: " << person.country << "\n"
        << "City: " << person.city << "\n"
        << "Region: " << person.region << "\n"
        << "Gender: " << person.gender << "\n"
        << "Hobby: " << person.hobby << "\n\n";
}
void printPersons(shared_ptr<Sequence<Person>> persons) {
    auto e = persons->GetEnumerator();
    while (e->next())
        printPerson(*(*e));
}



int main() {
    
    // Print the information of each person
    shared_ptr<Sequence<Person>> seq = personsFromFile("person_list_gender_dependent.txt");
    Range arr[] = {Range(160, 170),Range(170, 180),Range(180, 190)};
    shared_ptr<Sequence<Range>> ranges = shared_ptr<Sequence<Range>>(new ArraySequence<Range>(arr, 3));
    auto personBarChart =  make_shared<BarChart<Range, Person>>(seq, ranges, GetHeight);
    auto chart = personBarChart->GetChart();
    std::cout << chart->Get(Range(170, 180)) << "\n";
    std::cout << *(chart) << std::endl;

    return 0;
}
