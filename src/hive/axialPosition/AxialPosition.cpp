#include "AxialPosition.hpp"

#include <vector>
#include <math.h>

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

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositions() {
        std::vector<AxialPosition> neighbouringAxialPositions;

        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x, y - 1));

        if(IsAtBorderOfBoard()) {
            for(int i = 0; i < neighbouringAxialPositions.size(); i++) {
                if(neighbouringAxialPositions[i].x < -5 || neighbouringAxialPositions[i].x > 5 || neighbouringAxialPositions[i].y < -5 || neighbouringAxialPositions[i].y > 5) {
                    neighbouringAxialPositions.erase(neighbouringAxialPositions.begin() + i);
                }
            }
        }

        return neighbouringAxialPositions;
    }

    bool AxialPosition::IsAtBorderOfBoard() {
        int z = 0 - x - y;
        if(std::abs(x) + std::abs(y) + std::abs(z) == 10) {
            return true;
        } else {
            return false;
        }
    }
}