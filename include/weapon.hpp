#pragma once

#include <memory>
#include <string>
#include <utility>

#include "randomGen.hpp"

// Polymorphic weapon. Melee is unlimited; ranged hits harder but burns ammo and
// becomes unusable when empty (the wielder then falls back to bare hands).
class Weapon {
public:
    Weapon(std::string name, int damage)
        : name_(std::move(name)), damage_(damage) {}
    virtual ~Weapon() = default;

    const std::string& getName() const { return name_; }

    virtual int rollDamage() const { return damage_; }
    virtual bool canUse() const { return true; }
    virtual void onUse() {}
    virtual std::string kind() const = 0;
    virtual std::string ammoInfo() const { return ""; }

protected:
    std::string name_;
    int damage_;
};

class MeleeWeapon : public Weapon {
public:
    MeleeWeapon(std::string name, int damage) : Weapon(std::move(name), damage) {}

    std::string kind() const override { return "melee"; }
};

class RangedWeapon : public Weapon {
public:
    RangedWeapon(std::string name, int damage, int ammo)
        : Weapon(std::move(name), damage), ammo_(ammo) {}

    bool canUse() const override { return ammo_ > 0; }
    void onUse() override { if (ammo_ > 0) --ammo_; }
    std::string kind() const override { return "ranged"; }
    std::string ammoInfo() const override { return " [ammo " + std::to_string(ammo_) + "]"; }

    int ammo() const { return ammo_; }

private:
    int ammo_;
};

// small random factory so each run feels different
namespace WeaponFactory {

inline std::unique_ptr<Weapon> randomMelee() {
    return std::make_unique<MeleeWeapon>(RandomGen::getRandomString(4) + " Blade",
                                         RandomGen::getIntInRange(5, 8));
}

inline std::unique_ptr<Weapon> randomRanged() {
    return std::make_unique<RangedWeapon>(RandomGen::getRandomString(4) + " Bow",
                                          RandomGen::getIntInRange(7, 11),
                                          RandomGen::getIntInRange(3, 5));
}

}  // namespace WeaponFactory
