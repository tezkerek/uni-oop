#pragma once

#include "Car.hpp"
#include <algorithm>
#include <memory>
#include <vector>

using CarPtr = std::shared_ptr<Car>;

class Circuit {
private:
    std::vector<CarPtr> cars;

public:
    Circuit() = default;
    Circuit(const Circuit& rhs) = default;
    void addCar(const CarPtr &car);
    std::vector<CarPtr> getRanking();
};
