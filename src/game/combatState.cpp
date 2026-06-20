#include "combatState.hpp"

#include <iostream>

#include "battle.hpp"
#include "combatant.hpp"

namespace {
void act(Battle& battle, Combatant& actor) {
    actor.updateBehavior();
    auto foes = battle.livingFoesOf(actor);
    const Action a = actor.controller().decide(battle, actor);
    switch (a.type) {
        case Action::Type::Attack:
            if (a.target >= 0 && a.target < static_cast<int>(foes.size())) {
                actor.performAttack(*foes[a.target]);
            }
            break;
        case Action::Type::Heal:
            if (!actor.drinkPotion()) {
                std::cout << "  " << actor.getName() << " has no potions!\n";
            }
            break;
        case Action::Type::Pass:
            break;
    }
}
}  // namespace

std::unique_ptr<CombatState> PartyTurnState::run(Battle& battle) {
    std::cout << "\n=== Round " << battle.round() << " : your party acts ===\n";
    for (Combatant* ally : battle.livingParty()) {
        if (battle.hordeWiped()) {
            break;
        }
        act(battle, *ally);
    }
    if (battle.hordeWiped()) {
        return std::make_unique<VictoryState>();
    }
    return std::make_unique<HordeTurnState>();
}

std::unique_ptr<CombatState> HordeTurnState::run(Battle& battle) {
    std::cout << "\n--- the horde strikes back ---\n";
    for (Combatant* enemy : battle.livingHorde()) {
        if (battle.partyWiped()) {
            break;
        }
        act(battle, *enemy);
    }
    if (battle.partyWiped()) {
        return std::make_unique<DefeatState>();
    }
    battle.nextRound();
    if (battle.round() > 50) {  // safety net against an endless stalemate
        return std::make_unique<DefeatState>();
    }
    return std::make_unique<PartyTurnState>();
}

std::unique_ptr<CombatState> VictoryState::run(Battle&) {
    std::cout << "\nVictory! The horde is cleared.\n";
    return nullptr;
}

std::unique_ptr<CombatState> DefeatState::run(Battle&) {
    std::cout << "\nDefeat... your party has fallen.\n";
    return nullptr;
}
