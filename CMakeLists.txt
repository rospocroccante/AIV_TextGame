cmake_minimum_required(VERSION 3.15)

project(AIV_TextGame CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(game
    src/main.cpp
    src/game/game.cpp
    src/game/character.cpp
    src/game/enemy.cpp
    src/game/damageable.cpp
    src/game/gameEventManager.cpp
)

target_include_directories(game PRIVATE include)
