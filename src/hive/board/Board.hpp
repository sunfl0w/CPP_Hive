#pragma once

#include <vector>

#include "GamingPiece.hpp"

namespace Hive {
    class Board {
    private:
        std::vector<Piece::GamingPiece> pieces;

    public:
        Board();

    private:
        void PlaceObstacles();
    };
}  // namespace Hive