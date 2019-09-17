#pragma once

#include <vector>
#include <unordered_map>

#include "GamingPiece.hpp"
#include "Move.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, Piece::GamingPiece> gamingPieces;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        void PerformMove(Move& move);

        bool GamingPeaceExistsAtCoordinate(int x, int y, int layer);
        bool GamingPeaceExistsAtCoordinate(Coordinate& coordinate);

        Piece::GamingPiece& GetGamingPieceAtCoordinate(int x, int y, int layer);
        Piece::GamingPiece& GetGamingPieceAtCoordinate(Coordinate& coordinate);

        std::vector<Piece::GamingPiece> GetNeighbouringGamingPiecesAtCoordinate(Coordinate& coordinate);
        void AddGamingPiece(Piece::GamingPiece& gamingPiece);

    private:
        void PlaceObstacles();
    };
}  // namespace Hive