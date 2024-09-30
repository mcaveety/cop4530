#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"

class CalcList : public CalcListInterface { // Derived from CalcListInterface class
public:
    CalcList() { ; } // Empty object initializer
    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    std::string toString(unsigned short precision) const;

private:
    class Node { // For use in singly linked list as stack
    public:
        double totalVal = 0;
        FUNCTIONS newOp = ADDITION;
        double newNum = 0;
        int numOfOps = 0;
        Node *next = nullptr;
    };

    Node *top = nullptr; // Pointer to most recent node in calculation list
};


// Exceptions to catch in case of error
class DivByZero : std::runtime_error {
    public:
        DivByZero() : std::runtime_error("Division by zero") {};
};

class StackEmpty : std::runtime_error {
    public:
        StackEmpty() : std::runtime_error("Stack is empty") {};
};


#endif