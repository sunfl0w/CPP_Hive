#include "GamePiece.hpp"

namespace Hive::Piece {
    GamePiece::GamePiece(PieceType pieceType, PieceColor pieceColor) {
        this->pieceType = pieceType;
        this->pieceColor = pieceColor;
    }
}