#pragma once

#include <vector>

#include "gameState.hpp"
#include "Move.hpp"
#include "Player.hpp"
#include "Color.hpp"

namespace AI {
    class HiveLogic {
    protected:

    public:
        HiveLogic();
        Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
    };
} // namespace Piranhas::Logic