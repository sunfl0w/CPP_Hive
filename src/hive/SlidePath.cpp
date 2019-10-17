#include "SlidePath.hpp"

#include "Board.hpp"

namespace Hive {
    SlidePath::SlidePath(const AxialPosition& positionInPath, const Board& board) {
        slidePositions.push_back(positionInPath);

        std::vector<AxialPosition> accesibelNeighboursOnBorder = GetAccesibleNeighbouringPositionsAtBorderOfHive(positionInPath, board);
        while (!accesibelNeighboursOnBorder.empty()) {
            for (int i = 0; i < accesibelNeighboursOnBorder.size(); i++) {
                if (i == 0) {
                    slidePositions.push_front(accesibelNeighboursOnBorder[i]);
                } else {
                    slidePositions.push_back(accesibelNeighboursOnBorder[i]);
                }
            }
            std::vector<AxialPosition> nextAccesibelFrontNeighboursOnBorder = GetAccesibleNeighbouringPositionsAtBorderOfHive(slidePositions.front(), board);
            for(AxialPosition nextAccesibelFrontNeighbourOnBorder : nextAccesibelFrontNeighboursOnBorder) {
                if(!ContainsPosition(nextAccesibelFrontNeighbourOnBorder)) {
                    accesibelNeighboursOnBorder.push_back(nextAccesibelFrontNeighbourOnBorder);
                }
            }

            std::vector<AxialPosition> nextAccesibelBackNeighboursOnBorder = GetAccesibleNeighbouringPositionsAtBorderOfHive(slidePositions.back(), board);
            for(AxialPosition nextAccesibelBackNeighbourOnBorder : nextAccesibelBackNeighboursOnBorder) {
                if(!ContainsPosition(nextAccesibelBackNeighbourOnBorder)) {
                    accesibelNeighboursOnBorder.push_back(nextAccesibelBackNeighbourOnBorder);
                }
            }
        }
    }

    bool SlidePath::IsValidForPiece(const AxialPosition& piecePosition) const {
        bool isValid = false;
        for (AxialPosition slidePathPosition : slidePositions) {
            if (slidePathPosition.IsNeighbourTo(piecePosition)) {
                isValid = true;
                break;
            }
        }
        return isValid;
    }

    bool SlidePath::ContainsPosition(const AxialPosition& position) const {
        if (std::find(slidePositions.begin(), slidePositions.end(), position) != slidePositions.end()) {
            return true;
        } else {
            return false;
        }
    }

    const std::deque<AxialPosition>& SlidePath::GetContainingPositions() const {
        return slidePositions;
    }

    //Private

    std::vector<AxialPosition> SlidePath::GetAccesibleNeighbouringPositionsAtBorderOfHive(const AxialPosition& position, const Board& board) const {
        std::vector<AxialPosition> accesibleNeighbouringBorderPositions;
        for (AxialPosition hiveBorderPosition : board.hiveBorderPositions) {
            if (hiveBorderPosition.GetDistanceTo(position) == 1 && board.CanSlide(position, hiveBorderPosition)) {
                accesibleNeighbouringBorderPositions.push_back(hiveBorderPosition);
            }
        }
        return accesibleNeighbouringBorderPositions;
    }
}  // namespace Hive