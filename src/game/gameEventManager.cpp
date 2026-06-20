#include "gameEventManager.hpp"

#include <utility>

static std::vector<OnCharacterDie> g_dieCallbacks;

void GameEventManager::subscribeDieEvent(OnCharacterDie callback) {
    g_dieCallbacks.push_back(std::move(callback));
}

void GameEventManager::notifyCharacterDie() {
    for (const auto& callback : g_dieCallbacks) {
        callback();
    }
}
