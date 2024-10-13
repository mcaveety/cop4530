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
        std::string prefixToInfix(std::string);
        std::string prefixToPostfix(std::string);

        // Verify no illegal characters
        std::string verify(std::string);
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

std::string verify(std::string){

}

#endif /* NOTATION CONVERTER_H */