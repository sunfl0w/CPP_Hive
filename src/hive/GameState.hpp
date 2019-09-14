#pragma once

#include <vector>

#include "Move.hpp"

namespace Hive {
    class GameState {
    private:
        int turn;

    public:
        std::vector<Move> GetPossibleMoves();
    };
}  // namespace Hive