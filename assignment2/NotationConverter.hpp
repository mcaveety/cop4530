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
        std::string postfixToPrefix(std::string inStr); //Implement

        // Infix to other
        std::string infixToPostfix(std::string inStr); //Implement
        std::string infixToPrefix(std::string inStr);

        // Prefix to other
        std::string prefixToInfix(std::string inStr); //Implement
        std::string prefixToPostfix(std::string inStr);

        // // Verify no illegal characters
        // bool verify(std::string inStr, bool isInfix);

        // Housekeeping & Management
        std::string stripWhitespace(std::string);
        std::string addWhitespace(std::string);
        bool verify(std::string, bool);

        std::string charToStr(char ch) const;

        // private:

};

#endif /* NOTATION CONVERTER_H */