#include "Player.hpp"

namespace Hive {
    Player::Player(PlayerColor playerColor) {
        this->playerColor = playerColor;
        this->undeployedGamingPieces = std::vector<Piece>();
        InitializeUndeployedGamePieces();
    }

    const PlayerColor& Player::GetPlayerColor() const {
        return playerColor;
    }

    PieceColor Player::GetPieceColorFromPlayerColor() {
        if(playerColor == PlayerColor::Red) {
            return PieceColor::Red;
        } else {
            return PieceColor::Blue;
        }
    }

    const std::vector<Piece>& Player::GetUndeployedGamePieces() const {
        return undeployedGamingPieces;
    }

    void Player::InitializeUndeployedGamePieces() {
        undeployedGamingPieces.push_back(Piece(PieceType::QueenBee, GetPieceColorFromPlayerColor()));

        undeployedGamingPieces.push_back(Piece(PieceType::Spider, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Spider, GetPieceColorFromPlayerColor()));

        undeployedGamingPieces.push_back(Piece(PieceType::Beetle, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Beetle, GetPieceColorFromPlayerColor()));

        undeployedGamingPieces.push_back(Piece(PieceType::Grasshopper, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Grasshopper, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Grasshopper, GetPieceColorFromPlayerColor()));

        undeployedGamingPieces.push_back(Piece(PieceType::Ant, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Ant, GetPieceColorFromPlayerColor()));
        undeployedGamingPieces.push_back(Piece(PieceType::Ant, GetPieceColorFromPlayerColor()));
    }
}  // namespace Hive