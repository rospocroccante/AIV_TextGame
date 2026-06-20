#include <iostream>
#include <string>

#include "game.hpp"

int main() {
    std::cout << "Enter your name:\n";
    std::string playerName;
    std::cin >> playerName;

    Game game(playerName);
    game.init(10);

    while (!game.isGameOver()) {
        game.update();
    }

    std::cout << "Result: " << game.getStatus() << '\n';
    return 0;
}
