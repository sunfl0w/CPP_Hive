#pragma once

#include <vector>

#include "AxialPosition.hpp"

namespace Hive {
    class NeighbourMap {
    private:
        std::vector<std::vector<AxialPosition>> neighbourMap;
    public:
        NeighbourMap();
        std::vector<AxialPosition*> GetNeighbouringPositions(const AxialPosition& position);
        std::vector<AxialPosition>& GetNeighbouringPositionsRef(const AxialPosition& position);
    };
}  // namespace Hive