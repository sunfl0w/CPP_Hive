#pragma once

#include <vector>

#include "FlatPosition.hpp"
#include "GamingPiece.hpp"

namespace Hive::Piece {
    class GamingPieceStack {
    private:
        std::vector<GamingPiece> gamingPieces;
    public:
        GamingPieceStack();

        void AddGamingPieceOnTop(GamingPiece& gamingPiece);
        void RemoveGamingPieceOnTop();
        GamingPiece& GetGamingPieceOnTop();
        std::vector<GamingPiece>& GetGamingPieces();
    };
}  // namespace Hive::GamingPiece