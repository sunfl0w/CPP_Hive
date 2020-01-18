#pragma once

#include "Color.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Piece {
    private:
        PieceType type;
        Color color;

    public:
        Piece();
        Piece(const Piece& piece);
        Piece(const PieceType& pieceType, const Color& pieceColor);

        PieceType GetType() const;
        void SetType(PieceType pieceType);
        Color GetColor() const;
    };
}  // namespace Hive::Piece