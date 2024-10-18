/* COP 4530 001 Fall 2024
*  Assignment 2
*  Rylan Pietras & Michelle McAveety
*  Description:
*  Assignment 2 implements a deque to convert between polish, reverse polish, and infix arithmetic notations
*  Works for basic 4 operations
*/

#include "NotationConverter.hpp"
#include "Deque.hpp"

std::string NotationConverter::postfixToInfix(std::string inStr) {
    return ""; // for testing
}

std::string NotationConverter::postfixToPrefix(std::string inStr) { // Implement
    return ""; // for testing
}

std::string NotationConverter::infixToPostfix(std::string inStr) { // Implement
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
            curPres--;
        }
        else if ((inDeq.front() == 43) || (inDeq.front() == 45)) { // If front of inDeq is + or -
            while ((!stack.isEmpty()) && (stack.frontPres() >= curPres)) {
                outDeq.pushBack(stack.popFront());
            }
            stack.pushFront(inDeq.popFront());
        }
        else if ((inDeq.front() == 42) || (inDeq.front() == 47)) { // If front is inDeq is * or /
            while ((!stack.isEmpty()) && (stack.frontPres() >= curPres)) {
                if ((stack.frontPres() == curPres) && (stack.front() == 43 || stack.front() == 45)) // Prevents + and - from being treated with equal presedence as * and /
                    break;
                outDeq.pushBack(stack.popFront());
            }
            stack.pushFront(inDeq.popFront());
        }
    }

    while (!stack.isEmpty()) {
        outDeq.pushBack(stack.popFront());
    }

    return outDeq.toString();
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
    return ""; // for testing
}

std::string NotationConverter::prefixToInfix(std::string inStr) { // Implement
    return ""; // for testing
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
    return ""; // for testing
}

std::string NotationConverter::stripWhitespace(std::string inStr) {
    Deque dIn(inStr);
    Deque dOut;

    while (!dIn.isEmpty()) {
        if (dIn.front() != ' ')
            dOut.pushBack(dIn.front());

        dIn.popFront();
    }

    return dOut.toString();
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

    std::cout << NC.infixToPostfix("(4+5)*9") << std::endl;

    return 0;
}