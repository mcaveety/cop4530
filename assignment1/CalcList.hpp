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
    class Node {
    public:
        double totalVal = 0;
        FUNCTIONS newOp = ADDITION;
        double newNum = 0;
        int numOfOps = 0;
        Node *next = nullptr;
    };

    Node *top = nullptr; // Pointer to most recent node in calculation list
};

#endif