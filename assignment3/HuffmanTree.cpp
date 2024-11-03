#include <cstddef>
#include <string>
#include <iostream>
#include <map>

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"

std::map<char, int> HuffmanTree::giveFreqMap(std::string str) {
    std::map<char, int> freqMap;
    std::map<char, int>::iterator it;
    int len = str.length();

    // Count character frequency in string
    for (int i = 0; i < len; ++i) {
        it = freqMap.find(str[i]);

        if (it != freqMap.end()) {
            freqMap[str[i]] = ++(it->second);
        }
        else {
            freqMap[str[i]] = 1;
        }
    }

    return freqMap;
}

std::string HuffmanTree::compress(const std::string inputStr){

    HuffmanTree tree;
    std::map<char, int> freqmap = tree.giveFreqMap(inputStr);
    std::map<char,int>::iterator i;
    HeapQueue<HuffmanNode, HuffmanNode::Compare> minHeap;

    // For each item in the frequency map, add a node to the minheap
    for(i = freqmap.begin(); i != freqmap.end(); i++){
        std::cout << i->first << ": " << i->second << std::endl;

        // Create temporary node
        HuffmanNode temp(i->first, i->second);

        minHeap.insert(temp);
    }

    // Remove each minimum and print
    std::cout << "Highest priority in minheap" << std::endl;
    int length = minHeap.size();
    for(int i = 0; i < length; i++){
        HuffmanNode temp = minHeap.min();
        minHeap.removeMin();
        std::cout << temp.getCharacter() << ": " << temp.getFrequency() << std::endl;
    }
    std::cout << "Minheap is now empty" << std::endl;

    return "yay";

}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    return "testing";
}
std::string HuffmanTree::serializeTree() const{
    return "testing";
}

// Main function (remove before submission or test)
int main() {

    std::string test = "The quick brown fox jumped over the lazy dog.";
    HuffmanTree t;
    t.compress(test);

    return 0;
}