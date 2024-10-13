#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <string>
#include "NotationConverterInterface.hpp"
#include "Deque.hpp"

class NotationConverter : public NotationConverterInterface {
    public:
        // Constructor
        NotationConverter() {};

        // Postfix to other
        std::string postfixToInfix(std::string inStr);
        std::string postfixToPrefix(std::string inStr);

        // Infix to other
        std::string infixToPostfix(std::string inStr);
        std::string infixToPrefix(std::string inStr);

        // Prefix to other
        std::string prefixToInfix(std::string inStr);
        std::string prefixToPostfix(std::string inStr);

        // Verify no illegal characters
        bool verify(std::string inStr, bool isInfix);
    //private:

};


std::string NotationConverter::postfixToInfix(std::string inStr){

}

std::string NotationConverter::postfixToPrefix(std::string inStr){

}

std::string NotationConverter::infixToPostfix(std::string inStr){

}

std::string NotationConverter::infixToPrefix(std::string inStr){

}

std::string NotationConverter::prefixToInfix(std::string inStr){

}

std::string NotationConverter::prefixToPostfix(std::string inStr){

}

bool verify(std::string inStr, bool isInfix){
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
            ch != 40 && ch != 41 // ()
            && ch != 42 && ch != 43 && ch !=45 && ch!=47 // * + - /
            && (ch < 48 || ch > 57) // 0-9
            && (ch < 65 && ch > 90) // ABC-XYZ
            && (ch < 97 && ch > 122) // abc-xyz
        ) return false;

        if (ch == 40 or ch == 41){
            if (isInfix){
                // use deque as stack for matching parentheses
                Deque parentheses;
                // operations to add characters here
                if (!parentheses.isEmpty()){
                    return false; // non-matching parentheses detected
                }
            } else {
                return false; // cannot have parentheses in non-infix
            }
        }

    }

}

#endif /* NOTATION CONVERTER_H */