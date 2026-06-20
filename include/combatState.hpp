#pragma once

#include <memory>

class Battle;

// State pattern: each phase of a round is a state. run() performs the phase and
// returns the next state to enter; returning nullptr ends the battle.
class CombatState {
public:
    virtual ~CombatState() = default;

    virtual std::unique_ptr<CombatState> run(Battle& battle) = 0;
    virtual const char* name() const = 0;
};

class PartyTurnState : public CombatState {
public:
    std::unique_ptr<CombatState> run(Battle& battle) override;
    const char* name() const override { return "PartyTurn"; }
};

class HordeTurnState : public CombatState {
public:
    std::unique_ptr<CombatState> run(Battle& battle) override;
    const char* name() const override { return "HordeTurn"; }
};

class VictoryState : public CombatState {
public:
    std::unique_ptr<CombatState> run(Battle& battle) override;
    const char* name() const override { return "Victory"; }
};

class DefeatState : public CombatState {
public:
    std::unique_ptr<CombatState> run(Battle& battle) override;
    const char* name() const override { return "Defeat"; }
};
