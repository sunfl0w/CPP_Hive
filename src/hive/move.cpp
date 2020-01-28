#include "move.hpp"

namespace Hive {
    Move::Move() {}

    Move::Move(const Move &move) {
        this->moveType = move.moveType;
        this->color = move.color;
        this->startPosition = AxialPosition(move.startPosition);
        this->destinationPosition = AxialPosition(move.destinationPosition);
        this->movedPieceType = move.movedPieceType;
    }

    Move::Move(const MoveType &moveType, const Color &color, const AxialPosition &startPosition, const AxialPosition &destinationPosition, const PieceType &movedPieceType) : startPosition(startPosition), destinationPosition(destinationPosition) {
        this->moveType = moveType;
        this->color = color;
        this->movedPieceType = movedPieceType;
    }

    MoveType Move::GetMoveType() const {
        return moveType;
    }

    Color Move::GetColor() const {
        return color;
    }

    PieceType Move::GetMovedPieceType() const {
        return movedPieceType;
    }

    AxialPosition Move::GetStartPosition() const {
        return startPosition;
    }

    AxialPosition Move::GetDestinationPosition() const {
        return destinationPosition;
    }
}  // namespace Hive