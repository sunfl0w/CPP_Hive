#pragma once

namespace Hive {
    class Coordinate {
    private:
        int x, y;
        int layer;

    public:
        Coordinate();
        Coordinate(int x, int y, int layer);
    };
}  // namespace Hive