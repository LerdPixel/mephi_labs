#pragma once
#include "../Range.h"
#include "../IDictionary.h"
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
	double sres = scanf("%lf", n);
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