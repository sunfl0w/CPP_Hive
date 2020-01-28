#pragma once

#include <algorithm>
#include <vector>

#include "board.hpp"
#include "move.hpp"
#include "player.hpp"

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
        GameState(const GameState& gameState);

        unsigned int GetTurn() const;
        void SetTurn(unsigned int turn);

        Move& GetLastPerformedMove();

        Board& GetBoard();

        Player& GetPlayer(Color color);
        Player& GetCurrentPlayer();
        void SetCurrentPlayer(Player player);
        Player& GetPausedPlayer();
        void SetPausedPlayer(Player player);

        std::vector<Move> GetPossibleMoves();
        void PerformMove(const Move& move);

        std::vector<Move> GetPossibleDeployMoves();
        std::vector<Move> GetPossibleQueenBeeDeployMoves();

        std::vector<Move> GetPossibleDragMoves();
        std::vector<Move> GetPossibleQueenBeeDragMoves();
        std::vector<Move> GetPossibleSpiderDragMoves();
        std::vector<Move> GetPossibleBeetleDragMoves();
        std::vector<Move> GetPossibleGrasshopperDragMoves();
        std::vector<Move> GetPossibleAntDragMoves();

        bool IsGameOver();

    private:
        std::vector<AxialPosition> GetDeployablePositions();
        bool IsQueenBeeBlocked(Color color);
    };
}  // namespace Hive