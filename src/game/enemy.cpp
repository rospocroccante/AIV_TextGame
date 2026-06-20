#include "enemy.hpp"

#include <iostream>

#include "damageable.hpp"
#include "randomGen.hpp"

void Enemy::attack(Damageable& target) {
    const int damage = RandomGen::getIntInRange(damageBase_, damageBase_ + strength_);
    std::cout << getName() << " attacks " << target.getName() << '\n';
    target.takeDamage(damage);
}

void Enemy::onZeroHP() {
    active_ = false;
    std::cout << getName() << " died\n";
}
