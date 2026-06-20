#pragma once

#include "action.hpp"

class Battle;
class Combatant;

// Strategy: decides a combatant's action each turn. Swapping the controller is
// how we choose between a human player and the AI, at runtime.
class Controller {
public:
    virtual ~Controller() = default;

    virtual Action decide(Battle& battle, Combatant& self) = 0;
    virtual bool isHuman() const { return false; }
};

// Reads the action (and target) from the console.
class HumanController : public Controller {
public:
    Action decide(Battle& battle, Combatant& self) override;
    bool isHuman() const override { return true; }
};

// Rule-based policy:
//   hurt and still has potions  -> heal
//   otherwise                   -> attack the weakest living foe
class AIController : public Controller {
public:
    explicit AIController(bool canHeal) : canHeal_(canHeal) {}

    Action decide(Battle& battle, Combatant& self) override;

private:
    bool canHeal_;
};
