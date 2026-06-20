#include "character.hpp"

#include <iostream>
#include <utility>

#include "damageable.hpp"

void Character::setWeapon(std::unique_ptr<Weapon> weapon) {
    if (!weapon) return;

    weapon_ = std::move(weapon);  // reassigning frees the old weapon
    std::cout << "New weapon equipped -> Name: " << weapon_->getName()
              << " Damage: " << weapon_->getDamage() << '\n';
}

void Character::restoreHP(int heal) {
    hp_ += heal;
    std::cout << getName() << " healed " << heal
              << " (current HP: " << hp_ << ")\n";
}

void Character::attack(Damageable& target) {
    std::cout << getName() << " attacks " << target.getName() << '\n';
    const int finalDamage = weapon_ ? weapon_->getDamage() : damageBase_;
    target.takeDamage(finalDamage);
}

void Character::onZeroHP() {
    std::cout << getName() << " died\n";
}
