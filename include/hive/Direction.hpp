#pragma once

namespace Hive {
    class Direction {
    public:
        enum DirectionValue {
            UpRight,
            Right,
            DownRight,
            DownLeft,
            Left,
            Upleft,
        };

        Direction(DirectionValue directionValue) : value(directionValue) {}

    private:
        DirectionValue value;
    };
}  // namespace Hive