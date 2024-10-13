#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>

class Deque {
    private:
        class Node {
            public:
                char ch;
                Node * prev = nullptr;
                Node * next = nullptr;
        };
        // Head and Tail pointers
        Node *head = nullptr;
        Node *tail = nullptr;

    public:
        Deque() {};
        char front();
        char back();
        void pushFront(char ch);
        void pushBack(char ch);
        char popFront();
        char popBack();
        bool isEmpty();

};

class DequeEmpty : std::runtime_error {
    public:
        DequeEmpty() : std::runtime_error("Deque is empty") {} ;
};

// Return current front of the deque
char Deque::front(){
    if(isEmpty()){
        throw DequeEmpty();
    }
    else {
        return head->ch;
    }
}

// Return current back of the deque
char Deque::back(){
    if(isEmpty()){
        throw DequeEmpty();
    } else {
        return tail->ch;
    }

}

// Push new node to front of deque
void Deque::pushFront(char ch){
    Node *n = new Node;
    // If first node in deque
    if(isEmpty()){
        head = n;
        tail = n;
    } else {
        Node *thead = head;
        n->next = head;
        head = n;
        thead->prev = n;
    }
    return;
}

// Push new node to back of deque
void Deque::pushBack(char ch){
    Node *n = new Node;
    // If first node in deque
    if(isEmpty()){
        head = n;
        tail = n;
    } else {
        Node *ttail = tail;
        n->prev = tail;
        tail = n;
        ttail->next = n;
    }
    return;
}

// Pop first node from deque
char Deque::popFront(){
    char ch = ' ';
    if(isEmpty()){
        throw DequeEmpty();
    } else {
        ch = head->ch;
        Node *old = head;
        head = head->next;
        head->prev = nullptr;
        delete old;
    }
    return ch;
}

// Pop last node from deque
char Deque::popBack(){
    char ch = ' ';
    if(isEmpty()){
        throw DequeEmpty();
    } else {
        ch = tail->ch;
        Node *old = tail;
        tail = tail->prev;
        tail->next == nullptr;
        delete old;
    }
    return ch;
}

// Check if deque is empty
bool Deque::isEmpty(){
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}


#endif /* DEQUE_H */