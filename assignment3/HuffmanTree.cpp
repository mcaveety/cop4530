#include <cstddef>
#include <string>
#include <iostream>
#include <map>

#include "HuffmanTree.hpp"
#include "HuffmanBase.hpp"
#include "HeapQueue.hpp"


// MAIN FUNCTIONALITY START >>>
// Helper method to build character frequency map
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

// Helper method to generate Huffman Codes recursively
void HuffmanTree::generateCodes(HuffmanNode *node, std::string code, std::map<char, std::string> &codes){

    // Return previous level when nullptr encountered
    if (node == nullptr) return;

    // If leaf node encountered, store character code in map
    if (node->isLeaf()) {
        codes[node->getCharacter()] = code;
        return;
    }

    // Recurse left, appending '0' to the code
    generateCodes(node->left, code + "0", codes);

    // Recurse right, appending '1' to the code
    generateCodes(node->right, code + "1", codes);

}



// Compresses input string to binary output using Huffman Coding
std::string HuffmanTree::compress(const std::string inputStr){


    // Step 2: Create character frequency map
    HuffmanTree tree;
    std::map<char, int> freqmap = tree.giveFreqMap(inputStr);
    std::map<char,int>::iterator i;
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> minHeap;


    // Step 3: Create minheap using character frequencies
    for(i = freqmap.begin(); i != freqmap.end(); i++){
        // DEBUG: Display the frequencies of each character prior to addition
        std::cout << i->first << ": " << i->second << std::endl;

        HuffmanNode *temp = new HuffmanNode(i->first, i->second);
        minHeap.insert(temp);
    }


    // Step 4: Build the Huffman tree
    std::cout << "Beginning minHeap ---> Huffman Tree transformation..." << std::endl;
    
    while (minHeap.size() > 1){
        // Extract two highest priority items from minHeap
        HuffmanNode *temp1 = minHeap.min();
        minHeap.removeMin();
        HuffmanNode *temp2 = minHeap.min();
        minHeap.removeMin();

        // Place sum node back in minHeap priority queue, with two minimums as children
        HuffmanNode *sum = new HuffmanNode('\0', size_t(temp1->getFrequency() + temp2->getFrequency()), nullptr, temp1, temp2);
        minHeap.insert(sum);
    }


    // Defines root node as sum of all frequencies; last node on minheap
    tree.root = minHeap.min();

    // Prints tree status
    std::cout << "Transformation complete" << std::endl;
    std::cout << "Root node of tree: " << tree.root->getFrequency() << std::endl;

    // Step 5a: Encode the string using HuffmanTree
    std::map<char, std::string> charCodes; // Map of character codes

    // Generate character codes
    tree.generateCodes(tree.root, "", charCodes);
    std::map<char, std::string>::iterator j;

    for(j = charCodes.begin(); j != charCodes.end(); j++){
        // DEBUG
        std::cout << j->first << ": " << j->second << std::endl;
    }

    std::string huffmanString = "";
    int c;
    for (c = 0; c < int(inputStr.length()); c++){
        huffmanString += charCodes.find(inputStr[c])->second;
    }

    std::cout << huffmanString << std::endl;
    return huffmanString;

}


std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){

    // Step 6: Use encoded text and serialized Huffman tree to decompress string
    return "";
}


std::string HuffmanTree::serializeTree() const{

    // Step 5b: Post-order algorithm to serialize the Huffman Tree
    // Must use data from t.root to understand tree structure
    return "<serialized tree string>";
}


// Helper method to deserialize tree during decompression process
HuffmanNode HuffmanTree::deserializeTree() const{
    return;
}
// MAIN FUNCTIONALITY END <<<


// Main function (remove before submission or test)
int main() {

    std::string test = "if a machine is expected to be infallible it cannot also be intelligent";
    HuffmanTree t;
    t.compress(test);

    return 0;
}