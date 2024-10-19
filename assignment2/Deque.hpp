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
        Node *prev = nullptr;
        Node *next = nullptr;
    };

    // Head and Tail pointers
    Node *head = nullptr;
    Node *tail = nullptr;

    Deque() {};
    Deque(std::string inStr);
    ~Deque();
    char front() const;
    char back() const;
    int frontPres() const;
    int backPres() const;
    void pushFront(char ch, int pres = 0);
    void pushBack(char ch, int pres = 0);
    char popFront();
    char popBack();
    bool isEmpty() const;
    std::string toString() const;
};

#endif /* DEQUE_H */