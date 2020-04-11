#include "neighbourMap.hpp"

namespace Hive {
    NeighbourMap::NeighbourMap() {
        neighbourMap = std::vector<std::vector<AxialPosition>>();
        for (int i = 0; i < 11; i++) {
            for (int l = 0; l < 11; l++) {
                neighbourMap.push_back(std::vector<AxialPosition>());
            }
        }

        for (int x = -5; x < 6; x++) {
            for (int y = -5; y < 6; y++) {
                AxialPosition pos(x, y);
                neighbourMap[(x + 5) * 11 + (y + 5)] = pos.GetNeighbouringPositions();
            }
        }
    }

    std::vector<AxialPosition*> NeighbourMap::GetNeighbouringPositions(const AxialPosition& position) {
        std::vector<AxialPosition*> neighbouringPositions;
        neighbouringPositions.reserve(6);
        int maxNeighbours = neighbourMap[position.GetID()].size();
        for (int i = 0; i < maxNeighbours; i++) {
            neighbouringPositions.push_back(&neighbourMap[position.GetID()][i]);
        }
        return neighbouringPositions;
    }

    std::vector<AxialPosition>& NeighbourMap::GetNeighbouringPositionsRef(const AxialPosition& position) {
        return neighbourMap[position.GetID()];
    }
}  // namespace Hive