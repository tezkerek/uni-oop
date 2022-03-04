#include "CharQueue.hpp"
#include <iostream>

int main() {
    CharQueue::CharQueue cq1;
    std::cout << "Queue 1: ";
    std::cin >> cq1;

    CharQueue::CharQueue cq2;
    std::cout << "Queue 2: ";
    std::cin >> cq2;

    auto cq_sum = cq1 + cq2;
    std::cout << "Queue 1 + Queue 2: " << cq_sum << '\n';
    auto cq_diff = cq1 - cq2;
    std::cout << "Queue 1 - Queue 2: " << cq_diff << '\n';

    return 0;
}
