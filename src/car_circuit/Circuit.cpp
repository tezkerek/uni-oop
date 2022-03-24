#include "Circuit.hpp"
#include <memory>

void Circuit::addCar(const CarPtr &car) { cars.emplace_back(car); }

std::vector<CarPtr> Circuit::getRanking() {
    std::stable_sort(cars.begin(), cars.end(),
                     [](const CarPtr &car1, const CarPtr &car2) {
                         return car1->getSpeed() > car2->getSpeed();
                     });

    return cars;
}
