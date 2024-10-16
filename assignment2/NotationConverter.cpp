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
}

std::string NotationConverter::postfixToPrefix(std::string inStr) { // Implement
}

std::string NotationConverter::infixToPostfix(std::string inStr) { // Implement
}

std::string NotationConverter::infixToPrefix(std::string inStr) {
}

std::string NotationConverter::prefixToInfix(std::string inStr) { // Implement
}

std::string NotationConverter::prefixToPostfix(std::string inStr) {
}

// Verifies string characters
bool verify(std::string inStr, bool isInfix) // needs testing -- may need to convert to deque
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
    int length = inStr.length();
    for (int i = 0; i < length; i++){

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
        
        // Check that parentheses are only present in infix inputs
        if (ch == 40 or ch == 41)
        {
            if (!isInfix)
                return false; // cannot have parentheses in non-infix inputs

        }
    }
    return true;
}

// Validates whitespace matches expected conventions
bool NotationConverter::validateWhitespace(std::string inStr){ // under construction
    Deque subject = Deque(inStr);
    // conditions:
    /* mandatory whitespace between operands and operators
    * no operators adjacent to parentheses
    * parentheses and operands CAN be adjacent
    * but only where the operand is interior to the parentheses*/

    return true;
}

// Remove whitespace from string
std::string NotationConverter::removeWhitespace(std::string inStr){ // needs testing
    Deque subject = Deque(inStr);
    Deque stripped = Deque();
    Deque::Node *n = subject;
    while(n != nullptr){
        char ch = subject.front();
        if (ch != ' ')
            stripped.pushFront(ch)
        n->next
    }
    
}

int main(){



    return 0;
}