#include "HiveMove.hpp"

namespace Hive::Move {
    HiveMove::HiveMove(MoveType moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition) : startPosition(startPosition), destinationPosition(destinationPosition) {
        this->moveType = moveType;
    }

    MoveType HiveMove::GetMoveType() {
        return moveType;
    }

    const AxialPosition& HiveMove::GetStartPosition() {
        return startPosition;
    }

    const AxialPosition& HiveMove::GetDestinationPosition() {
        return destinationPosition;
    }
}