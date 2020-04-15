#include "axialPosition.hpp"

#include <math.h>

#include <vector>

namespace Hive {
    AxialPosition::AxialPosition() {
        id = -1;
    }

    AxialPosition::AxialPosition(const AxialPosition& axialPosition) {
        x = axialPosition.x;
        y = axialPosition.y;
        id = axialPosition.id;
    }

    AxialPosition::AxialPosition(int x, int y) {
        this->x = x;
        this->y = y;
        id = (x + 5) * 11 + (y + 5);
    }

    bool AxialPosition::operator==(const AxialPosition& axialPosition) const {
        return id == axialPosition.id;
    }

    bool AxialPosition::operator!=(const AxialPosition& axialPosition) const {
        return id != axialPosition.id;
    }

    int AxialPosition::GetX() const {
        return x;
    }

    int AxialPosition::GetY() const {
        return y;
    }

    int AxialPosition::GetZ() const {
        return 0 - x - y;
    }

    unsigned int AxialPosition::GetID() const {
        return id;
    }

    int AxialPosition::GetDistanceTo(const AxialPosition& otherPosition) const {
        return (std::abs(x - otherPosition.x) + std::abs(y - otherPosition.y) + std::abs(0 - x - y + 0 + otherPosition.y + otherPosition.y)) >> 1;
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