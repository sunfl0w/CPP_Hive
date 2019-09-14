#pragma once

#include "Coordinate.hpp"
#include "PlayerColor.hpp"

namespace Hive::Piece {
    class GamingPiece {
    private:
        Coordinate coordinate;
        PlayerColor playerColor;
    };
}  // namespace Hive::Piece