#include "AxialPosition.hpp"

namespace Hive {
    AxialPosition::AxialPosition() {}

    AxialPosition::AxialPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    int AxialPosition::GetHashValue() {
        int hashValue = (x * 31) + (y * 37);
        return hashValue;
    }
}