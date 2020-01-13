#pragma once
#include <random>
#include <vector>

#include "Logic.hpp"
#include "Move.hpp"

namespace AI {
    class HiveLogic : public Logic {
    public:
        HiveLogic();
        ~HiveLogic();
        Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
    };
}  // namespace AI