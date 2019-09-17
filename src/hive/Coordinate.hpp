#pragma once

#include <vector>

namespace Hive {
    class Coordinate {
    private:
    public:
        int x, y;
        int layer;

        Coordinate();
        Coordinate(int x, int y, int layer);
        int ToHash();
        std::vector<Coordinate> GetNeighbouringCoordinates_ZeroLayer();
        bool IsAtBoarderOfBoard();
    };
}  // namespace Hive