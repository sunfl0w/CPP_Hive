#pragma once

#include "AxialPosition.hpp"
#include "MoveType.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Move {
    private:
        MoveType moveType;
        AxialPosition startPosition;
        AxialPosition destinationPosition;
        PieceType movedPieceType;

    public:
        Move(const MoveType &moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition, const PieceType &movedPieceType);

        MoveType GetMoveType() const;
        PieceType GetMovedPieceType() const;
        AxialPosition GetStartPosition() const;
        AxialPosition GetDestinationPosition() const;
    };
}  // namespace Hive::Move