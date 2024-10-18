#include <string>
#include <iostream>

#include "Deque.hpp"

class DequeEmpty : std::runtime_error {
public:
    DequeEmpty() : std::runtime_error("Deque is empty") {};
};

// Construct a Deque from a string
Deque::Deque(std::string inStr) {
    int strLen = inStr.length();

    for (int i = 0; i < strLen; i++) {
        pushBack(inStr[i]);
    }
}

// Deque class deconstructor
Deque::~Deque() {
    while (!isEmpty())
        popFront();
}

// Return current front of the deque
char Deque::front() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return head->ch;
    }
}

// Return current back of the deque
char Deque::back() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return tail->ch;
    }
}

// Return current presendence of front of stack (for operators)
int Deque::frontPres() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return head->pres;
    }
}

// Return current presedence of back of stack (for operators)
int Deque::backPres() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return tail->pres;
    }
}

// Push new node to front of deque
void Deque::pushFront(char ch, int pres) {
    Node *n = new Node;
    n->ch = ch;
    n->pres = pres;
    // If first node in deque
    if (isEmpty()) {
        head = n;
        tail = n;
    }
    else {
        Node *thead = head;
        n->next = head;
        head = n;
        thead->prev = n;
    }
    return;
}

// Push new node to back of deque
void Deque::pushBack(char ch, int pres) {
    Node *n = new Node;
    n->ch = ch;
    n->pres = pres;
    // If first node in deque
    if (isEmpty()) {
        head = n;
        tail = n;
    }
    else {
        Node *ttail = tail;
        n->prev = tail;
        tail = n;
        ttail->next = n;
    }
    return;
}

// Pop first node from deque
char Deque::popFront() {
    char ch = ' ';
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else if (head == tail) { // If there is only one node left
        ch = head->ch;
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        ch = head->ch;
        Node *old = head;
        head = head->next;
        head->prev = nullptr;
        delete old;
    }
    return ch;
}

// Pop last node from deque
char Deque::popBack() {
    char ch = ' ';
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else if (tail == head) { // If there is only one node left
        ch = tail->ch;
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
    else {
        ch = tail->ch;
        Node *old = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete old;
    }
    return ch;
}

// Check if deque is empty
bool Deque::isEmpty() const {
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}

std::string Deque::toString() const {
    Node *temp = head;
    std::string outStr = "";

    while (temp != nullptr) {
        outStr += temp->ch;
        temp = temp->next;
    }

    return outStr;
}

// int main() { // main function just for testing (remove before submission)
//     Deque d1;

//     d1.pushBack('h');
//     d1.pushBack('e');
//     d1.pushBack('l');
//     d1.pushBack('l');
//     d1.pushBack('o');

//     std::cout << d1.toString() << std::endl;

//     Deque d2("goodbye");

//     std::cout << d2.toString() << std::endl;

//     d2.popFront();
//     d2.popFront();
//     d2.popFront();
//     d2.popFront();

//     std::cout << d2.toString() << std::endl;

//     std::cout << d1.isEmpty() << std::endl;

//     while (!d1.isEmpty())
//         d1.popBack();

//     std::cout << d1.isEmpty() << std::endl;

//     std::cout << d1.toString() << std::endl;

//     d1.~Deque();
//     d2.~Deque();

//     std::cout << d1.toString() << std::endl;
//     std::cout << d2.toString() << std::endl;


//     return 0;
// }