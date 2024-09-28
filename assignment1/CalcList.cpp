#include <iostream>
#include <string>
#include <iomanip>

// Header file with CalcList class definitions
#include "CalcList.hpp"

#define DEFAULT_TOTAL 0.0

// Return current value of most recent operation
double CalcList :: total() const {
    if(top != nullptr){
        return top->totalVal;
    }
    else{
        return DEFAULT_TOTAL; // Total value startes at 0 (DEFAULT_TOTAL is 0)
    }
}

// Perform a new operation in the sequence
void CalcList :: newOperation(const FUNCTIONS func, const double operand) {

    Node *temp = new Node; // Instantiate new node object
    // Set node values based on function arguments
    temp->newOp = func;
    temp->newNum = operand;

    if (top == nullptr) { // For first calculation performed
        top = temp; // Set top to point to temp
    }
    
    /* Perform specified func operation. 
    *  Note that, if first operation, temp = top
    *  Otherwise, top will be the previous operation performed.
    */
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
            if(operand == 0){
                delete temp; // avoid memory leaks
                throw("Divide by 0 Error");
            }
            else{
                temp->totalVal = top->totalVal / operand;
            }   
            break;
    }

    // If calculation was successful, link nodes
    // Note: only necessary if this is not the first operation
    if (temp != top){
        temp->numOfOps = (top->numOfOps)++; // increment number of operations
        temp->next = top; // point to previous top node
        top = temp;
    }

}

// Undo last operation performed in calculation sequence
void CalcList :: removeLastOperation() {
    Node *temp = top; // create temporary node pointing to last operation
    top = top->next; // point top to n-1th operation 
    delete temp; // delete the nth operation, effectively undoing one step
}



// toString function in progress <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< in progress
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

// For testing of class functionality

int main() {
    CalcList list = CalcList();
    std::cout << list.total() << std::endl;
    list.newOperation(ADDITION, 10);
    list.newOperation(DIVISION, 5);
    std::cout << list.total() << std::endl;
    list.newOperation(SUBTRACTION, 1);
    list.newOperation(MULTIPLICATION, 9);
    std::cout << list.total() << std::endl;

    return 0;
}

// hint: press  ctrl + / to comment out a highlighted code block
