#include <cstddef>
#include <string>
#include <iostream>
#include <map>
#include <stack>

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
    std::map<char, int> freqmap = giveFreqMap(inputStr);
    std::map<char,int>::iterator i;
    HeapQueue<HuffmanNode*, HuffmanNode::Compare> minHeap;


    // Step 3: Create minheap using character frequencies
    for(i = freqmap.begin(); i != freqmap.end(); i++){
        HuffmanNode *temp = new HuffmanNode(i->first, i->second);
        minHeap.insert(temp);
    }


    // Step 4: Build the Huffman tree
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
    root = minHeap.min();

    // Prints tree status
    // Step 5a: Encode the string using HuffmanTree
    std::map<char, std::string> charCodes; // Map of character codes

    // Generate character codes
    generateCodes(root, "", charCodes);
    std::map<char, std::string>::iterator j;

    std::string huffmanString = "";
    int c;
    for (c = 0; c < int(inputStr.length()); c++){
        huffmanString += charCodes.find(inputStr[c])->second;
    }

    return huffmanString;

}


std::string HuffmanTree::decompress(const std::string inputCode, const std::string serializedTree){

    // Step 6: Use encoded text and serialized Huffman tree to decompress string
    HuffmanNode *root = deserializeTree(serializedTree);
    std::string decompressed = "";
    int len = inputCode.length();
    int i;

    // Traverse each value in the string
    HuffmanNode *temp = root;
    for (i = 0; i < len + 1; i++){
        if (temp->isLeaf()){
            // When a leaf node is encountered, stop, return character, and then go back to the beginning
            decompressed += temp->getCharacter();
            temp = root;
            i--;
            continue;
        }
        if (inputCode[i] == '0'){
            temp = temp->left;
        }
        else { // == '1'
            temp = temp->right;
        }
    }

    return decompressed;
}


std::string HuffmanTree::serializeTree() const {
    // Step 5b: Post-order algorithm to serialize the Huffman Tree
    std::string charStr = "";
    std::string leafnBranchStr = "";
    std::string outStr = "";

    postorderCharStr(root, charStr);
    postorderLeafAndBranchStr(root, leafnBranchStr);

    int counter = 0;
    long unsigned int leafnBranchLen = leafnBranchStr.length();
    for (long unsigned int strI = 0; strI < leafnBranchLen; ++strI) {
        if (leafnBranchStr[strI] == 'L') {
            outStr += leafnBranchStr[strI];
            outStr += charStr[strI - counter];
        }
        else {
            outStr += leafnBranchStr[strI];
            counter++;
        }
    }

    return outStr;

}

// Returns string of chars in post order
void HuffmanTree::postorderCharStr(HuffmanNode *Node, std::string &inStr) const {
    if (Node == nullptr) {
        return;
    }

    postorderCharStr(Node->left, inStr);
    postorderCharStr(Node->right, inStr);


    if (Node->isLeaf()) {
        inStr += Node->getCharacter();
    }
}

// Helper function for tree serialization
void HuffmanTree::postorderLeafAndBranchStr(HuffmanNode *Node, std::string &inStr) const {
    if (Node == nullptr) {
        return;
    }

    postorderLeafAndBranchStr(Node->left, inStr);
    postorderLeafAndBranchStr(Node->right, inStr);

    if (Node->isLeaf()) {
        inStr += 'L';
    }
    else {
        inStr += 'B';
    }
}


// Helper method to deserialize tree during decompression process
HuffmanNode *HuffmanTree::deserializeTree(std::string serialized) const{
    // Reverse serialization by traversing in a reverse-postorder process.
    std::stack<HuffmanNode*> nodeStack;

    int len = serialized.length();
    for (int i = 0; i < len; i++){
        if (serialized[i] == 'L'){
            i++; // move to character following L
            nodeStack.push(new HuffmanNode(serialized[i], 0)); 
        }
        else if (serialized[i] == 'B'){

            HuffmanNode *right = nodeStack.top();
            nodeStack.pop();
            HuffmanNode *left = nodeStack.top();
            nodeStack.pop();

            // Create a branch node with the children
            HuffmanNode *parent = new HuffmanNode('\0', 0, nullptr, left, right);
            nodeStack.push(parent);
        }
    }

    HuffmanNode *root = nodeStack.top();
    nodeStack.pop();
    return root;
}
// MAIN FUNCTIONALITY END <<<


// Main function (remove before submission or test)
// int main() {

//     std::string test = "It is time to unmask the computing community as a Secret Society for the Creation and Preservation of Artificial Complexity";
//     HuffmanTree t;
//     std::string testEncode = t.compress(test);
//     std::string testSerialized = t.serializeTree();

//     std::string test2 = t.decompress(testEncode, testSerialized);

//     return 0;
// }