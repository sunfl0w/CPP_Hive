#include "Board.hpp"

#include <algorithm>
#include <random>

#include "RandomNumberGenerator.hpp"

namespace Hive {
    Board::Board() {
        PlaceObstacles();
        Util::RandomNumberGenerator randomNumberGenerator;
        randomNumberGenerator.GetRandomInt(-4, 4);
    }

    bool GamingPeaceExistsAtCoordinate(int x, int y, int layer) {
        //For unordered_map
        Coordinate coordinate(x, y, layer);
        if (gamingPieces.find(coordinate.ToHash()) == gamingPieces.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool Board::GamingPeaceExistsAtCoordinate(Coordinate& coordinate) {
        //For unordered_map
        if (gamingPieces.find(coordinate.ToHash()) == gamingPieces.end()) {
            return false;
        } else {
            return true;
        }
    }

    Piece::GamingPiece& Board::GetGamingPieceAtCoordinate(int x, int y, int layer) {
        //For unordered_map
        Coordinate coordinate(x, y, layer);
        return gamingPieces[coordinate.ToHash()];
    }

    Piece::GamingPiece& Board::GetGamingPieceAtCoordinate(Coordinate& coordinate) {
        //For unordered_map
        return gamingPieces[coordinate.ToHash()];
    }

    std::vector<Piece::GamingPiece> Board::GetNeighbouringGamingPiecesAtCoordinate(Coordinate& coordinate) {
        //For unordered_map
        std::vector<Piece::GamingPiece> neighbouringPieces;
        std::vector<Coordinate> neighbouringCoordinates = coordinate.GetNeighbouringCoordinates_ZeroLayer();

        bool isLayerEmpty = false;

        while (!isLayerEmpty) {
            for (int layer = 0; layer < 5; layer++) {
                for (int i = 0; i < neighbouringCoordinates.size(); i++) {
                    if (GamingPeaceExistsAtCoordinate(neighbouringCoordinates[i].x, neighbouringCoordinates[i].y, layer)) {
                        neighbouringPieces.push_back(GetGamingPieceAtCoordinate(neighbouringCoordinates[i].x, neighbouringCoordinates[i].y, layer));
                    }
                }
            }
        }
    }

    void Board::AddGamingPiece(Piece::GamingPiece& gamingPiece) {
        //For unordered_map
        gamingPieces[gamingPiece.GetCoordinate().ToHash()] = gamingPiece;
    }

    void Board::PlaceObstacles() {
        Util::RandomNumberGenerator randomNumberGenerator;
        std::vector<Coordinate> obstacleCoordinates;

        while (obstacleCoordinates.size() < 3) {
            int randXPos = randomNumberGenerator.GetRandomInt(-4, 4);
            int randYPos = randomNumberGenerator.GetRandomInt(-4, 4);
            Coordinate obstacleCoordinate = Coordinate(randXPos, randYPos, 0);

            if (std::find(obstacleCoordinates.begin(), obstacleCoordinates.end(), obstacleCoordinate) == obstacleCoordinates.end()) {
                obstacleCoordinates.push_back(obstacleCoordinate);
            }
        }

        for (int i = 0; i < 3; i++) {
            Piece::GamingPiece obstaclePiece(obstacleCoordinates[i], FieldColor::None);
            AddGamingPiece(obstaclePiece);
        }
    }
}  // namespace Hive
