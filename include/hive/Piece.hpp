#pragma once

#include "Color.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Piece {
    private:
        PieceType type;
        Color color;

    public:
        Piece(PieceType pieceType, Color pieceColor);

        const PieceType& GetType() const;
        const Color& GetColor() const;
    };
}  // namespace Hive::Piece