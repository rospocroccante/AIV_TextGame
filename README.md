# AIV TextGame

A small turn-based RPG in C++: lead a party against a horde of enemies. Ranged
weapons run on limited ammo, fighters get enraged at low HP, and the AI focus-fires
the weakest target. The fight is driven by a small state-machine combat loop.

## Demo

![party vs horde](demo/aiv_textgame_v2.gif)

### Before — the original 1v1 version

![original 1v1](demo/aiv_textgame.gif)

## Run

```bash
cmake -S . -B build && cmake --build build
./build/game
```
