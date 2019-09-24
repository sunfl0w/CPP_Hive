#pragma once

#include <vector>

#include "HiveMove.hpp"
#include "HivePlayer.hpp"
#include "Board.hpp"

namespace Hive {
    class GameState {
    private:
        int turn;
        Board board;
        Player::HivePlayer currentPlayer;
        Player::HivePlayer pausedPlayer;
        std::vector<Move::HiveMove> performedMoves;

    public:
        GameState();
        GameState(GameState& gameState);

        const Player::HivePlayer& GetCurrentPlayer() const;
        const Player::HivePlayer& GetPausedPlayer() const;

        std::vector<Move::HiveMove> GetPossibleMoves() const;
        bool IsMoveValid(const Move::HiveMove& move) const;

        std::vector<Move::HiveMove> GetPossibleDeployMoves() const;
        std::vector<Move::HiveMove> GetPossibleDragMoves() const;

        std::vector<Move::HiveMove> GetPossibleQueenBeeDragMoves() const;
        std::vector<Move::HiveMove> GetPossibleSpiderDragMoves() const;
        std::vector<Move::HiveMove> GetPossibleBeetleDragMoves() const;
        std::vector<Move::HiveMove> GetPossibleGrasshopperDragMoves() const;
        std::vector<Move::HiveMove> GetPossibleAntDragMoves() const;

        std::vector<AxialPosition> GetBorderPositionsOfHive() const;
    };
}  // namespace Hive