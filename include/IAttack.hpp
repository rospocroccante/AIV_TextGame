#pragma once

class Damageable;

class IAttack {
public:
    virtual ~IAttack() = default;

    virtual void attack(Damageable& target) = 0;
};
