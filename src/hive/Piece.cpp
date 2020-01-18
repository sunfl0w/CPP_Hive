#include "Piece.hpp"

namespace Hive {
    Piece::Piece() {}

    Piece::Piece(const Piece& piece) {
        this->type = piece.type;
        this->color = piece.color;
    }
    
    Piece::Piece(const PieceType& type, const Color& color) {
        this->type = type;
        this->color = color;
    }

    PieceType Piece::GetType() const {
        return type;
    }

    void Piece::SetType(PieceType pieceType) {
        type = pieceType;
    }
    
    Color Piece::GetColor() const {
        return color;
    }
}