#include "game.hpp"

#include <iostream>
#include <memory>
#include <string>

#include "weapon.hpp"

void Game::init(int enemyCount) {
    enemies_.reserve(static_cast<std::size_t>(enemyCount));
    for (int i = 0; i < enemyCount; ++i) {
        enemies_.emplace_back("Enemy_" + std::to_string(i), 10, 3, 3);
    }
    currentEnemyIndex_ = 0;
}

std::string Game::getStatus() const {
    switch (result_) {
        case GameResult::Win:  return "Win";
        case GameResult::Lose: return "Lose";
        default:               return "Ongoing";
    }
}

void Game::update() {
    Enemy& current = enemies_.at(currentEnemyIndex_);
    if (current.isActive()) {
        combat();
        return;
    }

    std::unique_ptr<Weapon> dropped = Weapon::weaponFactory();
    std::cout << "A new weapon dropped!\n";

    const Weapon* equipped = player_.getWeapon();
    if (equipped == nullptr) {
        player_.setWeapon(std::move(dropped));
    } else {
        equipped->displayStats();
        dropped->displayStats();
        if (*dropped > *equipped) {
            std::cout << "The new weapon is stronger!\n";
        }

        bool decided = false;
        while (!decided) {
            std::cout << "Swap weapon? [y/n]\n";
            std::string answer;
            std::cin >> answer;
            if (answer == "y") {
                player_.setWeapon(std::move(dropped));
                decided = true;
            } else if (answer == "n") {
                decided = true;
            }
        }
    }

    ++currentEnemyIndex_;
    if (currentEnemyIndex_ == enemies_.size()) {
        result_ = GameResult::Win;
    }
}

void Game::combat() {
    if (playerTurn_) {
        std::cout << "What will " << player_.getName() << " do? [attack/heal]\n";
        std::string action;
        std::cin >> action;

        if (action == "attack") {
            player_.attack(enemies_.at(currentEnemyIndex_));
        } else if (action == "heal") {
            player_.restoreHP(7);
        } else {
            std::cout << "Invalid command\n";
            return;  // don't consume the turn
        }
    } else {
        enemies_.at(currentEnemyIndex_).attack(player_);
        if (player_.getHP() <= 0) {
            result_ = GameResult::Lose;
        }
    }

    playerTurn_ = !playerTurn_;
}
