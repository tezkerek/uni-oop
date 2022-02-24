#include <iostream>

int main() {
    uint a, b;
    std::cin >> a >> b;

    for (uint x = a; x <= b; ++x) {
        uint divisor_sum = 0;

        for (uint d = 1; d <= x / 2; ++d) {
            if (x % d == 0) {
                divisor_sum += d;
            }
        }

        if (divisor_sum == x) {
            std::cout << x << " ";
        }
    }

    std::cout << "sunt numere perfecte.\n";

    return 0;
}
