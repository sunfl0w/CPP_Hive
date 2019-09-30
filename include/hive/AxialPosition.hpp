#pragma once

#include <vector>

namespace Hive {
    class AxialPosition {
    public:
        int x, y;

        AxialPosition();
        AxialPosition(int x, int y);

        bool operator==(const AxialPosition &axialPosition) const;

        int GetHashValue() const;
        std::vector<AxialPosition> GetNeighbouringPositions() const;
        bool IsAtBorderOfBoard() const;
    };
}  // namespace Hive