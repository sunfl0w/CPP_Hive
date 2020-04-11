#include "player.hpp"

namespace Hive {
    Player::Player() {
        undeployedPieceCounts = std::vector<int>(5);
    }

    Player::Player(Color color) {
        this->color = color;
        undeployedPieceCounts = std::vector<int>(5);
    }

    Color Player::GetColor() const {
        return color;
    }

    void Player::SetColor(Color color) {
        this->color = color;
    }

    const std::vector<int>& Player::GetUndeployedPieceTypeCounts() const {
        return undeployedPieceCounts;
    }

    void Player::AddUndeployedPieceType(PieceType type) {
        undeployedPieceCounts[static_cast<int>(type)] += 1;
    }

    void Player::RemoveUndeployedPieceType(PieceType type) {
        undeployedPieceCounts[static_cast<int>(type)] -= 1;
    }

    void Player::InitializeUndeployedPieces() {
        AddUndeployedPieceType(PieceType::QueenBee);

        AddUndeployedPieceType(PieceType::Spider);
        AddUndeployedPieceType(PieceType::Spider);

        AddUndeployedPieceType(PieceType::Beetle);
        AddUndeployedPieceType(PieceType::Beetle);

        AddUndeployedPieceType(PieceType::Grasshopper);
        AddUndeployedPieceType(PieceType::Grasshopper);
        AddUndeployedPieceType(PieceType::Grasshopper);

        AddUndeployedPieceType(PieceType::Ant);
        AddUndeployedPieceType(PieceType::Ant);
        AddUndeployedPieceType(PieceType::Ant);
    }
}  // namespace Hive