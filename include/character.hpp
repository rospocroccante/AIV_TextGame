#pragma once

#include <memory>
#include <string>

#include "IAttack.hpp"
#include "damageable.hpp"
#include "weapon.hpp"

class Character : public Damageable, public IAttack {
public:
    Character(std::string name, int hp, int damageBase)
        : Damageable(std::move(name), hp), damageBase_(damageBase) {}

    const Weapon* getWeapon() const { return weapon_.get(); }
    void setWeapon(std::unique_ptr<Weapon> weapon);

    void restoreHP(int heal);
    void attack(Damageable& target) override;

private:
    void onZeroHP() override;

    int damageBase_;
    std::unique_ptr<Weapon> weapon_;
};
