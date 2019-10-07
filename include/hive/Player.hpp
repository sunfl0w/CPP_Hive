#pragma once

#include <vector>

#include "PlayerColor.hpp"
#include "Piece.hpp"

namespace Hive {
    class Player {
    private:
        PlayerColor playerColor;

        std::vector<Piece::Piece> undeployedGamingPieces;
    public:
        Player(PlayerColor playerColor);

        const PlayerColor& GetPlayerColor() const;

        PieceColor GetPieceColorFromPlayerColor();
        const std::vector<Piece>& GetUndeployedGamePieces() const;

    private:
        void InitializeUndeployedGamePieces();
    };
}  // namespace Hive::Player