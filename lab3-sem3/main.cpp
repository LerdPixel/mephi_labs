#include <iostream>
#include <utility>
#include <type_traits>
#include <fstream>
#include <sstream>
#include <string>

#include "ArraySequence.h"
#include "SortedSequence.h"
#include "Range.h"
#include "smart_ptrs/shared_ptr.h"
#include "PersonsIO/PersonFromFile.h"
#include "PersonsIO/Person.h"
#include "PersonsIO/output.h"
#include "PersonsIO/input.h"
#include "BarChart.h"

void actions(shared_ptr<Sequence<Person>> seq);

template <typename T>
void chartTreatment(shared_ptr<BarChart<T, Person>> barchart, bool &continueCode) {
    chartOutput<T>(barchart);
    int optionType;
    std::cout << "Group by:\n0 - Detaled barchart; 1 - Build by another value; 2 - exit" << '\n'<< '\n';
    checkInput(&optionType);
    if (optionType == 0) {
        T param;
        std::cout << "Input parameter: ";
        std::cin >> param;
        actions(barchart->GetSequenceChart()->Get(param));
    } else if (optionType == 2) {
        continueCode = 0;
    }
    else if (optionType == 1) {
//        *barchart = BarChart<T, Person>();
    }
}

void actions(shared_ptr<Sequence<Person>> seq) {
    int optionType;
    bool continueCode = true;

    shared_ptr<BarChart<Range, Person>> personBarChartRange;
    shared_ptr<BarChart<std::string, Person>> personBarChartKey;
    shared_ptr<Sequence<Range>> ranges;
    shared_ptr<ISortedSequence<Range>> Sranges;
    Range (* rangeFunctions [])(const Person&) = {Person::GetHeightRange, Person::GetWeightRange, Person::GetSalaryRange, Person::GetAgeRange};
    const std::string& (* keyFunctions [])(const Person&) = {Person::GetCountry, Person::GetCity, Person::GetJob, Person::GetGender, Person::GetSurname, Person::GetName};
    const int rangeFunctionsLength = 4, keyFunctionsLength = 6;
    while (continueCode) {
        std::cout << "Group by:\n0 - Height; 1 - Weight; 2 - Salary; 3 - Age; 4 - Country; 5 - City ; 6 - Job; 7 - Gender; 8 - Surname; 9 - Name; 10 - exit" << '\n'<< '\n';
        checkInput(&optionType);
        if (optionType >= 0 && optionType < rangeFunctionsLength) {
            personBarChartRange = make_shared<BarChart<Range, Person>>(seq, rangeFunctions[optionType], sortedRangesInput());
            chartTreatment<Range>(personBarChartRange, continueCode);
        } else if (optionType < keyFunctionsLength + rangeFunctionsLength) {
            personBarChartKey =  shared_ptr<BarChart<std::string, Person>>(new BarChart<std::string, Person>(seq, keyFunctions[optionType - rangeFunctionsLength]));
            chartTreatment<std::string>(personBarChartKey, continueCode);
        } else {
            break;
        }
    }
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
