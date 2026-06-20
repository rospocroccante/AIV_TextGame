#pragma once

#include <string>

#include "IAttack.hpp"
#include "damageable.hpp"

class Enemy : public Damageable, public IAttack {
public:
    Enemy(std::string name, int hp, int damageBase, int strength)
        : Damageable(std::move(name), hp),
          damageBase_(damageBase),
          strength_(strength) {}

    bool isActive() const { return active_; }
    void attack(Damageable& target) override;

private:
    void onZeroHP() override;

    int damageBase_;
    int strength_;
    bool active_ = true;
};
