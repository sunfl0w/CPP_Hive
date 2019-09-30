#pragma once

#include "PieceColor.hpp"
#include "PieceType.hpp"
#include "PlayerColor.hpp"

namespace Hive::Piece {
    class GamePiece {
    private:
        PieceType pieceType;
        PieceColor pieceColor;

    public:
        GamePiece(PieceType pieceType, PieceColor pieceColor);

        const PieceType& GetPieceType() const;
        const PieceColor& GetPieceColor() const;
        const Player::PlayerColor GetCorrespondingPlayerColor() const;
    };
}  // namespace Hive::Piece