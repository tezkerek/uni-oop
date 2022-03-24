#include "Car.hpp"
#include "Circuit.hpp"
#include <iostream>
#include <memory>

int main() {
    Circuit circuit;

    circuit.addCar(std::make_unique<Renault>());
    circuit.addCar(std::make_unique<Dacia>());
    circuit.addCar(std::make_unique<Toyota>());
    circuit.addCar(std::make_unique<Dacia>());

    std::size_t rank = 1;
    for (auto &c : circuit.getRanking()) {
        std::cout << rank << ". " << c->getName() << '\n';
        ++rank;
    }
    return 0;
}
