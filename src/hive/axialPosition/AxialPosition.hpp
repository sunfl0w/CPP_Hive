#pragma once

namespace Hive {
    class AxialPosition {
    public:
        int x, y;

        AxialPosition();
        AxialPosition(int x, int y);

        int GetHashValue();
        std::vector<AxialPosition> GetNeighbouringPositions();
        bool IsAtBorderOfBoard();
    };
}  // namespace Hive