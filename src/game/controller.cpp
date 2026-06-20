#include "controller.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "battle.hpp"
#include "combatant.hpp"

Action HumanController::decide(Battle& battle, Combatant& self) {
    auto foes = battle.livingFoesOf(self);

    std::cout << "\n  " << self.getName() << "  HP " << self.getHP() << "/"
              << self.getMaxHP();
    if (self.weapon() != nullptr) {
        std::cout << "  | " << self.weapon()->getName() << self.weapon()->ammoInfo();
    }
    std::cout << "  | potions " << self.potions() << "\n  Enemies:\n";
    for (std::size_t i = 0; i < foes.size(); ++i) {
        std::cout << "    [" << i << "] " << foes[i]->getName() << "  HP "
                  << foes[i]->getHP() << "/" << foes[i]->getMaxHP()
                  << (foes[i]->enraged() ? "  (enraged)" : "") << "\n";
    }

    while (true) {
        std::cout << "  " << self.getName() << " action [attack/heal]: ";
        std::string cmd;
        if (!(std::cin >> cmd)) {
            return {Action::Type::Pass, -1};
        }
        if (cmd == "heal") {
            return {Action::Type::Heal, -1};
        }
        if (cmd == "attack") {
            if (foes.empty()) {
                return {Action::Type::Pass, -1};
            }
            if (foes.size() == 1) {
                return {Action::Type::Attack, 0};
            }
            std::cout << "  target [0-" << foes.size() - 1 << "]: ";
            int idx = -1;
            if (!(std::cin >> idx)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            if (idx >= 0 && idx < static_cast<int>(foes.size())) {
                return {Action::Type::Attack, idx};
            }
        }
        std::cout << "  invalid\n";
    }
}

Action AIController::decide(Battle& battle, Combatant& self) {
    // hurt and still has a potion -> heal
    if (canHeal_ && self.potions() > 0 && self.getHP() * 100 <= self.getMaxHP() * 35) {
        return {Action::Type::Heal, -1};
    }
    // otherwise focus-fire the weakest living foe
    auto foes = battle.livingFoesOf(self);
    if (foes.empty()) {
        return {Action::Type::Pass, -1};
    }
    int best = 0;
    for (std::size_t i = 1; i < foes.size(); ++i) {
        if (foes[i]->getHP() < foes[best]->getHP()) {
            best = static_cast<int>(i);
        }
    }
    return {Action::Type::Attack, best};
}
