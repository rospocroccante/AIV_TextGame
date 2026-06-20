#pragma once

#include <memory>
#include <vector>

#include "combatant.hpp"

// Holds the two sides and drives the combat finite-state machine to the end.
// Combatants are stored behind unique_ptr so their addresses stay stable while
// we pass pointers around.
class Battle {
public:
    Battle(std::vector<std::unique_ptr<Combatant>> party,
           std::vector<std::unique_ptr<Combatant>> horde);

    void run();

    std::vector<Combatant*> livingFoesOf(const Combatant& self);
    std::vector<Combatant*> livingParty();
    std::vector<Combatant*> livingHorde();

    bool partyWiped();
    bool hordeWiped();

    int round() const { return round_; }
    void nextRound() { ++round_; }

private:
    bool onParty(const Combatant& c) const;

    std::vector<std::unique_ptr<Combatant>> party_;
    std::vector<std::unique_ptr<Combatant>> horde_;
    int round_ = 1;
};
