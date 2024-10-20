/* COP 4530 001 Fall 2024
*  Assignment 2
*  Rylan Pietras & Michelle McAveety
*  Description:
*  Assignment 2 implements a deque to convert between polish, reverse polish, and infix arithmetic notations
*  Works for basic 4 operations
*/

#include "NotationConverter.hpp"
#include "Deque.hpp"

std::string NotationConverter::postfixToPrefix(std::string inStr) { // Implement
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

    return stack.strFront();
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

std::string NotationConverter::prefixToInfix(std::string inStr) { // Implement
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

    return stack.strFront();
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

std::string NotationConverter::charToStr(char ch) const {
    std::string str(1, ch);
    return str;
}

// bool verify(std::string inStr, bool isInfix)
// {
//     /* Must verify matching parentheses (infix only)
//      *  and matching operators & operands (all forms)
//      *  Allowed characters:
//      *  ( ) 40 & 41
//      *  * + - / 42, 43, 45, 47
//      *  0-9 48-57
//      *  ABC-XYZ 65-90
//      *  abc-xyz 97-122
//      */
//     int length = inStr.length();
//     for (int i = 0; i < length; i++)
//     {
//         char ch = inStr[i];
//         // Check for any illegal characters
//         if (
//             ch != 40 && ch != 41                            // ()
//             && ch != 42 && ch != 43 && ch != 45 && ch != 47 // * + - /
//             && (ch < 48 || ch > 57)                         // 0-9
//             && (ch < 65 && ch > 90)                         // ABC-XYZ
//             && (ch < 97 && ch > 122)                        // abc-xyz
//         )
//             return false;

//         if (ch == 40 or ch == 41)
//         {
//             if (isInfix)
//             {
//                 // use deque as stack for matching parentheses
//                 Deque parentheses;
//                 // operations to add characters here
//                 if (!parentheses.isEmpty())
//                 {
//                     return false; // non-matching parentheses detected
//                 }
//             }
//             else
//             {
//                 return false; // cannot have parentheses in non-infix
//             }
//         }
//     }
// }

int main() { // main function just for testing (remove before submission)
    NotationConverter NC;
    std::cout << std::endl;

    std::cout << NC.infixToPostfix("a + ((b -(c * ( d))))/ e/f*g*h-i+(((j)))/k + (m/(n/(p*z/q/(r))+s))") << std::endl;
    std::cout << std::endl;

    std::cout << NC.infixToPrefix("a + ((b -(c * ( d))))/ e/f*g*h-i+(((j)))/k + (m/(n/(p*z/q/(r))+s))") << std::endl; // giving errors
    std::cout << std::endl;

    std::cout << NC.prefixToInfix("- - - + - + - 9 7 8 2 4 / / / 3 9 7 8 * 2 4 3") << std::endl;
    std::cout << std::endl;

    std::cout << NC.prefixToPostfix("- - - + - + - 9 7 8 2 4 / / / 3 9 7 8 * 2 4 3") << std::endl;
    std::cout << std::endl;

    std::cout << NC.postfixToPrefix("9 7 - 8 + 2 - 4 + 3 9 / 7 / 8 / - 2 4 * - 3 -") << std::endl;
    std::cout << std::endl;

    std::cout << NC.postfixToInfix("9 7 - 8 + 2 - 4 + 3 9 / 7 / 8 / - 2 4 * - 3 -") << std::endl;
    std::cout << std::endl;

    return 0;
}