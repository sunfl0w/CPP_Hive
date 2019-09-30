#include "Board.hpp"

namespace Hive {
    //Public Functions

    Board::Board() {
        PlaceObstacles();
    }

    bool Board::GamePieceStackExists(const AxialPosition& position) const {
        //For unordered_map
        int hashValue = position.GetHashValue();
        if (gamePieceStacks.find(hashValue) == gamePieceStacks.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool Board::GamePieceStackExists(int x, int y) const {
        //For unordered_map
        AxialPosition position(x, y);
        return GamePieceStackExists(position);
    }

    Piece::GamePieceStack& Board::GetGamePieceStack(const AxialPosition& position) const {
        Piece::GamePieceStack stack = gamePieceStacks.at(position.GetHashValue());
        return stack;
    }

    Piece::GamePieceStack& Board::GetGamePieceStack(int x, int y) const {
        AxialPosition position(x, y);
        return GetGamePieceStack(position);
    }

    std::vector<Piece::GamePieceStack>& Board::GetGamePieceStacks() const {
        std::vector<Piece::GamePieceStack> stacks;
        for (std::pair<int, Piece::GamePieceStack> stack : gamePieceStacks) {
            stacks.push_back(stack.second);
        }
        return stacks;
    }

    Piece::GamePiece& Board::GetGamePiece(const AxialPosition& position, int layer) const {
        //For unordered_map
        return GetGamePieceStack(position).GetGamePieceByLayer(layer);
    }

    Piece::GamePiece& Board::GetGamePiece(int x, int y, int layer) const {
        AxialPosition position(x, y);
        return GetGamePiece(position, layer);
    }

    std::vector<Piece::GamePieceStack> Board::GetNeighbouringGamePieceStacks(const AxialPosition& position) const {
        //For unordered_map
        std::vector<Piece::GamePieceStack> neighbouringGamingPieceStacks;
        std::vector<AxialPosition> neighbouringPositions = position.GetNeighbouringPositions();

        for (AxialPosition neighbouringPosition : neighbouringPositions) {
            neighbouringGamingPieceStacks.push_back(GetGamePieceStack(neighbouringPosition));
        }
        return neighbouringGamingPieceStacks;
    }

    std::vector<AxialPosition> Board::GetNeighbouringEmptyAxialPositions(const AxialPosition& position) const {
        std::vector<AxialPosition> neighbouringPositions;
        neighbouringPositions = position.GetNeighbouringPositions();
        for (int i = 0; i < neighbouringPositions.size(); i++) {
            if (GamePieceStackExists(neighbouringPositions[i])) {
                neighbouringPositions.erase(neighbouringPositions.begin() + i);
            }
        }
        return neighbouringPositions;
    }

    void Board::AddGamePieceOnTop(Piece::GamePiece& gamePiece, AxialPosition& position) {
        GetGamePieceStack(position).AddGamePieceOnTop(gamePiece);
    }

    void Board::RemoveUpmostGamePiece(AxialPosition& position) {
        GetGamePieceStack(position).RemoveGamePieceOnTop();
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
                if (IsAxialPositionOnBoard(possiblyEmptyPositionOnBoard) && !GamePieceStackExists(possiblyEmptyPositionOnBoard)) {
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
            AddGamePieceOnTop(obstaclePiece, obstaclePositions[i]);
        }
    }
}  // namespace Hive
