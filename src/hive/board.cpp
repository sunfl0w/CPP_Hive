#include "board.hpp"

namespace Hive {
    //Public Functions

    Board::Board() {
        for (int x = -5; x < 6; x++) {
            for (int y = -5; y < 6; y++) {
                pieceStacks[(x + 5) * 11 + (y + 5)] = PieceStack(AxialPosition(x, y));
            }
        }
    }

    Board::Board(const Board& board) : pieceStacks(board.pieceStacks) {}

    bool Board::PieceStackExists(const AxialPosition& position) {
        return !pieceStacks[(position.x + 5) * 11 + (position.y + 5)].IsStackEmpty();
    }

    bool Board::PieceStackExists(int x, int y) {
        return !pieceStacks[(x + 5) * 11 + (y + 5)].IsStackEmpty();
    }

    PieceStack& Board::GetPieceStack(const AxialPosition& position) {
        return pieceStacks[(position.x + 5) * 11 + (position.y + 5)];
    }

    PieceStack& Board::GetPieceStack(int x, int y) {
        return pieceStacks[(x + 5) * 11 + (y + 5)];
    }

    PieceStack& Board::GetPieceStackUnsafe(const AxialPosition& position) {
        return pieceStacks[(position.x + 5) * 11 + (position.y + 5)];
    }

    std::vector<PieceStack*> Board::GetPieceStacks() {
        std::vector<PieceStack*> stacks;
        stacks.reserve(25);
        for (int x = 0; x < 11; x++) {
            for (int y = 0; y < 11; y++) {
                if (!pieceStacks[x * 11 + y].IsStackEmpty()) {
                    stacks.push_back(&pieceStacks[x * 11 + y]);
                }
            }
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksWithoutObstacles() {
        std::vector<PieceStack*> stacks = GetPieceStacks();
        for (int i = stacks.size() - 1; i >= 0; i--) {
            if (stacks[i]->GetPieceOnTop().GetType() == PieceType::Obstacle) {
                stacks.erase(stacks.begin() + i);
            }
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksByColor(Color color) {
        std::vector<PieceStack*> stacks = GetPieceStacks();
        for (int i = stacks.size() - 1; i >= 0; i--) {
            if (stacks[i]->GetPieceOnTop().GetColor() != color) {
                stacks.erase(stacks.begin() + i);
            }
        }
        return stacks;
    }

    std::vector<PieceStack*> Board::GetPieceStacksByColorAndType(Color color, PieceType pieceType) {
        std::vector<PieceStack*> stacks = GetPieceStacks();
        for (int i = stacks.size() - 1; i >= 0; i--) {
            if (stacks[i]->GetPieceOnTop().GetColor() != color || stacks[i]->GetPieceOnTop().GetType() != pieceType) {
                stacks.erase(stacks.begin() + i);
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
        neighbouringPieceStacks.reserve(6);

        for (AxialPosition neighbouringPosition : neighbourMap.GetNeighbouringPositionsRef(position)) {
            if (PieceStackExists(neighbouringPosition)) {
                neighbouringPieceStacks.push_back(&GetPieceStack(neighbouringPosition));
            }
        }
        return neighbouringPieceStacks;
    }

    std::vector<PieceStack*> Board::GetNeighbouringPieceStacksExceptObstacles(const AxialPosition& position) {
        std::vector<PieceStack*> neighbouringPieceStacks;
        neighbouringPieceStacks.reserve(6);

        for (AxialPosition neighbouringPosition : neighbourMap.GetNeighbouringPositionsRef(position)) {
            if (PieceStackExists(neighbouringPosition) && GetPieceStack(neighbouringPosition).GetPieceOnTop().GetType() != PieceType::Obstacle) {
                neighbouringPieceStacks.push_back(&GetPieceStack(neighbouringPosition));
            }
        }
        return neighbouringPieceStacks;
    }

    std::vector<AxialPosition*> Board::GetEmptyNeighbouringAxialPositions(const AxialPosition& position) {
        std::vector<AxialPosition*> neighbouringPositions = neighbourMap.GetNeighbouringPositions(position);
        for (int i = neighbouringPositions.size() - 1; i >= 0; i--) {
            if (PieceStackExists(*neighbouringPositions[i])) {
                neighbouringPositions.erase(neighbouringPositions.begin() + i);
            }
        }
        return neighbouringPositions;
    }

    std::vector<AxialPosition*> Board::GetEmptySlideableNeighbouringAxialPositions(const AxialPosition& position) {
        std::vector<AxialPosition*> emptyNeighbouringPositions = GetEmptyNeighbouringAxialPositions(position);
        for (int i = emptyNeighbouringPositions.size() - 1; i >= 0; i--) {
            if (!CanSlide(position, *emptyNeighbouringPositions[i])) {
                emptyNeighbouringPositions.erase(emptyNeighbouringPositions.begin() + i);
            }
        }
        return emptyNeighbouringPositions;
    }

    std::vector<AxialPosition*> Board::GetEmptySlideableNeighbouringAxialPositionsExcept(const AxialPosition& position, const std::vector<AxialPosition>& ignoredPositions) {
        std::vector<AxialPosition*> emptyNeighbouringSlideablePositions = GetEmptySlideableNeighbouringAxialPositions(position);
        for (int i = emptyNeighbouringSlideablePositions.size() - 1; i >= 0; i--) {
            for (AxialPosition ignoredPosition : ignoredPositions) {
                auto iterator = std::find_if(emptyNeighbouringSlideablePositions.begin(), emptyNeighbouringSlideablePositions.end(), [&](AxialPosition* pos) { return pos->GetHashValue() == ignoredPosition.GetHashValue(); });
                if (iterator != emptyNeighbouringSlideablePositions.end()) {
                    emptyNeighbouringSlideablePositions.erase(iterator);
                }
            }
        }

        return emptyNeighbouringSlideablePositions;
    }

    void Board::AddPieceOnTop(const Piece& piece, const AxialPosition& position) {
        if (PieceStackExists(position)) {
            GetPieceStackUnsafe(position).AddPieceOnTop(piece);
        } else {
            PieceStack newPieceStack = PieceStack(position);
            newPieceStack.AddPieceOnTop(piece);
            pieceStacks[(position.x + 5) * 11 + (position.y + 5)] = newPieceStack;
        }
    }

    void Board::RemoveUpmostPiece(const AxialPosition& position) {
        GetPieceStackUnsafe(position).RemovePieceOnTop();
    }

    bool Board::IsAxialPositionAtBorderOfBoard(AxialPosition& position) const {
        return std::abs(position.x) + std::abs(position.y) + std::abs(0 - position.x - position.y) == 10;
    }

    bool Board::IsPositionOnBoard(AxialPosition& position) const {
        return std::abs(position.x) + std::abs(position.y) + std::abs(0 - position.x - position.y) <= 10;
    }

    bool Board::IsPositionOnBoard(int x, int y) const {
        return std::abs(x) + std::abs(y) + std::abs(0 - x - y) <= 10;
    }

    std::vector<AxialPosition> Board::GetEmptyAxialPositionsOnBoard() {
        std::vector<AxialPosition> emptyAxialPositions;
        emptyAxialPositions.reserve(80);
        for (int x = 0; x < 11; x++) {
            for (int y = 0; y < 11; y++) {
                AxialPosition pos = AxialPosition(x, y);
                if (!PieceStackExists(x, y) && pos.IsOnBoard()) {
                    emptyAxialPositions.push_back(pos);
                }
            }
        }
        return emptyAxialPositions;
    }

    bool Board::IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position) {
        //Replacing moving piece with an obstacle for easy computation.
        std::vector<Piece> pieces = GetPieceStackUnsafe(position).GetPieces();
        std::vector<Piece> obstacle = {Piece(PieceType::Obstacle, Color::Undefined)};
        GetPieceStackUnsafe(position).SetPieces(obstacle);

        std::vector<PieceStack*> pieceStacks = GetPieceStacksWithoutObstacles();
        if (pieceStacks.size() == 1 || pieceStacks.size() == 0) {
            return true;
        }

        std::vector<PieceStack*> hive;
        hive.reserve(22);

        std::vector<AxialPosition*> neighbouringPositions = neighbourMap.GetNeighbouringPositions(position);

        PieceStack* startStack = pieceStacks[0];

        hive.push_back(startStack);
        std::deque<PieceStack*> pieceStacksToSearch;
        pieceStacksToSearch.push_back(startStack);

        int iterator = 0;
        while (!pieceStacksToSearch.empty()) {
            iterator++;
            std::vector<PieceStack*> neighbouringPieceStacks = GetNeighbouringPieceStacksExceptObstacles(pieceStacksToSearch[0]->GetAxialPosition());

            for (PieceStack* neighbouringPieceStack : neighbouringPieceStacks) {
                if (std::find(hive.begin(), hive.end(), neighbouringPieceStack) == hive.end()) {      
                    hive.push_back(neighbouringPieceStack);
                    pieceStacksToSearch.push_back(neighbouringPieceStack);
                }
            }
            if (iterator >= neighbouringPositions.size() + 14) {
                std::sort(hive.begin(), hive.end());
                bool allNeighboursInHive = true;

                for (AxialPosition* neighbouringPos : neighbouringPositions) {
                    if (std::find(hive.begin(), hive.end(), &GetPieceStackUnsafe(*neighbouringPos)) == hive.end()) {
                        allNeighboursInHive = false;
                        break;
                    }
                }
                if (allNeighboursInHive) {
                    GetPieceStackUnsafe(position).SetPieces(pieces);
                    return true;
                }
            }
            pieceStacksToSearch.pop_front();
        }

        GetPieceStackUnsafe(position).SetPieces(pieces);
        if (hive.size() == pieceStacks.size()) {
            return true;
        }
        return false;
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
                if (neighbouringPieceStackAtStart->GetAxialPosition() == neighbouringPieceStackAtEnd->GetAxialPosition() && neighbouringPieceStackAtEnd->GetAxialPosition() != slideStartPos && neighbouringPieceStackAtEnd->GetPieceOnTop().GetType() != PieceType::Undefined) {
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
        srand (time(NULL));
        std::vector<AxialPosition> obstaclePositions;

        while (obstaclePositions.size() < 3) {
            int randXPos = rand() % 11 - 5;
            int randYPos = rand() % 11 - 5;
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

    bool Board::GetCoherentHiveSize(const AxialPosition& pos) {
        //robin_hood::unordered_map<int, PieceStack*> hive;
        std::vector<PieceStack*> hive;
        std::vector<PieceStack*> pieceStacks = GetPieceStacksWithoutObstacles();

        std::vector<AxialPosition*> neighbouringPositions = neighbourMap.GetNeighbouringPositions(pos);

        PieceStack* startStack = pieceStacks[0];
        //hive.insert({startStack->GetAxialPosition().GetHashValue(), startStack});
        hive.push_back(startStack);
        std::deque<PieceStack*> pieceStacksToSearch;
        pieceStacksToSearch.push_back(startStack);

        int iterator = 0;
        while (!pieceStacksToSearch.empty()) {
            iterator++;
            std::vector<PieceStack*> neighbouringPieceStacks = GetNeighbouringPieceStacksExceptObstacles(pieceStacksToSearch[0]->GetAxialPosition());
            for (PieceStack* neighbouringPieceStack : neighbouringPieceStacks) {
                /*if (hive.find(neighbouringPieceStack->GetAxialPosition().GetHashValue()) == hive.end()) {
                    hive.insert({neighbouringPieceStack->GetAxialPosition().GetHashValue(), neighbouringPieceStack});
                    pieceStacksToSearch.push_back(neighbouringPieceStack);
                }*/
                if (std::find(hive.begin(), hive.end(), neighbouringPieceStack) == hive.end()) {
                    hive.push_back(neighbouringPieceStack);
                    pieceStacksToSearch.push_back(neighbouringPieceStack);
                }
            }
            if (iterator >= neighbouringPositions.size() + 14) {
                bool allNeighboursInHive = true;
                for (AxialPosition* neighbouringPos : neighbouringPositions) {
                    if (std::find(hive.begin(), hive.end(), &GetPieceStackUnsafe(*neighbouringPos)) == hive.end()) {
                        allNeighboursInHive = false;
                    }
                }
                if (allNeighboursInHive) {
                    return true;
                }
            }
            pieceStacksToSearch.pop_front();
        }
        return hive.size() == pieceStacks.size();
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

    bool Board::AreNeighbouringFieldsCoherent(const AxialPosition& pos) {
        std::vector<AxialPosition> neighbouringPositions = neighbourMap.GetNeighbouringPositionsRef(pos);

        int connectionSum = 0;
        for (AxialPosition neighbouringPosition : neighbouringPositions) {
            for (AxialPosition otherNeighbouringPosition : neighbouringPositions) {
                if (neighbouringPosition != otherNeighbouringPosition) {
                    if (neighbouringPosition.IsNeighbourTo(otherNeighbouringPosition)) {
                        connectionSum++;
                    }
                }
            }
        }

        if (connectionSum == neighbouringPositions.size() - 1 || neighbouringPositions.size() == 0) {
            return true;
        } else {
            return false;
        }
    }

}  // namespace Hive