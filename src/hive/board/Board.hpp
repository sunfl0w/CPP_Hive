#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>

#include "RandomNumberGenerator.hpp"
#include "GamePiece.hpp"
#include "GamePieceStack.hpp"
#include "Move.hpp"
#include "AxialPosition.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, Piece::GamePieceStack> gamePieceStacks;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        void PerformMove(Move& move);

        bool GamePieceStackExistsAtPosition(AxialPosition& coordinate);
        bool GamePieceStackExistsAtPosition(int x, int y);

        Piece::GamePieceStack& GetGamePieceStackAtPosition(AxialPosition& position);
        Piece::GamePieceStack& GetGamePieceStackAtPosition(int x, int y);

        Piece::GamePiece& GetGamePieceAtPositionAndLayer(AxialPosition& position, int layer);
        Piece::GamePiece& GetGamePieceAtPositionAndLayer(int x, int y, int layer);

        std::vector<Piece::GamePieceStack> GetNeighbouringGamePieceStacksAtPosition(AxialPosition& position);

        void AddGamePieceOnTopAtPosition(Piece::GamePiece& gamePiece, AxialPosition& position);
        void RemoveUpmostGamePieceAtPosition(AxialPosition& position);

    private:
        void PlaceObstacles();
    };
}  // namespace Hive