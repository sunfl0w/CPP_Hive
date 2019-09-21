#pragma once

#include <vector>

#include "GamingPiece.hpp"

namespace Hive::Piece {
    class GamingPieceStack {
    private:
        std::vector<GamingPiece> gamingPieces;
    public:
        GamingPieceStack();

        void AddGamingPieceOnTop(GamingPiece& gamingPiece);
        void RemoveGamingPieceOnTop();
        GamingPiece& GetGamingPieceByLayer(int layer);
        GamingPiece& GetGamingPieceOnTop();
        std::vector<GamingPiece>& GetGamingPieces();
    };
}  // namespace Hive::GamingPiece