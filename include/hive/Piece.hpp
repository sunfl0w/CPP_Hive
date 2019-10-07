#pragma once

#include "PieceColor.hpp"
#include "PieceType.hpp"
#include "PlayerColor.hpp"

namespace Hive {
    class Piece {
    private:
        PieceType pieceType;
        PieceColor pieceColor;

    public:
        Piece(PieceType pieceType, PieceColor pieceColor);

        const PieceType& GetPieceType() const;
        const PieceColor& GetPieceColor() const;
        const PlayerColor GetCorrespondingPlayerColor() const;
    };
}  // namespace Hive::Piece