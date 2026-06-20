#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "battle.hpp"
#include "combatant.hpp"
#include "controller.hpp"
#include "weapon.hpp"

int main() {
    std::cout << "Enter your hero's name:\n";
    std::string heroName;
    std::cin >> heroName;

    std::vector<std::unique_ptr<Combatant>> party;
    // the whole party is AI-controlled (auto-battle); swap any one for a
    // HumanController to take the controls yourself
    party.push_back(std::make_unique<Combatant>(
        heroName, 26, 4, std::make_unique<AIController>(true),
        std::make_unique<MeleeWeapon>("Iron Sword", 7), 3));
    party.push_back(std::make_unique<Combatant>(
        "Archer", 18, 3, std::make_unique<AIController>(true),
        std::make_unique<RangedWeapon>("Oak Bow", 9, 4), 2));
    party.push_back(std::make_unique<Combatant>(
        "Mage", 16, 3, std::make_unique<AIController>(true),
        std::make_unique<RangedWeapon>("Spark Staff", 10, 3), 2));

    std::vector<std::unique_ptr<Combatant>> horde;
    const int hordeSize = 5;
    for (int i = 0; i < hordeSize; ++i) {
        horde.push_back(std::make_unique<Combatant>(
            "Goblin_" + std::to_string(i), 12, 3,
            std::make_unique<AIController>(false)));
    }

    Battle battle(std::move(party), std::move(horde));
    battle.run();
    return 0;
}
