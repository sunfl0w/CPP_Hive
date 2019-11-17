#pragma once

#include <unordered_map>
#include <vector>

#include "AxialPosition.hpp"

namespace Hive {
    class NeighbourMap {
    private:
        std::unordered_map<int, std::vector<AxialPosition>> neighbourMap;
    public:
        NeighbourMap();
        std::vector<AxialPosition*> GetNeighbouringPositions(const AxialPosition& axialPosition); 
    };
}  // namespace Hive