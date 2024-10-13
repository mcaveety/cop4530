#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <string>
#include "NotationConverterInterface.hpp"

class NotationConverterInterface : public NotationConverter {
    public:
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
    private:

};


std::string NotationConverter::postfixToInfix(std::string inStr){

}

std::string NotationConverter:
#endif /* NOTATION CONVERTER_H */