#include "combatant.hpp"

#include <iostream>
#include <string>

void Combatant::performAttack(Combatant& target) {
    int dmg;
    std::string with;
    if (weapon_ && weapon_->canUse()) {
        dmg = weapon_->rollDamage();
        weapon_->onUse();
        with = weapon_->getName();
    } else {
        dmg = baseDamage_;
        with = weapon_ ? "bare hands (out of ammo)" : "bare hands";
    }
    if (enraged_) {
        dmg = dmg * 3 / 2;  // enraged fighters hit 50% harder
    }

    std::cout << "  " << getName() << " attacks " << target.getName()
              << " with " << with << (enraged_ ? " [ENRAGED]" : "") << '\n';
    target.takeDamage(dmg);
}

bool Combatant::drinkPotion() {
    if (potions_ <= 0) {
        return false;
    }
    --potions_;
    std::cout << "  " << getName() << " drinks a potion (" << potions_ << " left)\n";
    heal(8);
    return true;
}

void Combatant::updateBehavior() {
    // tiny behavior FSM: at or below 30% HP, enrage once and stay enraged
    if (!enraged_ && isAlive() && hp_ * 10 <= maxHp_ * 3) {
        enraged_ = true;
        std::cout << "  " << getName() << " is ENRAGED!\n";
    }
}

void Combatant::onZeroHP() {
    std::cout << "    " << getName() << " falls!\n";
}
