#pragma once

#include <utility>

#include "baseEntity.hpp"

// abstract: each subclass reacts to dying via onZeroHP
class Damageable : public BaseEntity {
public:
    Damageable(std::string name, int hp)
        : BaseEntity(std::move(name)), hp_(hp), maxHp_(hp) {}

    int getHP() const { return hp_; }
    int getMaxHP() const { return maxHp_; }
    bool isAlive() const { return hp_ > 0; }

    virtual void takeDamage(int damage);
    void heal(int amount);

protected:
    int hp_;
    int maxHp_;

private:
    virtual void onZeroHP() = 0;
};
