#pragma once

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "Player.hpp"
#include "board.hpp"
#include "SlidePathNode.hpp"

namespace Hive {
    class GameState {
    private:
        unsigned int turn;
        Board board;
        Player currentPlayer;
        Player pausedPlayer;
        std::vector<Move> performedMoves;

    public:
        GameState();
        GameState(GameState& gameState);

        unsigned int GetTurn() const;
        void SetTurn(unsigned int turn);

        Board& GetBoard();

        Player& GetPlayer(Color color);
        Player& GetCurrentPlayer();
        void SetCurrentPlayer(Player player);
        Player& GetPausedPlayer();
        void SetPausedPlayer(Player player);

        std::vector<Move> GetPossibleMoves();
        void PerformMove(const Move& move);

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