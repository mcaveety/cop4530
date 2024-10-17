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
    return ""; // for testing
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
        if (dIn.front() != ' ') {
            dOut.pushBack(dIn.front());
        }
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

    std::string str = " this has white space ";

    std::cout << str << std::endl;

    str = NC.stripWhitespace(str);

    std::cout << str << std::endl;


    return 0;
}