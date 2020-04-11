#include "axialPosition.hpp"

#include <math.h>

#include <vector>

namespace Hive {
    AxialPosition::AxialPosition() {
        id = -1;
    }

    AxialPosition::AxialPosition(const AxialPosition& axialPosition) {
        id = axialPosition.id;
    }

    AxialPosition::AxialPosition(int x, int y) {
        id = (x + 5) * 11 + (y + 5);
    }

    AxialPosition::AxialPosition(unsigned int id) {
        this->id = id;
    }

    bool AxialPosition::operator==(const AxialPosition& axialPosition) const {
        return id == axialPosition.id;
    }

    bool AxialPosition::operator!=(const AxialPosition& axialPosition) const {
        return id != axialPosition.id;
    }

    int AxialPosition::GetX() const {
        return id / 11 - 5;
    }

    int AxialPosition::GetY() const {
        return id % 11 - 5;
    }

    int AxialPosition::GetZ() const {
        return 0 - GetX() - GetY();
    }

    unsigned int AxialPosition::GetID() const {
        return id;
    }

    int AxialPosition::GetDistanceTo(const AxialPosition& otherPosition) const {
        return (std::abs(GetX() - otherPosition.GetX()) + std::abs(GetY() - otherPosition.GetY()) + std::abs(0 - GetX() - GetY() + 0 + otherPosition.GetX() + otherPosition.GetY())) >> 1;
    }

    bool AxialPosition::IsNeighbourTo(const AxialPosition& otherPosition) const {
        return GetDistanceTo(otherPosition) == 1;
    }

    AxialPosition AxialPosition::Add(const AxialPosition& otherPosition) const {
        return AxialPosition(GetX() + otherPosition.GetX(), GetY() + otherPosition.GetY());
    }

    AxialPosition AxialPosition::Subtract(const AxialPosition& otherPosition) const {
        return AxialPosition(GetX() - otherPosition.GetX(), GetY() - otherPosition.GetY());
    }

    std::vector<AxialPosition> AxialPosition::GetNeighbouringPositions() const {
        std::vector<AxialPosition> neighbouringAxialPositions = std::vector<AxialPosition>();
        neighbouringAxialPositions.reserve(6);
        int x = GetX();
        int y = GetY();
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
        int x = GetX();
        int y = GetY();
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x + 1, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y - 1));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y));
        neighbouringAxialPositions.push_back(AxialPosition(x - 1, y + 1));
        neighbouringAxialPositions.push_back(AxialPosition(x, y + 1));

        return neighbouringAxialPositions;
    }

    bool AxialPosition::IsAtBorderOfBoard() const {
        return std::abs(GetX()) + std::abs(GetY()) + std::abs(0 - GetX() - GetY()) == 10;
    }

    bool AxialPosition::IsOnBoard() const {
        return std::abs(GetX()) + std::abs(GetY()) + std::abs(0 - GetX() - GetY()) <= 10;
    }

    AxialPosition AxialPosition::GetTranslationToOtherPosition(const AxialPosition& otherPosition) const {
        return otherPosition.Subtract(*this);
    }
}  // namespace Hive