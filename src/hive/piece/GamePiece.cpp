#include "GamePiece.hpp"

namespace Hive::Piece {
    GamePiece::GamePiece(PieceType pieceType, PieceColor pieceColor) {
        this->pieceType = pieceType;
        this->pieceColor = pieceColor;
    }

    const PieceType& GamePiece::GetPieceType() const {
        return pieceType;
    }
    
    const PieceColor& GamePiece::GetPieceColor() const {
        return pieceColor;
    }

    const Player::PlayerColor GamePiece::GetCorrespondingPlayerColor() const {
        if(pieceColor == PieceColor::Red) {
            return Player::PlayerColor::Red;
        } else if(pieceColor == PieceColor::Blue) {
            return Player::PlayerColor::Blue;
        } else {
            return Player::PlayerColor::Undefined;
        }
    }
}