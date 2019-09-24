#pragma once

#include "PieceColor.hpp"
#include "PieceType.hpp"

namespace Hive::Piece {
    class GamePiece {
    private:
        PieceType pieceType;
        PieceColor pieceColor;

    public:
        GamePiece(PieceType pieceType, PieceColor pieceColor);
    };
}  // namespace Hive::Piece