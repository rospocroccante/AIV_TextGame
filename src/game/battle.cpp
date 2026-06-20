#include "battle.hpp"

#include <iostream>
#include <utility>

#include "combatState.hpp"

namespace {
std::vector<Combatant*> livingOf(std::vector<std::unique_ptr<Combatant>>& side) {
    std::vector<Combatant*> out;
    for (auto& c : side) {
        if (c->isAlive()) {
            out.push_back(c.get());
        }
    }
    return out;
}
}  // namespace

Battle::Battle(std::vector<std::unique_ptr<Combatant>> party,
               std::vector<std::unique_ptr<Combatant>> horde)
    : party_(std::move(party)), horde_(std::move(horde)) {}

std::vector<Combatant*> Battle::livingParty() { return livingOf(party_); }
std::vector<Combatant*> Battle::livingHorde() { return livingOf(horde_); }

bool Battle::onParty(const Combatant& c) const {
    for (const auto& p : party_) {
        if (p.get() == &c) {
            return true;
        }
    }
    return false;
}

std::vector<Combatant*> Battle::livingFoesOf(const Combatant& self) {
    return onParty(self) ? livingHorde() : livingParty();
}

bool Battle::partyWiped() { return livingParty().empty(); }
bool Battle::hordeWiped() { return livingHorde().empty(); }

void Battle::run() {
    std::cout << "A horde of " << horde_.size() << " enemies appears!\n";
    std::unique_ptr<CombatState> state = std::make_unique<PartyTurnState>();
    while (state) {
        state = state->run(*this);
    }
}
