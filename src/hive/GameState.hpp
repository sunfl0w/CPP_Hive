#pragma once

#include <vector>

#include "Move.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace Hive {
    class GameState {
    private:
        int turn;
        Player startingPlayer;
        Player currentPlayer;
        Board board;
        std::vector<Move> performedMoves;

    public:
        GameState();
        GameState(GameState& gameState);

        Player& GetCurrentPlayer();
        Player& GetPausedPlayer();

        std::vector<Move> GetPossibleMoves();
    };
}  // namespace Hive