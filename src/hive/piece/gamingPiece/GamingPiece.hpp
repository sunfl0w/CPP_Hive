#pragma once

#include "PieceColor.hpp"
#include "PieceType.hpp"

namespace Hive::Piece {
    class GamingPiece {
    private:
        PieceType peiceType;
        PieceColor pieceColor;

    public:
        GamingPiece(PieceType pieceType, PieceColor pieceColor);
    };
}  // namespace Hive::Piece