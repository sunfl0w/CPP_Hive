#include "Board.hpp"

#include <random>
#include <algorithm>

#include "RandomNumberGenerator.hpp"

namespace Hive {
    Board::Board() {
        PlaceObstacles();
        Util::RandomNumberGenerator randomNumberGenerator;
        randomNumberGenerator.GetRandomInt(-4, 4);
    }

    void Board::PlaceObstacles() {
        Util::RandomNumberGenerator randomNumberGenerator;
        std::vector<Coordinate> obstacleCoordinates;

        while(obstacleCoordinates.size() < 3) {
            int randXPos = randomNumberGenerator.GetRandomInt(-4, 4);
            int randYPos = randomNumberGenerator.GetRandomInt(-4, 4);
            Coordinate obstacleCoordinate = Coordinate(randXPos, randYPos, 0);

            if(std::find(obstacleCoordinates.begin(), obstacleCoordinates.end(), obstacleCoordinate) == obstacleCoordinates.end()) {
                obstacleCoordinates.push_back(obstacleCoordinate);
            }
        }

        for(int i = 0; i < 3; i++) {
            Piece::GamingPiece obstaclePiece(obstacleCoordinates[i], FieldColor::None);
            pieces.push_back(obstaclePiece);
        }
    }
}  // namespace Hive
