#include <iostream>
#include <map>
#include "HuffmanTree.hpp"

std::map<char, int> HuffmanTree::giveFreqMap(std::string str) {
    std::map<char, int> freqMap;
    std::map<char, int>::iterator it;
    int len = str.length();

    for (int i = 0; i < len; ++i) {
        freqMap.find(str[i]) = it;

        if (it != freqMap.end()) {
            freqMap[str[i]] = ++(it->second);
        }
        else {
            freqMap[str[i]] = 1;
        }
    }

    return freqMap;
}

// int main() {
//     return 0;
// }