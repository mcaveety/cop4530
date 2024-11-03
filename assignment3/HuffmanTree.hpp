#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <cstddef>
#include <string>
#include <iostream>
#include <map>

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase {
    public:

        std::string compress(const std::string inputStr);
        std::string serializeTree() const;
        std::string decompress(const std::string inputCode, const std::string serializedTree);

        // Helper methods
        std::map<char, int> giveFreqMap(std::string str);
        void generateCodes(HuffmanNode *node, std::string code, std::map<char, std::string> &codes);
        std::string deserializeTree() const;

    private:
        HuffmanNode *root = nullptr;
};



#endif /* HUFFMANTREE_H */