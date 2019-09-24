#pragma once

#include <string>
#include <vector>

#include "PlayerColor.hpp"
#include "GamePiece.hpp"

namespace Hive::Player {
    class HivePlayer {
    private:
        std::string playerName;
        PlayerColor playerColor;

        std::vector<Piece::GamePiece> undeplyedGamingPieces;
    public:
        HivePlayer(std::string playerName, PlayerColor playerColor);

    private:
        AddUndeployedGamePieces
    };
}  // namespace Hive::Player