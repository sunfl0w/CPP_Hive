#pragma once

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "Player.hpp"
#include "Board.hpp"

namespace Hive {
    class GameState {
    private:
        int turn;
        Board board;
        Player currentPlayer;
        Player pausedPlayer;
        std::vector<Move> performedMoves;

    public:
        GameState();
        GameState(GameState& gameState);

        const Player& GetCurrentPlayer() const;
        const Player& GetPausedPlayer() const;

        std::vector<Move> GetPossibleMoves() const;
        bool IsMoveValid(const Move& move) const;

        std::vector<Move> GetPossibleDeployMoves() const;
        std::vector<Move> GetPossibleDragMoves() const;

        std::vector<Move> GetPossibleQueenBeeDragMoves(const std::vector<SlidePath>& slidePaths) const;
        std::vector<Move> GetPossibleSpiderDragMoves(const std::vector<SlidePath>& slidePaths) const;
        std::vector<Move> GetPossibleBeetleDragMoves() const;
        std::vector<Move> GetPossibleGrasshopperDragMoves() const;
        std::vector<Move> GetPossibleAntDragMoves() const;

        std::vector<AxialPosition> GetBorderPositionsOfHive() const;
    };
}  // namespace Hive