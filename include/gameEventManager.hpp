#pragma once

#include <functional>
#include <vector>

using OnCharacterDie = std::function<void()>;

class GameEventManager {
public:
    GameEventManager() = delete;

    static void subscribeDieEvent(OnCharacterDie callback);
    static void notifyCharacterDie();
};
