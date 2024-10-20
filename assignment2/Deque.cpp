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
    
    if (isEmpty()) { // If first node in deque
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
    
    if (isEmpty()) { // If first node in deque
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

bool Deque::isOneNode() const {
    if (head == tail)
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

std::string Deque::strFront() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return head->stackStr;
    }
}

std::string Deque::strBack() const {
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else {
        return tail->stackStr;
    }
}

void Deque::strPushFront(std::string inStr) {
    Node *n = new Node;
    n->stackStr = inStr;

    if (isEmpty()) { // If first node in deque
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

void Deque::strPushBack(std::string inStr) {
    Node *n = new Node;
    n->stackStr = inStr;

    if(isEmpty()) {
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

std::string Deque::strPopFront() {
    std::string str = "";
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else if (head == tail) { // If there is only one node left
        str = head->stackStr;
        delete head;
        head = nullptr;
        tail = nullptr;
    }
    else {
        str = head->stackStr;
        Node *old = head;
        head = head->next;
        head->prev = nullptr;
        delete old;
    }

    return str;
}

std::string Deque::strPopBack() {
    std::string str = "";
    if (isEmpty()) {
        throw DequeEmpty();
    }
    else if (tail == head) { // If there is only one node left
        str = tail->stackStr;
        delete tail;
        head = nullptr;
        tail = nullptr;
    }
    else {
        str = tail->stackStr;
        Node *old = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete old;
    }

    return str;
}

// int main() { // main function just for testing (remove before submission)
//     Deque d1;

//     d1.strPushFront(" is ");
//     d1.strPushBack(" a ");
//     d1.strPushFront(" this ");
//     d1.strPushBack(" test " );

//     std::cout << d1.strFront() << std::endl;
//     std::cout << d1.strBack() << std::endl;
//     std::cout << std::endl;

//     while (!d1.isEmpty()) {
//         std::cout << d1.strPopFront();
//     }
//     std::cout << std::endl;

//     Deque d2;

//     d2.strPushBack("This is a sentence that takes up one node.");

//     if (d2.isOneNode()) {
//         std::cout << d2.strPopBack() << std::endl;
//     }

//     return 0;
// }