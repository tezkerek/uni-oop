#pragma once

#include <istream>
#include <ostream>

namespace CharQueue {

class Node {
private:
    char value;
    Node *next;

public:
    explicit Node(char value, Node *next = nullptr);
    char getValue() const;
    Node *getNext() const;
    void setValue(char value);
    void setNext(Node *next);
};

class CharQueue {
private:
    Node *start, *end;
    std::size_t size_;

public:
    CharQueue();
    CharQueue(const CharQueue &rhs);
    explicit CharQueue(const std::string &str);
    ~CharQueue();
    std::size_t size() const;
    bool isEmpty() const;
    void push(char value);
    char pop();
    void clear();

    CharQueue &operator=(const std::string &str);

    friend CharQueue operator+(const CharQueue &lhs, const CharQueue &rhs);
    friend CharQueue operator-(const CharQueue &lhs, const CharQueue &rhs);
};

std::ostream &operator<<(std::ostream &os, CharQueue &rhs);
std::istream &operator>>(std::istream &is, CharQueue &rhs);
} // namespace CharQueue
