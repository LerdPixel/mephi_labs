#pragma once

template <typename T> class ITree {
public:
    virtual void insert(const T&) = 0;
    virtual T find(const T&) const = 0;
    virtual void remove(const T&) = 0;
    virtual ~ITree() {}
};