#ifndef IOBJECT_H
#define IOBJECT_H

template <class T> class IObject {
public:
    virtual void prt() const = 0;
    virtual ~IObject() {}
};

class doubleNum : public IObject {
    
public:
    doubleNum(double)
}


#endif
