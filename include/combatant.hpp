#pragma once

#include <memory>
#include <string>
#include <utility>

#include "controller.hpp"
#include "damageable.hpp"
#include "weapon.hpp"

// A fighter on either side. Owns its weapon and its controller (Strategy), and
// carries a tiny behavior state: it gets Enraged at or below 30% HP and hits harder.
class Combatant : public Damageable {
public:
    Combatant(std::string name, int hp, int baseDamage,
              std::unique_ptr<Controller> controller,
              std::unique_ptr<Weapon> weapon = nullptr,
              int potions = 0)
        : Damageable(std::move(name), hp),
          baseDamage_(baseDamage),
          controller_(std::move(controller)),
          weapon_(std::move(weapon)),
          potions_(potions) {}

    Controller& controller() { return *controller_; }
    const Weapon* weapon() const { return weapon_.get(); }
    int potions() const { return potions_; }
    bool enraged() const { return enraged_; }

    void performAttack(Combatant& target);
    bool drinkPotion();      // heal from a potion; false if none left
    void updateBehavior();   // Normal -> Enraged when low on HP

private:
    void onZeroHP() override;

    int baseDamage_;
    std::unique_ptr<Controller> controller_;
    std::unique_ptr<Weapon> weapon_;
    int potions_ = 0;
    bool enraged_ = false;
};
