#pragma once

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "SlidePathNode.hpp"

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

        Board& GetBoard();

        Player& GetCurrentPlayer();
        Player& GetPausedPlayer();

        std::vector<Move> GetPossibleMoves();
        bool IsMoveValid(const Move& move) const;

        std::vector<Move> GetPossibleDeployMoves() const;
        std::vector<Move> GetPossibleQueenBeeDeployMoves() const;

        std::vector<Move> GetPossibleDragMoves();
        std::vector<Move> GetPossibleQueenBeeDragMoves() const;
        std::vector<Move> GetPossibleSpiderDragMoves();
        std::vector<Move> GetPossibleBeetleDragMoves() const;
        std::vector<Move> GetPossibleGrasshopperDragMoves() const;
        std::vector<Move> GetPossibleAntDragMoves();

        std::vector<AxialPosition> GetBorderPositionsOfHive() const;

    private:
        std::vector<AxialPosition> GetDeployablePositions() const;
    };
}  // namespace Hive