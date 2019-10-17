#pragma once

#include <vector>
#include <deque>

#include "AxialPosition.hpp"

namespace Hive {
    class SlidePath {
    private:
        std::deque<AxialPosition> slidePositions;

    public:
        SlidePath(const AxialPosition& positionInPath, const Board& board);
        bool IsValidForPiece(const AxialPosition& piecePosition) const;
        bool ContainsPosition(const AxialPosition& position) const;
        const std::deque<AxialPosition>& GetContainingPositions() const;
    
    private:
        std::vector<AxialPosition> GetAccesibleNeighbouringPositionsAtBorderOfHive(const AxialPosition& position, const Board& board) const;
    };
}  // namespace Hive