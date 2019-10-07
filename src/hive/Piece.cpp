#include "Piece.hpp"

namespace Hive {
    Piece::Piece(PieceType pieceType, PieceColor pieceColor) {
        this->pieceType = pieceType;
        this->pieceColor = pieceColor;
    }

    const PieceType& Piece::GetPieceType() const {
        return pieceType;
    }
    
    const PieceColor& Piece::GetPieceColor() const {
        return pieceColor;
    }

    const PlayerColor Piece::GetCorrespondingPlayerColor() const {
        if(pieceColor == PieceColor::Red) {
            return PlayerColor::Red;
        } else if(pieceColor == PieceColor::Blue) {
            return PlayerColor::Blue;
        } else {
            return PlayerColor::Undefined;
        }
    }
}