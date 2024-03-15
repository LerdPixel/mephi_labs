#pragma once
#include <string>

class IPrintableVertex {
public:
    virtual const std::string& GetName() const = 0;
    virtual const std::string& PrintableOutput() = 0;
    virtual ~IPrintableVertex() {};
};