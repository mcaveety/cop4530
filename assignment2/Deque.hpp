#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>

class Deque {
public:
    class Node {
    public:
        char ch = 0;
        int pres = 0; // To provide a value for presedence
        std::string stackStr = "";
        Node *prev = nullptr;
        Node *next = nullptr;
    };

    // Head and Tail pointers
    Node *head = nullptr;
    Node *tail = nullptr;

    // Default Constructor & Destructor
    Deque() {};
    ~Deque();

    // Methods for managing Nodes
    bool isEmpty() const;
    bool isOneNode() const;

    // Constructors and methods for managing ch and pres
    Deque(std::string inStr);
    char front() const;
    char back() const;
    int frontPres() const;
    int backPres() const;
    void pushFront(char ch, int pres = 0);
    void pushBack(char ch, int pres = 0);
    char popFront();
    char popBack();
    std::string toString() const;

    // Methods for managing stackStr
    std::string strFront() const;
    std::string strBack() const;
    void strPushFront(std::string inStr);
    void strPushBack(std::string inStr);
    std::string strPopFront();
    std::string strPopBack();
};

#endif /* DEQUE_H */