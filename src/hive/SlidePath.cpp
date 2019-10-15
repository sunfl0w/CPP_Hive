#include "SlidePath.hpp"

#include "Board.hpp"

namespace Hive{
    SlidePath::SlidePath(const AxialPosition& positionInPath) {
        
    }

    bool SlidePath::IsValidForPiece(const AxialPosition& piecePosition) const {
        bool isValid = false;
        for(AxialPosition slidePathPosition : slidePositions) {
            if(slidePathPosition.IsNeighbourTo(piecePosition)) {
                isValid = true;
                break;
            }
        }
        return isValid;
    }

    bool SlidePath::ContainsPosition(const AxialPosition& position) const {
        if(std::find(slidePositions.begin(), slidePositions.end(), position) != slidePositions.end()) {
            return true;
        } else {
            return false;
        }
    }
}