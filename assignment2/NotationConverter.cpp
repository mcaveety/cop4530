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
    if (!verify(inStr, false))
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
    if (!verify(inStr, true))
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
    if (!verify(inStr, false))
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
    return prefixToInfix(postfixToPrefix(inStr));
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    return postfixToPrefix(infixToPostfix(inStr));
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    return infixToPostfix(prefixToInfix(inStr));
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

    while (!inDeq.isEmpty()) {
        outDeq.pushBack(inDeq.popFront());

        if (inDeq.isEmpty()){
            break;
        }
        if (outDeq.back() == '(') {
            continue;
        }
        else if (inDeq.front() == ')') {
            continue;
        }
        else {
            outDeq.pushBack(' ');
        }
    }

    return outDeq.toString();
}

std::string NotationConverter::charToStr(char ch) const {
    std::string str(1, ch);
    return str;
}

bool NotationConverter::verify(std::string inStr, bool isInfix) {
    /* Must verify matching parentheses (infix only)
     *  and matching operators & operands (all forms)
     *  Allowed characters:
     *  ( ) 40 & 41
     *  * + - / 42, 43, 45, 47
     *  0-9 48-57
     *  ABC-XYZ 65-90
     *  abc-xyz 97-122
     */

    Deque inDeq(inStr);
    Deque stack;

    while (!inDeq.isEmpty()) {
        if (
        (inDeq.front() != ' ') &&
        (inDeq.front() != '(' && inDeq.front() != ')') &&
        (inDeq.front() != '+' && inDeq.front() != '-' && inDeq.front() != '*' && inDeq.front() != '/') &&
        (inDeq.front() < '0' || inDeq.front() > '9') &&
        (inDeq.front() < 'A' || inDeq.front() > 'Z') &&
        (inDeq.front() < 'a' || inDeq.front() > 'z')) {
            throw;
        }

        if (isInfix) {
            if (inDeq.front() == '(') {
                stack.pushBack('(');
            }
            else if (inDeq.front() == ')') {
                stack.popFront();
            }
        }

        inDeq.popFront();
    }

    if (!stack.isEmpty()) {
        throw;
    }

    return true;
}

//     // Check for any illegal characters
//     if (
//         (ch != '(' && ch != ')') &&
//         (ch != '+' && ch != '-' && ch != '*' && ch != '/') &&
//         (ch < '0' || ch > '9') &&
//         (ch < 'A' || ch > 'Z') &&
//         (ch < 'a' || ch > 'z'))
//     {
//         throw;
//         }

//         if (ch == 40 || ch == 41) {
//             if (isInfix) {
//                 if (ch == 40) {
//                     stack.pushFront('(');
//                 } else {
//                     stack.popFront();
//                 }
//             }
//             else {
//                 //throw; // cannot have parentheses in non-infix
//             }
//         }
//     }
//     if (!stack.isEmpty())
//         throw;
//     return true;
// }

// int main() { // REMOVE BEFORE SUBMISSION
//     NotationConverter NC;
//     std::cout << std::endl;

//     std::cout << NC.infixToPostfix("a + ((b -(c * ( d))))/ e/f*g*h-i+(((j)))/k + (m/(n/(p*z/q/(r))+s))") << std::endl;
//     std::cout << std::endl;

//     std::cout << NC.infixToPrefix("a + ((b -(c * ( d))))/ e/f*g*h-i+(((j)))/k + (m/(n/(p*z/q/(r))+s))") << std::endl; // giving errors
//     std::cout << std::endl;

//     std::cout << NC.prefixToInfix("- - - + - + - 9 7 8 2 4 / / / 3 9 7 8 * 2 4 3") << std::endl;
//     std::cout << std::endl;

//     std::cout << NC.prefixToPostfix("- - - + - + - 9 7 8 2 4 / / / 3 9 7 8 * 2 4 3") << std::endl;
//     std::cout << std::endl;

//     std::cout << NC.postfixToPrefix("9 7 - 8 + 2 - 4 + 3 9 / 7 / 8 / - 2 4 * - 3 -") << std::endl;
//     std::cout << std::endl;

//     std::cout << NC.postfixToInfix("9 7 - 8 + 2 - 4 + 3 9 / 7 / 8 / - 2 4 * - 3 -") << std::endl;
//     std::cout << std::endl;

// }