#include "AxialPosition.hpp"

#include <math.h>
#include <vector>

namespace Hive {
    AxialPosition::AxialPosition() {
        this->x = 0;
        this->y = 0;
    }

    AxialPosition::AxialPosition(const AxialPosition &axialPosition) {
        this->x = axialPosition.x;
        this->y = axialPosition.y;
    }

    AxialPosition::AxialPosition(int x, int y) {
        this->x = x;
        this->y = y;
    }

    bool AxialPosition::operator==(const AxialPosition& axialPosition) const {
        return !(x != axialPosition.x || y != axialPosition.y);
    }

    bool AxialPosition::operator!=(const AxialPosition& axialPosition) const {
        return x != axialPosition.x || y != axialPosition.y;
    }

    int AxialPosition::GetHashValue() const {
        int hashValue = (x * 31) + (y * 37); //<== Note to myself: Is slow but reliable
        //int hashValue = (x + 5) << 16 | ((y + 5) & 0xFFFF);
        //int hashValue = ((x * 0x1f1f1f1f) ^ y);
        //int hashValue = ((y << 16) ^ x);
        //int hashValue = x | (y << 15);
        return hashValue;
    }

    int AxialPosition::GetZCoordinate() const {
        return 0 - x - y;
    }

    int AxialPosition::GetDistanceTo(const AxialPosition& otherPosition) const {
        //int z = 0 - x - y;
        //int zOther = 0 - otherPosition.x - otherPosition.y;
        return (std::abs(x - otherPosition.x) + std::abs(y - otherPosition.y) + std::abs(0 - x - y + 0 + otherPosition.x + otherPosition.y)) >> 1;
    }

    bool AxialPosition::IsNeighbourTo(const AxialPosition& otherPosition) const {
        return GetDistanceTo(otherPosition) == 1;
    }

    AxialPosition AxialPosition::Add(const AxialPosition& otherPosition) const {
        return AxialPosition(x + otherPosition.x, y + otherPosition.y);
    }

    AxialPosition AxialPosition::Subtract(const AxialPosition& otherPosition) const {
        return AxialPosition(x - otherPosition.x, y - otherPosition.y);
    }

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositions() const {
        std::vector<AxialPosition> neighbouringAxialPositions = std::vector<AxialPosition>();
        neighbouringAxialPositions.reserve(6);

        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y + 1));

        for (int i = neighbouringAxialPositions.size() - 1; i >= 0; i--) {
            if (!neighbouringAxialPositions[i].IsOnBoard()) {
                neighbouringAxialPositions.erase(neighbouringAxialPositions.begin() + i);
            }
        }
        return neighbouringAxialPositions;
    }

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositionsIncludingOutsideBoardPositions() const {
         std::vector<AxialPosition> neighbouringAxialPositions = std::vector<AxialPosition>();

        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y + 1));

        return neighbouringAxialPositions;
    }

    bool AxialPosition::IsAtBorderOfBoard() const {
        return std::abs(x) + std::abs(y) + std::abs(0 - x - y) == 10;
    }

    bool AxialPosition::IsOnBoard() const {
        return std::abs(x) + std::abs(y) + std::abs(0 - x - y) <= 10;
    }

    AxialPosition AxialPosition::GetTranslationToOtherPosition(const AxialPosition& otherPosition) const {
        return otherPosition.Subtract(*this);
    }
}  // namespace Hive