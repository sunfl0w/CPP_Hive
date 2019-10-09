#pragma once

#include <vector>

#include "AxialPosition.hpp"

namespace Hive {
    class SlidePath {
    private:
        std::vector<AxialPosition> slidePositions;

    public:
        SlidePath();
        bool IsValidForPiece(const AxialPosition& piecePosition, const Board& board) const;

    };
}  // namespace Hive