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
        Move(MoveType moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition, PieceType movedPieceType);

        MoveType GetMoveType();
        const AxialPosition& GetStartPosition();
        const AxialPosition& GetDestinationPosition();
    };
}  // namespace Hive::Move