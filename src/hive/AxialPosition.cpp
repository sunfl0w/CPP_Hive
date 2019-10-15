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

    int AxialPosition::GetDistanceTo(const AxialPosition& otherPosition) const {
        int z = 0 - x - y;
        int zOther = 0 - otherPosition.x - otherPosition.y;
        return (std::abs(x - otherPosition.x) + std::abs(y - otherPosition.y) + std::abs(z - zOther)) / 2;
    }

    bool AxialPosition::IsNeighbourTo(const AxialPosition& otherPosition) const {
        if(GetDistanceTo(otherPosition) == 1) {
            return true;
        } else {
            return false;
        }
    }

    AxialPosition AxialPosition::Subtract(const AxialPosition& otherPosition) const {
        //int z = 0 - x - y;
        //int zOther = 0 - otherPosition.x - otherPosition.y;
        AxialPosition result = AxialPosition(x - otherPosition.x, y - otherPosition.y);
        return result;
    }

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositions() const {
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

    bool AxialPosition::IsAtBorderOfBoard() const {
        int z = 0 - x - y;
        if (std::abs(x) + std::abs(y) + std::abs(z) == 10) {
            return true;
        } else {
            return false;
        }
    }
}  // namespace Hive