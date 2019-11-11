#include "board.hpp"

namespace Hive {
    //Public Functions

    Board::Board() {
        pieceStacks = std::unordered_map<int, PieceStack>();
        //pieceStacks = std::map<int, PieceStack>();
        //PlaceObstacles();
    }

    Board::Board(const Board& board) {
        pieceStacks = std::unordered_map<int, PieceStack>(board.pieceStacks);
        //pieceStacks = std::map<int, PieceStack>(board.pieceStacks);
    }

    bool Board::PieceStackExists(const AxialPosition& position) const {
        if (pieceStacks.find(position.GetHashValue()) == pieceStacks.end()) {
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

    PieceStack& Board::GetPieceStack(const AxialPosition& position) {
        //PieceStack pieceStack = pieceStacks.at(position.GetHashValue());
        return pieceStacks.at(position.GetHashValue());
    }

    PieceStack& Board::GetPieceStack(int x, int y) {
        AxialPosition position(x, y);
        return GetPieceStack(position);
    }

    PieceStack& Board::GetPieceStackUnsafe(const AxialPosition& position) {
        return pieceStacks.at(position.GetHashValue());
    }

    std::vector<PieceStack*> Board::GetPieceStacks() {
        std::vector<int> keys;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            keys.push_back(pair.first); 
        }

        std::vector<PieceStack*> stacks;
        for (int key : keys) {           
            stacks.push_back(&pieceStacks.at(key));         
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksWithoutObstacles() {
        std::vector<int> keys;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            if (pair.second.GetPieceOnTop().GetType() != PieceType::Obstacle) {
                keys.push_back(pair.first);
            }
        }

        std::vector<PieceStack*> stacks;
        for (int key : keys) {           
            stacks.push_back(&pieceStacks.at(key));         
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksByColor(Color color) {
        std::vector<int> keys;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            if (pair.second.GetPieceOnTop().GetColor() == color) {
                keys.push_back(pair.first);
            }
        }

        std::vector<PieceStack*> stacks;
        for (int key : keys) {           
            stacks.push_back(&pieceStacks.at(key));         
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksByColorAndType(Color color, PieceType pieceType) {
        std::vector<int> keys;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            if (pair.second.GetPieceOnTop().GetColor() == color && pair.second.GetPieceOnTop().GetType() == pieceType) {
                keys.push_back(pair.first);
            }
        }

        std::vector<PieceStack*> stacks;
        for (int key : keys) {           
            stacks.push_back(&pieceStacks.at(key));         
        }
        return stacks;
        /*std::vector<PieceStack> stacks;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            if (pair.second.GetPieceOnTop().GetColor() == color && pair.second.GetPieceOnTop().GetType() == pieceType) {
                stacks.push_back(pair.second);
            }
        }
        return stacks;*/
    }

    std::vector<PieceStack> Board::GetPieceStacksByColorAndType_Copy(Color color, PieceType pieceType) {
        std::vector<PieceStack> stacks;
        for (std::pair<int, PieceStack> pair : pieceStacks) {
            if (pair.second.GetPieceOnTop().GetColor() == color && pair.second.GetPieceOnTop().GetType() == pieceType) {
                stacks.push_back(pair.second);
            }
        }
        return stacks;
    }

    Piece& Board::GetPiece(const AxialPosition& position, int layer) {
        return GetPieceStack(position).GetPieceByLayer(layer);
    }

    Piece& Board::GetPiece(int x, int y, int layer) {
        AxialPosition position(x, y);
        return GetPiece(position, layer);
    }

    std::vector<PieceStack*> Board::GetNeighbouringPieceStacks(const AxialPosition& position) {
        std::vector<PieceStack*> neighbouringPieceStacks;
        neighbouringPieceStacks.reserve(4);

        for (AxialPosition neighbouringPosition : position.GetNeighbouringPositions()) {
            if (PieceStackExists(neighbouringPosition)) {
                neighbouringPieceStacks.push_back(&GetPieceStack(neighbouringPosition));
            }
        }
        return neighbouringPieceStacks;
    }

    std::vector<PieceStack*> Board::GetNeighbouringPieceStacksExceptObstacles(const AxialPosition& position) {
        //For unordered_map
        std::vector<PieceStack*> neighbouringPieceStacks;
        std::vector<AxialPosition> neighbouringPositions = position.GetNeighbouringPositions();

        for (AxialPosition neighbouringPosition : neighbouringPositions) {
            if (PieceStackExists(neighbouringPosition) && GetPieceStack(neighbouringPosition).GetPieceOnTop().GetType() != PieceType::Obstacle) {
                neighbouringPieceStacks.push_back(&GetPieceStack(neighbouringPosition));
            }
        }
        return neighbouringPieceStacks;
    }

    std::vector<AxialPosition> Board::GetEmptyNeighbouringAxialPositions(const AxialPosition& position) {
        std::vector<AxialPosition> neighbouringPositions;
        neighbouringPositions = position.GetNeighbouringPositions();
        for (int i = neighbouringPositions.size() - 1; i >= 0; i--) {
            if (PieceStackExists(neighbouringPositions[i])) {
                neighbouringPositions.erase(neighbouringPositions.begin() + i);
            }
        }
        return neighbouringPositions;
    }

    std::vector<AxialPosition> Board::GetEmptySlideableNeighbouringAxialPositions(const AxialPosition& position) {
        std::vector<AxialPosition> emptyNeighbouringPositions = GetEmptyNeighbouringAxialPositions(position);
        for (int i = emptyNeighbouringPositions.size() - 1; i >= 0; i--) {
            if (!CanSlide(position, emptyNeighbouringPositions[i])) {
                emptyNeighbouringPositions.erase(emptyNeighbouringPositions.begin() + i);
            }
        }
        return emptyNeighbouringPositions;
    }

    std::vector<AxialPosition> Board::GetEmptySlideableNeighbouringAxialPositionsExcept(const AxialPosition& position, const std::vector<AxialPosition>& ignoredPositions) {
        std::vector<AxialPosition> emptyNeighbouringSlideablePosition = GetEmptySlideableNeighbouringAxialPositions(position);
        for (AxialPosition ignoredPosition : ignoredPositions) {
            auto iterator = std::find(emptyNeighbouringSlideablePosition.begin(), emptyNeighbouringSlideablePosition.end(), ignoredPosition);
            if (iterator != emptyNeighbouringSlideablePosition.end()) {
                emptyNeighbouringSlideablePosition.erase(iterator);
            }
        }

        return emptyNeighbouringSlideablePosition;
    }

    void Board::AddPieceOnTop(const Piece& piece, const AxialPosition& position) {
        if (PieceStackExists(position)) {
            GetPieceStackUnsafe(position).AddPieceOnTop(piece);
        } else {
            PieceStack newPieceStack = PieceStack(position);
            newPieceStack.AddPieceOnTop(piece);
            pieceStacks.insert({position.GetHashValue(), newPieceStack});
        }
    }

    void Board::RemoveUpmostPiece(const AxialPosition& position) {
        GetPieceStackUnsafe(position).RemovePieceOnTop();
        if (GetPieceStackUnsafe(position).GetPieces().empty()) {
            pieceStacks.erase(position.GetHashValue());
        }
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

    bool Board::IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position) {
        PieceType type = GetPieceStackUnsafe(position).GetPieceOnTop().GetType();
        Color color = GetPieceStackUnsafe(position).GetPieceOnTop().GetColor();
        std::vector<Piece> pieces = GetPieceStackUnsafe(position).GetPieces();
        std::vector<Piece> obstacle = {Piece(PieceType::Obstacle, Color::Undefined)};
        GetPieceStackUnsafe(position).SetPieces(obstacle);
        //GetPieceStackUnsafe(position).RemovePieceOnTop();
        //RemoveUpmostPiece(position);
        //int hiveSize = GetCoherentHiveSize();
        if (GetCoherentHiveSize() == pieceStacks.size() - 3 - 1) {
            //GetPieceStackUnsafe(position).AddPieceOnTop(Piece(type, color));
            //AddPieceOnTop(Piece(type, color), position);
            GetPieceStackUnsafe(position).SetPieces(pieces);
            return true;
        } else {
            //GetPieceStackUnsafe(position).AddPieceOnTop(Piece(type, color));
            //AddPieceOnTop(Piece(type, color), position);
            GetPieceStackUnsafe(position).SetPieces(pieces);
            return false;
        }
    }

    bool Board::CanSlide(const AxialPosition& slideStartPos, const AxialPosition& slideEndPos) {
        if (!slideStartPos.IsNeighbourTo(slideEndPos)) {
            return false;
        }

        std::vector<PieceStack*> neighbouringPieceStacksAtStart = GetNeighbouringPieceStacks(slideStartPos);
        std::vector<PieceStack*> neighbouringPieceStacksAtEnd = GetNeighbouringPieceStacks(slideEndPos);

        int commonNeighbourCount = 0;
        int commonNeighbourCountExcludingObstacles = 0;

        for (PieceStack* neighbouringPieceStackAtStart : neighbouringPieceStacksAtStart) {
            for (PieceStack* neighbouringPieceStackAtEnd : neighbouringPieceStacksAtEnd) {
                if (neighbouringPieceStackAtStart->GetAxialPosition() == neighbouringPieceStackAtEnd->GetAxialPosition() && neighbouringPieceStackAtEnd->GetAxialPosition() != slideStartPos) {
                    commonNeighbourCount++;
                    if (neighbouringPieceStackAtStart->GetPieceOnTop().GetType() != PieceType::Obstacle) {
                        commonNeighbourCountExcludingObstacles++;
                    }
                }
            }
        }

        if (commonNeighbourCount < 2 && commonNeighbourCountExcludingObstacles > 0) {
            return true;
        } else {
            return false;
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
            Piece obstaclePiece(PieceType::Obstacle, Color::Undefined);
            AddPieceOnTop(obstaclePiece, obstaclePositions[i]);
        }
    }

    int Board::GetCoherentHiveSize() {
        std::unordered_map<int, PieceStack*> hive;
        std::vector<PieceStack*> pieceStacks = GetPieceStacksWithoutObstacles();

        if (pieceStacks.size() == 0) {
            return 0;
        }

        PieceStack* startStack = pieceStacks[0];
        hive.insert({startStack->GetAxialPosition().GetHashValue(), startStack});
        std::vector<PieceStack*> pieceStacksToSearch;
        pieceStacksToSearch.push_back(startStack);

        while (!pieceStacksToSearch.empty()) {
            std::vector<PieceStack*> neighbouringPieceStacks = GetNeighbouringPieceStacks(pieceStacksToSearch[0]->GetAxialPosition());
            for (PieceStack* neighbouringPieceStack : neighbouringPieceStacks) {
                if (hive.find(neighbouringPieceStack->GetAxialPosition().GetHashValue()) == hive.end() && neighbouringPieceStack->GetPieceOnTop().GetType() != PieceType::Obstacle) {
                    hive.insert({neighbouringPieceStack->GetAxialPosition().GetHashValue(), neighbouringPieceStack});
                    pieceStacksToSearch.push_back(neighbouringPieceStack);
                }
            }
            pieceStacksToSearch.erase(pieceStacksToSearch.begin());
        }
        return hive.size();
    }

    int Board::GetDirectionOfNeighbouringPositions(const AxialPosition& startPos, const AxialPosition& destinationPos) const {
        if (startPos.GetDistanceTo(destinationPos) != 1) {
            throw "Error. Unable to get direction between two positions that are not neighbours";
        }
        AxialPosition axialDirection = destinationPos.Subtract(startPos);
        if (AxialPosition(1, -1) == axialDirection) {
            return 0;
        } else if (AxialPosition(1, 0) == axialDirection) {
            return 1;
        } else if (AxialPosition(0, 1) == axialDirection) {
            return 2;
        } else if (AxialPosition(-1, 1) == axialDirection) {
            return 3;
        } else if (AxialPosition(-1, 0) == axialDirection) {
            return 4;
        } else if (AxialPosition(0, -1) == axialDirection) {
            return 5;
        } else {
            return -1;
        }
    }
}  // namespace Hive