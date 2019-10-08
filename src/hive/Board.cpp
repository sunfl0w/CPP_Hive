#include "Board.hpp"

namespace Hive {
    //Public Functions

    Board::Board() {
        PlaceObstacles();
    }

    bool Board::PieceStackExists(const AxialPosition& position) const {
        //For unordered_map
        int hashValue = position.GetHashValue();
        if (pieceStacks.find(hashValue) == pieceStacks.end()) {
            return false;
        } else {
            return true;
        }
    }

    bool Board::PieceStackExists(int x, int y) const {
        //For unordered_map
        AxialPosition position(x, y);
        return PieceStackExists(position);
    }

    PieceStack& Board::GetPieceStack(const AxialPosition& position) const {
        PieceStack pieceStack = pieceStacks.at(position.GetHashValue());
        return pieceStack;
    }

    PieceStack& Board::GetPieceStack(int x, int y) const {
        AxialPosition position(x, y);
        return GetPieceStack(position);
    }

    std::vector<PieceStack>& Board::GetPieceStacks() const {
        std::vector<PieceStack> stacks;
        for (std::pair<int, PieceStack> stackPair : pieceStacks) {
            stacks.push_back(stackPair.second);
        }
        return stacks;
    }

    std::vector<PieceStack>& Board::GetPieceStacksByColor(PlayerColor playerColor) const {
        std::vector<PieceStack> stacks;
        for (std::pair<int, PieceStack> stackPair : pieceStacks) {
            if (stackPair.second.GetPieceOnTop().GetCorrespondingPlayerColor() == playerColor) {
                stacks.push_back(stackPair.second);
            }
        }
        return stacks;
    }

    std::vector<PieceStack>& Board::GetPieceStacksByColorAndType(PlayerColor playerColor, PieceType pieceType) const {
        std::vector<PieceStack> stacks;
        for (std::pair<int, PieceStack> stackPair : pieceStacks) {
            if (stackPair.second.GetPieceOnTop().GetCorrespondingPlayerColor() == playerColor && stackPair.second.GetPieceOnTop().GetPieceType() == pieceType) {
                stacks.push_back(stackPair.second);
            }
        }
        return stacks;
    }

    Piece& Board::GetPiece(const AxialPosition& position, int layer) const {
        //For unordered_map
        return GetPieceStack(position).GetPieceByLayer(layer);
    }

    Piece& Board::GetPiece(int x, int y, int layer) const {
        AxialPosition position(x, y);
        return GetPiece(position, layer);
    }

    std::vector<PieceStack> Board::GetNeighbouringPieceStacks(const AxialPosition& position) const {
        //For unordered_map
        std::vector<PieceStack> neighbouringPieceStacks;
        std::vector<AxialPosition> neighbouringPositions = position.GetNeighbouringPositions();

        for (AxialPosition neighbouringPosition : neighbouringPositions) {
            neighbouringPieceStacks.push_back(GetPieceStack(neighbouringPosition));
        }
        return neighbouringPieceStacks;
    }

    std::vector<AxialPosition> Board::GetNeighbouringEmptyAxialPositions(const AxialPosition& position) const {
        std::vector<AxialPosition> neighbouringPositions;
        neighbouringPositions = position.GetNeighbouringPositions();
        for (int i = 0; i < neighbouringPositions.size(); i++) {
            if (PieceStackExists(neighbouringPositions[i])) {
                neighbouringPositions.erase(neighbouringPositions.begin() + i);
            }
        }
        return neighbouringPositions;
    }

    void Board::AddPieceOnTop(Piece& piece, AxialPosition& position) {
        if (PieceStackExists(position)) {
            GetPieceStack(position).AddPieceOnTop(piece);
        } else {
            PieceStack newPieceStack = PieceStack(position);
            newPieceStack.AddPieceOnTop(piece);
            pieceStacks[position.GetHashValue()] = newPieceStack;
        }
    }

    void Board::RemoveUpmostPiece(AxialPosition& position) {
        GetPieceStack(position).RemovePieceOnTop();
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
                if (IsAxialPositionOnBoard(possiblyEmptyPositionOnBoard) && !PieceStackExists(possiblyEmptyPositionOnBoard)) {
                    emptyAxialPositions.push_back(possiblyEmptyPositionOnBoard);
                }
            }
        }
        //std::cout << emptyAxialPositions.size() << std::endl;
        return emptyAxialPositions;
    }

    bool Board::IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position) const {
        if (GetCoherentHiveSize(position) == pieceStacks.size() - 1) {
            return true;
        } else {
            return false;
        }
    }

    std::unordered_map<int, AxialPosition> Board::GetMoveableBorderPositionsOfHive(const AxialPosition& moveStartPos) const {
        std::unordered_map<int, AxialPosition> moveableBorderPositions;
        std::unordered_map<int, AxialPosition> borderPositionsToSearch;
        borderPositionsToSearch[moveStartPos.GetHashValue()] = moveStartPos;

        while (!borderPositionsToSearch.empty()) {
            std::vector<AxialPosition> neighbouringEmptyPositions = GetNeighbouringEmptyAxialPositions(borderPositionsToSearch[0]);
            for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
            }
        }
    }

    bool Board::CanSlide(const AxialPosition& slideStartPos, const AxialPosition& slideEndPos) const {
        int slideDirection = GetDirectionOfNeighbouringPositions(slideStartPos, slideEndPos);
        std::vector<PieceStack> neighbouringPieceStacks = GetNeighbouringPieceStacks(slideStartPos);

        bool slideBlockedFromRight = false;
        bool slideBlockedFromLeft = false;
        for(PieceStack neighbouringPieceStack : neighbouringPieceStacks) {
            int directionToNeighbour = GetDirectionOfNeighbouringPositions(slideStartPos, neighbouringPieceStack.GetAxialPosition());
            if(directionToNeighbour == slideDirection - 1 || (slideDirection == 0 && directionToNeighbour == 6)) {
                slideBlockedFromLeft = true;
            } else if(directionToNeighbour == slideDirection + 1 || (slideDirection == 6 && directionToNeighbour == 0)) {
                slideBlockedFromRight = true;
            }
        }

        if(slideBlockedFromLeft && slideBlockedFromRight) {
            return false;
        } else {
            return true;
        }
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
            Piece obstaclePiece(PieceType::Obstacle, PieceColor::None);
            AddPieceOnTop(obstaclePiece, obstaclePositions[i]);
        }
    }

    int Board::GetCoherentHiveSize() const {
        std::unordered_map<int, PieceStack> hive;
        std::vector<PieceStack> pieceStacks = GetPieceStacks();

        if (pieceStacks.size() == 0) {
            return 0;
        }

        PieceStack startStack = pieceStacks[0];
        std::vector<PieceStack> pieceStacksToSearch;
        pieceStacksToSearch.push_back(startStack);

        while (!pieceStacksToSearch.empty()) {
            std::vector<PieceStack> neighbouringPieceStacks = GetNeighbouringPieceStacks(pieceStacksToSearch[0].GetAxialPosition());
            for (PieceStack neighbouringPieceStack : neighbouringPieceStacks) {
                if (hive.find(neighbouringPieceStack.GetAxialPosition().GetHashValue()) == hive.end()) {
                    hive[neighbouringPieceStack.GetAxialPosition().GetHashValue()] = neighbouringPieceStack;
                }
                pieceStacksToSearch.push_back(neighbouringPieceStack);
            }
            pieceStacksToSearch.erase(pieceStacksToSearch.begin());
        }
        return hive.size();
    }

    int Board::GetCoherentHiveSize(const AxialPosition& ignorePosition) const {
        std::unordered_map<int, PieceStack> hive;
        std::vector<PieceStack> pieceStacks = GetPieceStacks();

        if (pieceStacks.size() == 0) {
            return 0;
        }

        PieceStack startStack = pieceStacks[0];
        std::vector<PieceStack> pieceStacksToSearch;
        pieceStacksToSearch.push_back(startStack);

        while (!pieceStacksToSearch.empty()) {
            std::vector<PieceStack> neighbouringPieceStacks = GetNeighbouringPieceStacks(pieceStacksToSearch[0].GetAxialPosition());
            for (PieceStack neighbouringPieceStack : neighbouringPieceStacks) {
                if (neighbouringPieceStack.GetAxialPosition() == ignorePosition) {
                    break;
                }
                if (hive.find(neighbouringPieceStack.GetAxialPosition().GetHashValue()) == hive.end()) {
                    hive[neighbouringPieceStack.GetAxialPosition().GetHashValue()] = neighbouringPieceStack;
                }
                pieceStacksToSearch.push_back(neighbouringPieceStack);
            }
            pieceStacksToSearch.erase(pieceStacksToSearch.begin());
        }
        return hive.size();
    }

    int Board::GetDirectionOfNeighbouringPositions(const AxialPosition& startPos, const AxialPosition& destinationPos) const {
        if(startPos.GetDistanceTo(destinationPos) != 1) {
            throw "Error. Unable to get direction between two positions that are not neighbours";
        }
        AxialPosition axialDirection = destinationPos.Subtract(startPos);
        if(AxialPosition(1, -1) == axialDirection) {
            return 0;
        } else if(AxialPosition(1, 0) == axialDirection) {
            return 1;
        } else if(AxialPosition(0, 1) == axialDirection) {
            return 2;
        } else if(AxialPosition(-1, 1) == axialDirection) {
            return 3;
        } else if(AxialPosition(-1, 0) == axialDirection) {
            return 4;
        } else if(AxialPosition(0, -1) == axialDirection) {
            return 5;
        }
    }
}  // namespace Hive
