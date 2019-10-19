#include "Move.hpp"

namespace Hive {
    Move::Move(MoveType moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition, PieceType movedPieceType) : startPosition(startPosition), destinationPosition(destinationPosition) {
        this->moveType = moveType;
        this->movedPieceType = movedPieceType;
    }

    MoveType Move::GetMoveType() {
        return moveType;
    }

    const AxialPosition& Move::GetStartPosition() {
        return startPosition;
    }

    const AxialPosition& Move::GetDestinationPosition() {
        return destinationPosition;
    }
}