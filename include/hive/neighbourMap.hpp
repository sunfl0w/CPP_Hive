#pragma once

#include <vector>

#include "axialPosition.hpp"

namespace Hive {
    /**
     * @brief This is a special class that holds all Positions of the Board and their neighbouring Positions for fast access.
     * 
     */
    class NeighbourMap {
    private:
        /**
         * @brief The data structure that holds all Positions and their neighbours.
         * 
         */
        std::vector<std::vector<AxialPosition>> neighbourMap;
    public:
        /**
         * @brief Constructs new NeighbourMap and initializes it.
         * 
         */
        NeighbourMap();

        /**
         * @brief Gets the neighbouring Positions of a Position.
         * 
         * @param position The positions to get the neighbours of.
         * @return A vector of pointers to neighbouring Positions.
         */
        std::vector<AxialPosition*> GetNeighbouringPositions(const AxialPosition& position);

        /**
         * @brief Gets the neighbouring Positions of a Position.
         * 
         * @param position The positions to get the neighbours of.
         * @return A vector of neighbouring Positions as reference.
         */
        std::vector<AxialPosition>& GetNeighbouringPositionsRef(const AxialPosition& position);
    };
}  // namespace Hive