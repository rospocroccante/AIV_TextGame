#pragma once

#include "baseEntity.hpp"

// abstract: each subclass reacts to dying via onZeroHP
class Damageable : public BaseEntity {
public:
    Damageable(std::string name, int hp)
        : BaseEntity(std::move(name)), hp_(hp) {}

    int getHP() const { return hp_; }

    virtual void takeDamage(int damage);

protected:
    int hp_;

private:
    virtual void onZeroHP() = 0;
};
