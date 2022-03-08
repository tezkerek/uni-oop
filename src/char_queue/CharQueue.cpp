#include "CharQueue.hpp"
#include <algorithm>
#include <istream>
#include <ostream>
#include <string>

namespace CharQueue {

Node::Node(char value, Node *next) : value(value), next(next) {}
char Node::getValue() const { return value; }
Node *Node::getNext() const { return next; }
void Node::setValue(char value) { this->value = value; }
void Node::setNext(Node *next) { this->next = next; }

CharQueue::CharQueue() : start(nullptr), end(nullptr), size_(0) {}
CharQueue::CharQueue(const CharQueue &rhs) : CharQueue() {
    if (rhs.isEmpty()) {
        return;
    }
    // At least one node in rhs

    // Clone every node in rhs
    auto prevNode = start = new Node(rhs.start->getValue());
    auto origNode = rhs.start->getNext();
    while (origNode != nullptr) {
        auto newNode = new Node(origNode->getValue());
        prevNode->setNext(newNode);
        prevNode = newNode;
        origNode = origNode->getNext();
    }
    end = prevNode;
    size_ = rhs.size();
}
CharQueue::CharQueue(const std::string &str) : CharQueue() { *this = str; }
CharQueue::~CharQueue() {
    auto node = start;
    while (node != nullptr) {
        auto nextNode = node->getNext();
        delete node;
        node = nextNode;
    }
}

std::size_t CharQueue::size() const { return size_; }
bool CharQueue::isEmpty() const { return start == nullptr; }

void CharQueue::push(char value) {
    Node *newNode = new Node(value);
    if (isEmpty()) {
        start = end = newNode;
    } else {
        end->setNext(newNode);
        end = newNode;
    }
    size_++;
}

char CharQueue::pop() {
    auto value = start->getValue();
    auto oldStart = start;
    start = start->getNext();
    delete oldStart;
    if (isEmpty()) {
        // oldStart == end, so end was also freed
        end = nullptr;
    }
    size_--;
    return value;
}

void CharQueue::clear() {
    while (!isEmpty()) {
        pop();
    }
}

CharQueue &CharQueue::operator=(const std::string &str) {
    // Remove extra nodes from current queue (if str is shorter than the queue)
    for (std::size_t i = str.length(); i < size(); i++) {
        pop();
    }

    // Set values for existing nodes
    auto node = start;
    std::size_t pos = 0;
    while (node != nullptr) {
        node->setValue(str[pos]);
        pos++;
        node = node->getNext();
    }

    // Add nodes for any remaining chars in the string (if str is longer than
    // the queue)
    for (; pos < str.length(); pos++) {
        push(str[pos]);
    }

    return *this;
}

CharQueue operator+(const CharQueue &lhs, const CharQueue &rhs) {
    CharQueue result(lhs);
    auto node = rhs.start;
    while (node != nullptr) {
        result.push(node->getValue());
        node = node->getNext();
    }

    return result;
}

CharQueue operator-(const CharQueue &lhs, const CharQueue &rhs) {
    CharQueue result;
    auto lnode = lhs.start;
    auto rnode = rhs.start;
    while (lnode != nullptr && rnode != nullptr) {
        result.push(std::max(lnode->getValue(), rnode->getValue()));
        lnode = lnode->getNext();
        rnode = rnode->getNext();
    }

    return result;
}

std::ostream &operator<<(std::ostream &os, CharQueue &rhs) {
    while (!rhs.isEmpty()) {
        os << rhs.pop();
    }

    return os;
}

std::istream &operator>>(std::istream &is, CharQueue &rhs) {
    std::string str;
    is >> str;
    for (auto ch : str) {
        rhs.push(ch);
    }

    return is;
}
} // namespace CharQueue
