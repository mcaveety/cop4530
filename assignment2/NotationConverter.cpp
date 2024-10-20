/* COP 4530 001 Fall 2024
*  Assignment 2
*  Rylan Pietras & Michelle McAveety
*  Description:
*  Assignment 2 implements a deque to convert between polish, reverse polish, and infix arithmetic notations
*  Works for basic 4 operations
*/

#include "NotationConverter.hpp"
#include "Deque.hpp"

std::string NotationConverter::postfixToPrefix(std::string inStr) {
    if (!NotationConverter::verify(inStr, false))
        throw;

    Deque inDeq(stripWhitespace(inStr));
    Deque stack;

    while (!inDeq.isEmpty()) {
        if (((inDeq.front() >= 48) && (inDeq.front() <= 57)) || ((inDeq.front() >= 65) && (inDeq.front() <= 90)) || ((inDeq.front() >= 97) && (inDeq.front() <= 122))) { // If the front of inDeq is an operand
            stack.strPushFront(charToStr(inDeq.popFront()));
        }
        else if ((inDeq.front() == 43) || (inDeq.front() == 45) || (inDeq.front() == 42) || (inDeq.front() == 47)) { // If the front of inDeq is an operator
            std::string operand1 = stack.strPopFront();
            std::string operand2 = stack.strPopFront();
            std::string opSymbol = charToStr(inDeq.popFront());

            stack.strPushFront(opSymbol + operand2 + operand1);
        }
    }

    return addWhitespace(stack.strFront());
}

std::string NotationConverter::infixToPostfix(std::string inStr) { 
    if (!NotationConverter::verify(inStr, true))
        throw;

    Deque inDeq(stripWhitespace(inStr));
    Deque outDeq;
    Deque stack;
    int curPres = 0; // Used to track parentheses order

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

    return addWhitespace(outDeq.toString());
}

std::string NotationConverter::prefixToInfix(std::string inStr) { 
    if (!NotationConverter::verify(inStr, false))
        throw;

    Deque inDeq(stripWhitespace(inStr));
    Deque stack;

    while (!inDeq.isEmpty()) {
        if (((inDeq.back() >= 48) && (inDeq.back() <= 57)) || ((inDeq.back() >= 65) && (inDeq.back() <= 90)) || ((inDeq.back() >= 97) && (inDeq.back() <= 122))) { // If back of inDeq is an operand
            stack.strPushFront(charToStr(inDeq.popBack()));
        }
        else if ((inDeq.front() == 43) || (inDeq.front() == 45) || (inDeq.front() == 42) || (inDeq.front() == 47)) { // If back of inDeq is an operator
            std::string operand1 = stack.strPopFront();
            std::string operand2 = stack.strPopFront();
            std::string opSymbol = charToStr(inDeq.popBack());

            stack.strPushFront("(" + operand1 + opSymbol + operand2 + ")");
        }
    }


    return addWhitespace(stack.strFront());
}

std::string NotationConverter::postfixToInfix(std::string inStr) {
    return addWhitespace(prefixToInfix(postfixToPrefix(inStr)));
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    return addWhitespace(postfixToPrefix(infixToPostfix(inStr)));
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    return addWhitespace(infixToPostfix(prefixToInfix(inStr)));
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

// Adds whitespace back to string
std::string NotationConverter::addWhitespace(std::string inStr){
    Deque inDeq(inStr);
    Deque outDeq;

    while (!inDeq.isEmpty()){
        outDeq.pushBack(inDeq.front());
        if (inDeq.front() == '(' && outDeq.back() == '('){
            inDeq.popFront();
            continue;
        }

        if (inDeq.front() == ')' && outDeq.back() == ')'){
            inDeq.popFront();
            continue;
        }

        inDeq.popFront();
        if (!inDeq.isEmpty())
            outDeq.pushBack(' ');
    }
    return outDeq.toString();
}

std::string NotationConverter::charToStr(char ch) const {
    std::string str(1, ch);
    return str;
}

bool NotationConverter::verify(std::string inStr, bool isInfix)
{
    /* Must verify matching parentheses (infix only)
     *  and matching operators & operands (all forms)
     *  Allowed characters:
     *  ( ) 40 & 41
     *  * + - / 42, 43, 45, 47
     *  0-9 48-57
     *  ABC-XYZ 65-90
     *  abc-xyz 97-122
     */
    Deque stack;
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
            throw;

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
                throw; // cannot have parentheses in non-infix
            }
        }
    }
    if (!stack.isEmpty())
        throw;
    return true;
}