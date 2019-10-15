#pragma once

#include <vector>

#include "AxialPosition.hpp"

namespace Hive {
    class SlidePath {
    private:
        std::vector<AxialPosition> slidePositions;

    public:
        SlidePath(const AxialPosition& positionInPath);
        bool IsValidForPiece(const AxialPosition& piecePosition) const;
        bool ContainsPosition(const AxialPosition& position) const;
    };
}  // namespace Hive