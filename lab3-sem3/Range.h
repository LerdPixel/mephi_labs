#pragma once

class Range {
    double _start;
    double _end;
public:
    Range() : _start(0), _end(0) {}
    Range(double start, double end) : _start(start), _end(end) {
        if (_start > _end) {
            std::swap(_start, end);
        }
    }
    bool has(const int number) const {
        return (number >= _start && number < _end);
    }
    bool has(const double number) const {
        return (number >= _start && number < _end);
    }
    bool has(const Range& other) const {
        return (other._start >= _start && other._end <= _end);
    }
    bool operator<(double number) const {
        return number < _start;
    }
    bool operator<(const Range& other) const {
        return _end <= other._start;
    }
    bool operator==(const Range& other) const {
        return _start == other._start && _end == other._end;
    }
    double GetStart() const {
        return _start;
    }
    double GetEnd() const {
        return _end;
    }
};