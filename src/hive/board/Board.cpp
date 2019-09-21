#include "Board.hpp"

namespace Hive {
    Board::Board() {
        PlaceObstacles();
        Util::RandomNumberGenerator randomNumberGenerator;
        randomNumberGenerator.GetRandomInt(-4, 4);
    }

    bool Board::GamingPieceStackExistsAtPosition(AxialPosition& position) {
        //For unordered_map
        if (gamingPieceStacks.find(position.GetHashValue()) == gamingPieceStacks.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool Board::GamingPieceStackExistsAtPosition(int x, int y) {
        //For unordered_map
        AxialPosition position(x, y);
        return GamingPieceStackExistsAtPosition(position);
    }

    Piece::GamingPieceStack& Board::GetGamingPieceStackAtPosition(AxialPosition& position) {
        return gamingPieceStacks[position.GetHashValue()];
    }

    Piece::GamingPieceStack& Board::GetGamingPieceStackAtPosition(int x, int y) {
        AxialPosition position(x, y);
        return GetGamingPieceStackAtPosition(position);
    }

    Piece::GamingPiece& Board::GetGamingPieceAtPositionAndLayer(AxialPosition& position, int layer) {
        //For unordered_map
        return GetGamingPieceStackAtPosition(position).GetGamingPieceByLayer(layer);
    }

    Piece::GamingPiece& Board::GetGamingPieceAtPositionAndLayer(int x, int y, int layer) {
        AxialPosition position(x, y);
        return GetGamingPieceAtPositionAndLayer(position, layer);
    }

    std::vector<Piece::GamingPieceStack> Board::GetNeighbouringGamingPieceStacksAtPosition(AxialPosition& position) {
        //For unordered_map
        std::vector<Piece::GamingPieceStack> neighbouringGamingPieceStacks;
        std::vector<AxialPosition> neighbouringPositions = position.GetNeighbouringPositions();

        for(AxialPosition neighbouringPosition : neighbouringPositions) {
            neighbouringGamingPieceStacks.push_back(GetGamingPieceStackAtPosition(neighbouringPosition));
        }
        return neighbouringGamingPieceStacks;
    }

    void Board::AddGamingPieceOnTopAtPosition(Piece::GamingPiece& gamingPiece, AxialPosition& position) {
        GetGamingPieceStackAtPosition(position).AddGamingPieceOnTop(gamingPiece);
    }

    void Board::RemoveUpmostGamingPieceAtPosition(AxialPosition& position) {
        GetGamingPieceStackAtPosition(position).RemoveGamingPieceOnTop();
    }

    void Board::PlaceObstacles() {
        Util::RandomNumberGenerator randomNumberGenerator;
        std::vector<AxialPosition> obstaclePositions;

        while (obstaclePositions.size() < 3) {
            int randXPos = randomNumberGenerator.GetRandomInt(-5, 5);
            int randYPos = randomNumberGenerator.GetRandomInt(-5, 5);
            AxialPosition obstaclePosition = AxialPosition(randXPos, randYPos);

            if (std::find(obstaclePositions.begin(), obstaclePositions.end(), obstaclePosition) == obstaclePositions.end()) {
                obstaclePositions.push_back(obstaclePosition);
            }
        }

        for (int i = 0; i < 3; i++) {
            Piece::GamingPiece obstaclePiece(Piece::PieceType::Obstacle, Piece::PieceColor::None);
            AddGamingPieceOnTopAtPosition(obstaclePiece, obstaclePositions[i]);
        }
    }
}  // namespace Hive
