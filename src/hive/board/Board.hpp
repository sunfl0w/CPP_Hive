#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>

#include "RandomNumberGenerator.hpp"
#include "GamingPiece.hpp"
#include "GamingPieceStack.hpp"
#include "Move.hpp"
#include "AxialPosition.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, Piece::GamingPieceStack> gamingPieceStacks;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        void PerformMove(Move& move);

        bool GamingPieceStackExistsAtPosition(AxialPosition& coordinate);
        bool GamingPieceStackExistsAtPosition(int x, int y);

        Piece::GamingPieceStack& GetGamingPieceStackAtPosition(AxialPosition& position);
        Piece::GamingPieceStack& GetGamingPieceStackAtPosition(int x, int y);

        Piece::GamingPiece& GetGamingPieceAtPositionAndLayer(AxialPosition& position, int layer);
        Piece::GamingPiece& GetGamingPieceAtPositionAndLayer(int x, int y, int layer);

        std::vector<Piece::GamingPieceStack> GetNeighbouringGamingPieceStacksAtPosition(AxialPosition& position);

        void AddGamingPieceOnTopAtPosition(Piece::GamingPiece& gamingPiece, AxialPosition& position);
        void RemoveUpmostGamingPieceAtPosition(AxialPosition& position);

    private:
        void PlaceObstacles();
    };
}  // namespace Hive