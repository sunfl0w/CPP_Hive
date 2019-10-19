#include "Player.hpp"

namespace Hive {
    Player::Player(Color color) {
        this->color = color;
        this->undeployedPieces = std::vector<Piece>();
        InitializeUndeployedPieces();
    }

    const Color& Player::GetColor() const {
        return color;
    }

    const std::vector<Piece>& Player::GetUndeployedPieces() const {
        return undeployedPieces;
    }

    void Player::InitializeUndeployedPieces() {
        undeployedPieces.push_back(Piece(PieceType::QueenBee, color));

        undeployedPieces.push_back(Piece(PieceType::Spider, color));
        undeployedPieces.push_back(Piece(PieceType::Spider, color));

        undeployedPieces.push_back(Piece(PieceType::Beetle, color));
        undeployedPieces.push_back(Piece(PieceType::Beetle, color));

        undeployedPieces.push_back(Piece(PieceType::Grasshopper, color));
        undeployedPieces.push_back(Piece(PieceType::Grasshopper, color));
        undeployedPieces.push_back(Piece(PieceType::Grasshopper, color));

        undeployedPieces.push_back(Piece(PieceType::Ant, color));
        undeployedPieces.push_back(Piece(PieceType::Ant, color));
        undeployedPieces.push_back(Piece(PieceType::Ant, color));
    }
}  // namespace Hive