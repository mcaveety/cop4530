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


// Compress input string to binary output using Huffman algorithm
std::string HuffmanTree::compress(const std::string inputStr){

    // Step 2: Create character frequency map
    HuffmanTree tree;
    std::map<char, int> freqmap = tree.giveFreqMap(inputStr);
    std::map<char,int>::iterator i;
    HeapQueue<HuffmanNode, HuffmanNode::Compare> minHeap;

    // Step 3: Create minheap using character frequencies
    for(i = freqmap.begin(); i != freqmap.end(); i++){
        // DEBUG: Display the frequencies of each character prior to addition
        std::cout << i->first << ": " << i->second << std::endl;

        HuffmanNode temp(i->first, i->second);
        minHeap.insert(temp);
    }

    // Step 4: Build the Huffman tree
    // Note: this.root should point to the tree root
    std::cout << "Beginning minHeap ---> Huffman Tree transformation..." << std::endl;

    while (minHeap.size() > 1){
        // Extract two highest priority items from minHeap
        HuffmanNode min1 = minHeap.min();
        minHeap.removeMin();
        HuffmanNode min2 = minHeap.min();
        minHeap.removeMin();

        // Place sum node back in minHeap priority queue
        HuffmanNode parent('\0', size_t(min1.getFrequency() + min2.getFrequency()));
        minHeap.insert(parent);

        // Convert to leaf nodes, with parent as sum
        min1.parent = &parent;
        min2.parent = &parent;
        parent.left = &min1;
        parent.right = &min2;
        
    }

    std::cout << "Transformation complete" << std::endl;


    return "<this is the compressed huffman string>";

}

std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){
    return "";
}
std::string HuffmanTree::serializeTree() const{
    return "<serialized tree string>";
}

// Main function (remove before submission or test)
int main() {

    std::string test = "The quick brown fox jumped over the lazy dog.";
    HuffmanTree t;
    t.compress(test);

    return 0;
}