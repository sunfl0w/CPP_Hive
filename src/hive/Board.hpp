#pragma once

#include <vector>

#include "GamingPiece.hpp"

namespace Hive {
    class Board {
        std::vector<Piece::GamingPiece> pieces;
    };
}