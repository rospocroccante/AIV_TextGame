#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "character.hpp"
#include "enemy.hpp"

enum class GameResult { Ongoing, Win, Lose };

class Game {
public:
    explicit Game(const std::string& playerName)
        : player_(playerName, 20, 5) {}

    void init(int enemyCount);

    bool isGameOver() const { return result_ != GameResult::Ongoing; }
    std::string getStatus() const;

    void update();

private:
    void combat();

    std::vector<Enemy> enemies_;
    Character player_;
    std::size_t currentEnemyIndex_ = 0;
    GameResult result_ = GameResult::Ongoing;
    bool playerTurn_ = true;
};
