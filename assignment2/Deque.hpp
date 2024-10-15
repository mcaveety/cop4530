#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>

class Deque {
public:
    class Node {
    public:
        char ch = 0;
        Node *prev = nullptr;
        Node *next = nullptr;
    };

    // Head and Tail pointers
    Node *head = nullptr;
    Node *tail = nullptr;

    Deque() {};
    Deque(std::string inStr);
    ~Deque() {};
    char front() const;
    char back() const;
    void pushFront(char ch);
    void pushBack(char ch);
    char popFront();
    char popBack();
    bool isEmpty() const;
    std::string toString() const;
};

#endif /* DEQUE_H */