#include "Board.hpp"

namespace Hive {
    //Public Functions

    Board::Board() {
        PlaceObstacles();
    }

    bool Board::GamePieceStackExistsAtPosition(const AxialPosition& position) const {
        //For unordered_map
        int hashValue = position.GetHashValue();
        if (gamePieceStacks.find(hashValue) == gamePieceStacks.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool Board::GamePieceStackExistsAtPosition(int x, int y) const {
        //For unordered_map
        AxialPosition position(x, y);
        return GamePieceStackExistsAtPosition(position);
    }

    Piece::GamePieceStack& Board::GetGamePieceStackAtPosition(AxialPosition& position) {
        return gamePieceStacks[position.GetHashValue()];
    }

    Piece::GamePieceStack& Board::GetGamePieceStackAtPosition(int x, int y) {
        AxialPosition position(x, y);
        return GetGamePieceStackAtPosition(position);
    }

    Piece::GamePiece& Board::GetGamePieceAtPositionAndLayer(AxialPosition& position, int layer) {
        //For unordered_map
        return GetGamePieceStackAtPosition(position).GetGamePieceByLayer(layer);
    }

    Piece::GamePiece& Board::GetGamePieceAtPositionAndLayer(int x, int y, int layer) {
        AxialPosition position(x, y);
        return GetGamePieceAtPositionAndLayer(position, layer);
    }

    std::vector<Piece::GamePieceStack> Board::GetNeighbouringGamePieceStacksAtPosition(AxialPosition& position) {
        //For unordered_map
        std::vector<Piece::GamePieceStack> neighbouringGamingPieceStacks;
        std::vector<AxialPosition> neighbouringPositions = position.GetNeighbouringPositions();

        for (AxialPosition neighbouringPosition : neighbouringPositions) {
            neighbouringGamingPieceStacks.push_back(GetGamePieceStackAtPosition(neighbouringPosition));
        }
        return neighbouringGamingPieceStacks;
    }

    void Board::AddGamePieceOnTopAtPosition(Piece::GamePiece& gamePiece, AxialPosition& position) {
        GetGamePieceStackAtPosition(position).AddGamePieceOnTop(gamePiece);
    }

    void Board::RemoveUpmostGamePieceAtPosition(AxialPosition& position) {
        GetGamePieceStackAtPosition(position).RemoveGamePieceOnTop();
    }

    bool Board::IsAxialPositionAtBorderOfBoard(AxialPosition& position) const {
        int z = 0 - position.x - position.y;
        if (std::abs(position.x) + std::abs(position.y) + std::abs(z) == 10) {
            return true;
        } else {
            return false;
        }
    }

    bool Board::IsAxialPositionOnBoard(AxialPosition& position) const {
        int z = 0 - position.x - position.y;
        if (std::abs(position.x) + std::abs(position.y) + std::abs(z) <= 10) {
            return true;
        } else {
            return false;
        }
    }

    std::vector<AxialPosition> Board::GetEmptyAxialPositionsOnBoard() const {
        std::vector<AxialPosition> emptyAxialPositions;
        for (int x = -5; x <= 5; x++) {
            for (int y = -5; y <= 5; y++) {
                AxialPosition possiblyEmptyPositionOnBoard = AxialPosition(x, y);
                if (IsAxialPositionOnBoard(possiblyEmptyPositionOnBoard) && !GamePieceStackExistsAtPosition(possiblyEmptyPositionOnBoard)) {
                    emptyAxialPositions.push_back(possiblyEmptyPositionOnBoard);
                }
            }
        }
        //std::cout << emptyAxialPositions.size() << std::endl;
        return emptyAxialPositions;
    }

    //Private Functions

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
            Piece::GamePiece obstaclePiece(Piece::PieceType::Obstacle, Piece::PieceColor::None);
            AddGamePieceOnTopAtPosition(obstaclePiece, obstaclePositions[i]);
        }
    }
}  // namespace Hive
