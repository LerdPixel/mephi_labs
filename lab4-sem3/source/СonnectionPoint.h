#pragma once
#include "containers/smart_ptrs/shared_ptr.h"
#include <string>

class СonnectionPoint {
private:
    std::string name;
public:
    СonnectionPoint(const std::string &_name) {
        name = _name;
    }
    const std::string& GetName(void) const { return name; }
    bool operator ==(const СonnectionPoint &other) const {
        if (name && other.name) {
            return (*name == *(other.name));
        }
        return !(name || other.name);
    }
};