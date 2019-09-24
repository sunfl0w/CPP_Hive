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

    private:
        void InitializeUndeployedGamePieces();
    };
}  // namespace Hive::Player