#include "player.hpp"

namespace Hive {
    Player::Player() {
        undeployedPieces = std::vector<Piece>();
    }

    Player::Player(Color color) {
        this->color = color;
        undeployedPieces = std::vector<Piece>();
    }

    Color Player::GetColor() const {
        return color;
    }

    void Player::SetColor(Color color) {
        this->color = color;
    }

    const std::vector<Piece>& Player::GetUndeployedPieces() const {
        return undeployedPieces;
    }

    void Player::AddUndeployedPiece(Piece piece) {
        undeployedPieces.push_back(piece);
    }

    void Player::RemoveUndeployedPiece(PieceType type) {
        for(int i = 0; i < undeployedPieces.size(); i++) {
            if(undeployedPieces[i].GetType() == type) {
                undeployedPieces.erase(undeployedPieces.begin() + i);
            }
        }
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