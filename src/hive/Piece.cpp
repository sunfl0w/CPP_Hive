#include "Piece.hpp"

namespace Hive {
    Piece::Piece(PieceType type, Color color) {
        this->type = type;
        this->color = color;
    }

    const PieceType& Piece::GetType() const {
        return type;
    }
    
    const Color& Piece::GetColor() const {
        return color;
    }
}