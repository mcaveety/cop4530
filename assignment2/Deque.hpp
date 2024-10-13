#ifndef DEQUE_H
#define DEQUE_H

#include <string>
#include <iostream>

class Deque {
    private:
        class Node {
            public:
                char ch;
                Node * prev;
                Node * next;
        };
        // Head and Tail sentinel nodes of deque
        Node *head = nullptr;
        Node *tail = nullptr;

        // Sets up the start of a deque
        void setDeque(char ch);
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

// Return current front of the deque
char Deque::front(){
    if(isEmpty()){
        std::cout << "Empty deque" << std::endl;
        return ' ';
    }
    else {
        return head->next->ch;
    }
}

// Return current back of the deque
char Deque::back(){
    if(isEmpty()){
        std::cout << "Empty deque" << std::endl;
    } else {
        return tail->prev->ch;
    }

}

// Push new node to front of deque
void Deque::pushFront(char ch){
    
}

// Push new node to back of deque
void Deque::pushBack(char ch){


}

// Pop first node from deque
char Deque::popFront(){
    if(isEmpty()){
        std::cout << "Deque empty! Nothing to pop" << std::endl;
    } else {

    }
}

// Pop last node from deque
char Deque::popBack(){
    if(isEmpty()){
        std::cout << "Deque empty! Nothing to pop" << std::endl;
    } else {

    }
}

// Check if deque is empty
bool Deque::isEmpty(){
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}



#endif /* DEQUE_H */