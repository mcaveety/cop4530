#include <string>
#include <iostream>

#include "Deque.hpp"

class DequeEmpty : std::runtime_error
{
public:
    DequeEmpty() : std::runtime_error("Deque is empty") {};
};

// Return current front of the deque
char Deque::front() const
{
    if (isEmpty())
    {
        throw DequeEmpty();
    }
    else
    {
        return head->ch;
    }
}

// Return current back of the deque
char Deque::back() const
{
    if (isEmpty())
    {
        throw DequeEmpty();
    }
    else
    {
        return tail->ch;
    }
}

// Push new node to front of deque
void Deque::pushFront(char ch)
{
    Node *n = new Node;
    // If first node in deque
    if (isEmpty())
    {
        head = n;
        tail = n;
    }
    else
    {
        Node *thead = head;
        n->next = head;
        head = n;
        thead->prev = n;
    }
    return;
}

// Push new node to back of deque
void Deque::pushBack(char ch)
{
    Node *n = new Node;
    // If first node in deque
    if (isEmpty())
    {
        head = n;
        tail = n;
    }
    else
    {
        Node *ttail = tail;
        n->prev = tail;
        tail = n;
        ttail->next = n;
    }
    return;
}

// Pop first node from deque
char Deque::popFront()
{
    char ch = ' ';
    if (isEmpty())
    {
        throw DequeEmpty();
    }
    else
    {
        ch = head->ch;
        Node *old = head;
        head = head->next;
        head->prev = nullptr;
        delete old;
    }
    return ch;
}

// Pop last node from deque
char Deque::popBack()
{
    char ch = ' ';
    if (isEmpty())
    {
        throw DequeEmpty();
    }
    else
    {
        ch = tail->ch;
        Node *old = tail;
        tail = tail->prev;
        tail->next = nullptr;
        delete old;
    }
    return ch;
}

// Check if deque is empty
bool Deque::isEmpty() const
{
    if (head == nullptr && tail == nullptr)
        return true;
    return false;
}