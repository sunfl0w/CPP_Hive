#include "AxialPosition.hpp"

#include <math.h>
#include <vector>

namespace Hive {
    AxialPosition::AxialPosition() {
        this->x = 0;
        this->y = 0;
    }

    AxialPosition::AxialPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool AxialPosition::operator==(const AxialPosition &axialPosition) const {
        if (x == axialPosition.x && y == axialPosition.y) {
            return true;
        } else {
            return false;
        }
    }

    int AxialPosition::GetHashValue() const {
        //int hashValue = (x * 31) + (y * 37);
        int hashValue = (x + 5) << 16 | ((y + 5)&0xFFFF);
        return hashValue;
    }

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositions() {
        std::vector<AxialPosition> neighbouringAxialPositions;

        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x, y - 1));

        if (IsAtBorderOfBoard()) {
            for (int i = 0; i < neighbouringAxialPositions.size(); i++) {
                if (neighbouringAxialPositions[i].x < -5 || neighbouringAxialPositions[i].x > 5 || neighbouringAxialPositions[i].y < -5 || neighbouringAxialPositions[i].y > 5) {
                    neighbouringAxialPositions.erase(neighbouringAxialPositions.begin() + i);
                }
            }
        }

        return neighbouringAxialPositions;
    }

    bool AxialPosition::IsAtBorderOfBoard() {
        int z = 0 - x - y;
        if (std::abs(x) + std::abs(y) + std::abs(z) == 10) {
            return true;
        } else {
            return false;
        }
    }
}  // namespace Hive