#include <iostream>
#include <string>
#include <iomanip>
#include "CalcList.hpp"


double CalcList :: total() const {
    return top->totalVal;
}

void CalcList :: newOperation(const FUNCTIONS func, const double operand) {
    if (top == nullptr) { //first if statement for first Node
        Node *temp = new Node;

        switch(func) { // temp->totalVal just accesses the default values for Node
            case ADDITION:
                temp->totalVal = temp->totalVal + operand;
                break;
            case SUBTRACTION:
                temp->totalVal = temp->totalVal - operand;
                break;
            case MULTIPLICATION:
                temp->totalVal = temp->totalVal * operand;
                break;
            case DIVISION:
                if(operand == 0){
                    throw("Divide by 0 Error");
                }
                else{
                    temp->totalVal = temp->totalVal / operand;
                }   
        }

        temp->newOp = func;
        temp->newNum = operand;
        temp->numOfOps = (temp->numOfOps)++;
        temp->next = nullptr;

        top = temp;
    }
    else{ //else for any node other than first
        Node *temp = new Node;

        switch(func) {
            case ADDITION:
                temp->totalVal = top->totalVal + operand;
                break;
            case SUBTRACTION:
                temp->totalVal = top->totalVal - operand;
                break;
            case MULTIPLICATION:
                temp->totalVal = top->totalVal * operand;
                break;
            case DIVISION:
                if (operand == 0) {
                    throw("Divide by 0 Error");
                }
                else {
                    temp->totalVal = top->totalVal / operand;
                }
        }

        temp->newOp = func;
        temp->newNum = operand;
        temp->numOfOps = (top->numOfOps)++;
        temp->next = top;

        top = temp;
    }
}

void CalcList :: removeLastOperation() {
    Node *temp = top;
    top = top->next;
    delete temp;
}

// toString function in progress
std::string CalcList :: toString(unsigned short precision) const {
    if(precision < 0 || precision > 10) {
        throw("Precision Input Invalid");
    }

    std::string allOutputs = "";
    
    Node *temp = top;
    while (temp != nullptr) {

        temp = temp->next;
    }

    return allOutputs;
}

int main() {
    return 0;
}