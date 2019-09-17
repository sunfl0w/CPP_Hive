#include "Coordinate.hpp"

#include <math.h>

namespace Hive {
    Coordinate::Coordinate() {}

    Coordinate::Coordinate(int x, int y, int layer) {
        if(x > 5 || x < -5 || y > 5 || y < 5) {
            throw "Coordinate would not be on the board!";
        }
        this->x = x;
        this->y = y;
        this->layer = layer;
    }

    int Coordinate::ToHash() {
        return ((73856093 * x) ^ (19349663 * y) ^ (83492791 * layer)) % 100;
    }

    std::vector<Coordinate> Coordinate::GetNeighbouringCoordinates_ZeroLayer() {
        std::vector<Coordinate> neighbouringCoordinates;

        neighbouringCoordinates.push_back(Coordinate(x + 1, y - 1, 0));
        neighbouringCoordinates.push_back(Coordinate(x + 1, y, 0));
        neighbouringCoordinates.push_back(Coordinate(x, y + 1, 0));
        neighbouringCoordinates.push_back(Coordinate(x - 1, y + 1, 0));
        neighbouringCoordinates.push_back(Coordinate(x - 1, y, 0));
        neighbouringCoordinates.push_back(Coordinate(x, y - 1, 0));

        if(IsAtBoarderOfBoard()) {
            for(int i = 0; i < neighbouringCoordinates.size(); i++) {
                if(neighbouringCoordinates[i].x < -5 || neighbouringCoordinates[i].x > 5 || neighbouringCoordinates[i].y < -5 || neighbouringCoordinates[i].y > 5) {
                    neighbouringCoordinates.erase(neighbouringCoordinates.begin() + i);
                }
            }
        }

        return neighbouringCoordinates;
    }

    bool Coordinate::IsAtBoarderOfBoard() {
        int z = 0 - x - y;
        if(std::abs(x) + std::abs(y) + std::abs(z) == 10) {
            return true;
        } else {
            return false;
        }
    }
}  // namespace Hive