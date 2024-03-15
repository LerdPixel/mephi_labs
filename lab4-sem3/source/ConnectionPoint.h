#pragma once
#include <string>
#include <functional>
#include "containers/smart_ptrs/shared_ptr.h"
#include "IPrintableVertex.h"

class ConnectionPoint : public IPrintableVertex {
private:
    std::string name;
public:
    ConnectionPoint(const std::string &_name) {
        name = _name;
    }
    ConnectionPoint() {
        // Default constructor for serialization purposes only!
    }
    const std::string& GetName() const override { return name; }
    const std::string& PrintableOutput() override { return name; }    
    bool operator ==(const ConnectionPoint &other) const {
        return name == other.name;
    }
    const std::string& operator() () {
        return name;
    }
    ~ConnectionPoint() {}
};

template<> 
struct std::hash<ConnectionPoint> {
    size_t operator()(const ConnectionPoint& obj) const {
        return std::hash<std::string>{}(obj.GetName());
    }
};