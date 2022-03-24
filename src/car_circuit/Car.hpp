#pragma once

#include <string>
#include <memory>

class Car {
public:
    Car() = default;
    Car(const Car &rhs) = default;
    virtual ~Car() = default;

    virtual std::string getName() const = 0;
    virtual unsigned getSpeed() const = 0;
};

class Dacia : public Car {
public:
    Dacia() = default;
    Dacia(const Dacia &rhs) = default;
    ~Dacia() override = default;

    std::string getName() const override;
    unsigned getSpeed() const override;
};

class Toyota : public Car {
public:
    Toyota() = default;
    Toyota(const Toyota &rhs) = default;
    ~Toyota() override = default;

    std::string getName() const override;
    unsigned getSpeed() const override;
};

class Renault : public Car {
public:
    Renault() = default;
    Renault(const Renault &rhs) = default;
    ~Renault() override = default;

    std::string getName() const override;
    unsigned getSpeed() const override;
};
