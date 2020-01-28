#pragma once
#include <random>
#include <vector>

#include "logic.hpp"
#include "move.hpp"

namespace AI {
    class HiveLogic : public Logic {
    public:
        HiveLogic();
        ~HiveLogic();
        Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
        void OnGameEnd(Hive::Color colorOfWinningPlayer);
    };
}  // namespace AI