#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <map>
#include "HuffmanBase.hpp"

class HuffmanTree : public HuffmanTreeBase {
public:
    std::string compress(const std::string inputStr);
    std::string serializeTree() const;
    std::string decompress(const std::string inputCode, const std::string serializedTree);

    std::map<char, int> giveFreqMap(std::string str);

private:
    HuffmanNode *root = nullptr;  
};



#endif