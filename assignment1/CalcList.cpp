/* COP 4530 Section 001 Assignment 1 
*  Rylan Pietras & Michelle McAveety
*  Goal: Create a basic 4-function calculator utilizing a linked list
*  Calculator can display total value, print operation sequence, and undo previous actions
*/

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
        return DEFAULT_TOTAL; // Total value starts at 0 (DEFAULT_TOTAL is 0)
    }

}


// Perform a new operation in the sequence
void CalcList :: newOperation(const FUNCTIONS func, const double operand) {

    // Instantiate new node object
    Node *temp = new Node; 

    // Set node values based on function arguments
    temp->newOp = func;
    temp->newNum = operand;

    if (top == nullptr) { // For first calculation performed only
        top = temp;
    }
    
    /* Perform specified func operation. 
    *  Note that, if first operation, default totalVal is 0
    *  Otherwise, top will be the previous operation performed. */
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
            try {
                // Check for division by 0
                if (operand == 0) {
                    delete temp; // Avoids memory leaks
                    throw DivByZero();
                }
                temp->totalVal = top->totalVal / operand;
            }
            catch (const DivByZero &e) {
                std::cout << "Cannot divide by 0" << std::endl;
                return;
            }
            
            break;
    }

    // If calculation was successful, link nodes
    // Note: only necessary if this is not the first operation
    if (temp != top){
        temp->numOfOps = top->numOfOps + 1; // increment number of operations
        temp->next = top; // point to previous top node
        top = temp;
    }

}


// Undo last operation performed in calculation sequence
void CalcList :: removeLastOperation() {
    try {
        if (top == nullptr)
            throw StackEmpty();
        
        Node *temp = top; // create temporary node pointing to last operation
        top = top->next; // point top to n-1th operation 
        delete temp; // delete the nth operation
    } catch (const StackEmpty &e) {
        std::cout << "Stack is empty, nothing to remove" << std::endl;
    }
}


// Returns a string of all calculations
std::string CalcList :: toString(unsigned short precision) const {
    double zero = 0.0;

    // Check that at least one operation has been performed
    try {
        if (top == nullptr)
            throw StackEmpty();
    } catch (const StackEmpty &e) {
        std::cout << "Stack is empty, nothing to display" << std::endl;
    }

    // Generate string
    std::ostringstream allCalc;
    allCalc << std::fixed << std::setprecision(precision);
    
    // Iterate through each operation and form string
    Node *temp = top;
    while (temp != nullptr) {

        allCalc << temp->numOfOps + 1 << ": ";
        
        if (temp->next == nullptr)
            allCalc << zero;
        else
            allCalc << temp->next->totalVal;
        
        // Apply symbol for appropriate identifier
        switch(temp->newOp){
            case ADDITION:
                allCalc << "+";
                break;
            case SUBTRACTION:
                allCalc << "-";
                break;
            case MULTIPLICATION:
                allCalc << "*";
                break;
            case DIVISION:
                allCalc << "/";
                break;
        }
        
        allCalc << temp->newNum << "=" << temp->totalVal << "\n";

        temp = temp->next; // Move to next operation
        
    }

    // Convert & return string
    return allCalc.str();

}


// >>> REMOVE IF CONFLICT WITH TEST FILE OCCURS <<<
int main(){

    // CalcList list;
    // list.newOperation(ADDITION, 10);
    // list.newOperation(DIVISION, 0);
    // list.newOperation(MULTIPLICATION, 3);
    // std::cout << list.total() << std::endl;
    // std::cout << list.toString(2) << std::endl;

    return 0;
}
