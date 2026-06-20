#include "damageable.hpp"

#include <iostream>

void Damageable::takeDamage(int damage) {
    hp_ -= damage;
    const int shown = hp_ < 0 ? 0 : hp_;
    std::cout << "    " << name_ << " takes " << damage
              << " (HP " << shown << "/" << maxHp_ << ")\n";
    if (hp_ <= 0) {
        onZeroHP();
    }
}

void Damageable::heal(int amount) {
    hp_ += amount;
    if (hp_ > maxHp_) {
        hp_ = maxHp_;
    }
    std::cout << "    " << name_ << " heals " << amount
              << " (HP " << hp_ << "/" << maxHp_ << ")\n";
}
