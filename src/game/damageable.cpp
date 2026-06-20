#include "damageable.hpp"

#include <iostream>

void Damageable::takeDamage(int damage) {
    std::cout << name_ << " took " << damage << '\n';
    hp_ -= damage;
    if (hp_ <= 0) {
        onZeroHP();
    }
}
