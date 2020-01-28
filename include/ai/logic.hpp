#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "gameState.hpp"
#include "move.hpp"
#include "player.hpp"
#include "color.hpp"

namespace AI {
    class Logic {
    public:
        Logic();
        virtual ~Logic();
        virtual Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
        virtual void OnGameEnd(Hive::Color colorOfWinningPlayer);
    };
} // namespace Piranhas::Logic