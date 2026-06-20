#pragma once

// What a combatant decides to do on its turn.
// target is an index into the living-foe list (only used by Attack).
struct Action {
    enum class Type { Attack, Heal, Pass };

    Type type = Type::Pass;
    int target = -1;
};
