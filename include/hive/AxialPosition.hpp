#pragma once

#include <vector>

namespace Hive {
    class AxialPosition {
    public:
        int x, y;

        AxialPosition();
        AxialPosition(const AxialPosition &axialPosition);
        AxialPosition(int x, int y);

        bool operator==(const AxialPosition &axialPosition) const;
        bool operator!=(const AxialPosition &axialPosition) const;

        int GetHashValue() const;
        int GetZCoordinate() const;
        int GetDistanceTo(const AxialPosition& otherPosition) const;
        bool IsNeighbourTo(const AxialPosition& otherPosition) const;
        AxialPosition Add(const AxialPosition& otherPosition) const;
        AxialPosition Subtract(const AxialPosition& otherPosition) const;
        std::vector<AxialPosition> GetNeighbouringPositions() const;
        std::vector<AxialPosition> GetNeighbouringPositionsIncludingOutsideBoardPositions() const;
        bool IsAtBorderOfBoard() const;
        bool IsOnBoard() const;
        AxialPosition GetTranslationToOtherPosition(const AxialPosition& otherPosition) const;
    };
}  // namespace Hive