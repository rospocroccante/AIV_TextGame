#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "randomGen.hpp"

class Weapon {
public:
    Weapon(std::string name, int damage)
        : name_(std::move(name)), damage_(damage) {}

    const std::string& getName() const { return name_; }
    int getDamage() const { return damage_; }

    void displayStats() const {
        std::cout << "Name: " << name_ << " - Damage: " << damage_ << '\n';
    }

    static std::unique_ptr<Weapon> weaponFactory() {
        return std::make_unique<Weapon>(RandomGen::getRandomString(5),
                                        RandomGen::getIntInRange(5, 8));
    }

    bool operator>(const Weapon& rhs) const { return damage_ > rhs.damage_; }
    bool operator<(const Weapon& rhs) const { return rhs > *this; }

private:
    std::string name_;
    int damage_;
};
