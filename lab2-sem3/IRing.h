#ifndef IRING_H
#define IRING_H

class Math

class IRing {
public:
    virtual ~IRing() {};
    virtual IRing& operator*(IRing& rv) = 0;
    virtual IRing operator* (const IRing& rhs) = 0;
}

#endif
