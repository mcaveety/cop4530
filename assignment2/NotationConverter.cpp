/* COP 4530 001 Fall 2024
*  Assignment 2
*  Rylan Pietras & Michelle McAveety
*  Description:
*  Assignment 2 implements a deque to convert between polish, reverse polish, and infix arithmetic notations
*  Works for basic 4 operations
*/

#include "NotationConverter.hpp"
#include "Deque.hpp"

// Notation Conversion Methods
std::string NotationConverter::postfixToInfix(std::string inStr) {
    bool stringOk = verify(inStr, false);
    return ""; // for testing
}

std::string NotationConverter::postfixToPrefix(std::string inStr) { // Implement
    bool stringOk = verify(inStr, false);
    return ""; // for testing
}

std::string NotationConverter::infixToPostfix(std::string inStr) { // Implement
    bool stringOk = verify(inStr, true);
    Deque inDeq(stripWhitespace(inStr));
    Deque outDeq;
    Deque stack;
    int curPres = 0;

    while (!inDeq.isEmpty()) {
        if (((inDeq.front() >= 48) && (inDeq.front() <= 57)) || ((inDeq.front() >= 65) && (inDeq.front() <= 90)) || ((inDeq.front() >= 97) && (inDeq.front() <= 122))) { // If front of inDeq is an operand
            outDeq.pushBack(inDeq.popFront());
        }
        else if (inDeq.front() == 40) { // If front of inDeq is '('
            stack.pushFront(inDeq.popFront(), -1);
            curPres++;
        }
        else if (inDeq.front() == 41) { // If front of inDeq is ')'
            while ((!stack.isEmpty()) && (stack.front() != 40)) {
                outDeq.pushBack(stack.popFront());
            }
            stack.popFront();
            inDeq.popFront();
            curPres--;
        }
        else if ((inDeq.front() == 43) || (inDeq.front() == 45)) { // If front of inDeq is + or -
            while ((!stack.isEmpty()) && (stack.frontPres() >= curPres)) {
                outDeq.pushBack(stack.popFront());
            }
            stack.pushFront(inDeq.popFront(), curPres);
        }
        else if ((inDeq.front() == 42) || (inDeq.front() == 47)) { // If front is inDeq is * or /
            while ((!stack.isEmpty()) && (stack.frontPres() >= curPres)) {
                if ((stack.frontPres() == curPres) && (stack.front() == 43 || stack.front() == 45)) // Prevents + and - from being treated with equal presedence as * and /
                    break;
                outDeq.pushBack(stack.popFront());
            }
            stack.pushFront(inDeq.popFront(), curPres);
        }
    }

    while (!stack.isEmpty()) {
        outDeq.pushBack(stack.popFront());
    }

    return outDeq.toString();
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    bool stringOk = verify(inStr, true);
    return ""; // for testing
}

std::string NotationConverter::prefixToInfix(std::string inStr) { // Implement
    bool stringOk = verify(inStr, false);
    return ""; // for testing
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    bool stringOk = verify(inStr, false);
    return ""; // for testing
}


// Housekeeping & Management Methods

// Removes all extraneous whitespace from string input
std::string NotationConverter::stripWhitespace(std::string inStr) {
    Deque dIn(inStr);
    Deque dOut;

    while (!dIn.isEmpty()) {
        if (dIn.front() != ' ')
            dOut.pushBack(dIn.front());

        dIn.popFront();
    }

    // Returns deque as string
    return dOut.toString();
}

// Adds whitespace to string for printing
std::string NotationConverter::addWhitespace(std::string inStr){
    Deque dIn(inStr);
    Deque dOut;

    // Adds whitespace inbetween characters
    while (!dIn.isEmpty()){
        if (dIn.front() == '('){
            dOut.pushBack(dIn.front());
            dIn.popFront();
            continue;
        }
        dOut.pushBack(dIn.front());
        dOut.pushBack(' ');
        dIn.popFront();
    }
}


// Checks input string for illegal syntax
bool NotationConverter::verify(std::string inStr, bool isInfix)
{
    /*  Verifies parentheses, operators, & operands for all forms
     * 
     *  Allowed characters:
     *  ( ) 40 & 41
     *  * + - / 42, 43, 45, 47
     *  0-9 48-57
     *  ABC-XYZ 65-90
     *  abc-xyz 97-122
     */

    Deque stack; // for tracking parentheses

    int length = inStr.length();
    for (int i = 0; i < length; i++)
    {
        char ch = inStr[i];
        // Check for any illegal characters
        if (
            ch != 40 && ch != 41                            // ()
            && ch != 42 && ch != 43 && ch != 45 && ch != 47 // * + - /
            && (ch < 48 || ch > 57)                         // 0-9
            && (ch < 65 && ch > 90)                         // ABC-XYZ
            && (ch < 97 && ch > 122)                        // abc-xyz
        )
            return false;

        if (ch == 40 || ch == 41)
        {
            if (isInfix)
            {
                if (ch == 40){
                    stack.pushFront('(');
                } else {
                    stack.popFront();
                }
            }
            else
            {
                return false; // cannot have parentheses in non-infix
            }
        }
    }

    if (!stack.isEmpty()){
        return false;
    }

    return true;
}



int main() { // main function just for testing (remove before submission)
    NotationConverter NC;

    std::cout << NC.infixToPostfix("1 + ((2 -(3 * ( 4))))/ 5/4*7*7-0+(((3)))/5 + (5/(6/(3*/2/(1))+1))") << std::endl;

    return 0;
}