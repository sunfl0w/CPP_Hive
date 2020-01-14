#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "gameState.hpp"
#include "Move.hpp"
#include "Player.hpp"
#include "Color.hpp"

namespace AI {
    class Logic {
    public:
        Logic();
        virtual ~Logic();
        virtual Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
    };
} // namespace Piranhas::Logic