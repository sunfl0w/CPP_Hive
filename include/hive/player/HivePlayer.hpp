#pragma once

#include <vector>

#include "PlayerColor.hpp"
#include "GamePiece.hpp"

namespace Hive::Player {
    class HivePlayer {
    private:
        PlayerColor playerColor;

        std::vector<Piece::GamePiece> undeployedGamingPieces;
    public:
        HivePlayer(PlayerColor playerColor);

        Piece::PieceColor GetPieceColorFromPlayerColor();
        const std::vector<Piece::GamePiece>& GetUndeployedGamePieces() const;

    private:
        void InitializeUndeployedGamePieces();
    };
}  // namespace Hive::Player