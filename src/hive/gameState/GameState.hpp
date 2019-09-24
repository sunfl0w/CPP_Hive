#pragma once

#include <vector>

#include "Move.hpp"
#include "HivePlayer.hpp"
#include "Board.hpp"

namespace Hive {
    class GameState {
    private:
        int turn;
        Board board;
        Player::HivePlayer currentPlayer;
        Player::HivePlayer pausedPlayer;
        std::vector<Move> performedMoves;

    public:
        GameState();
        GameState(GameState& gameState);

        const Player::HivePlayer& GetCurrentPlayer() const;
        const Player::HivePlayer& GetPausedPlayer() const;

        const std::vector<Move> GetPossibleMoves() const;
        const bool IsMoveValid(const Move& move) const;

    private:
        const std::vector<Move> GetPossibleDeployMoves() const;
        const std::vector<Move> GetPossibleDragMoves() const;

        const std::vector<Move> GetPossibleQueenBeeDragMoves() const;
        const std::vector<Move> GetPossibleSpiderDragMoves() const;
        const std::vector<Move> GetPossibleBeetleDragMoves() const;
        const std::vector<Move> GetPossibleGrasshopperDragMoves() const;
        const std::vector<Move> GetPossibleAntDragMoves() const;

        const std::vector<AxialPosition> GetBorderPositionsOfHive() const;
    };
}  // namespace Hive