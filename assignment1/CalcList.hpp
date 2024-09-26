#ifndef CALCLIST_H
#define CALCLIST_H

#include "CalcListInterface.hpp"

//test

class CalcList : public CalcListInterface {
public:
    double total() const;
    void newOperation(const FUNCTIONS func, const double operand);
    void removeLastOperation();
    std::string toString(unsigned short precision) const;

private:
    class Node {
    public:
        double total = 0;
        FUNCTIONS newOp = ADDITION;
        double newNum = 0;
        Node *next = nullptr;
        int numOps = 0;
    };

    Node *top = nullptr;
};

#endif