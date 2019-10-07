#pragma once

#include "AxialPosition.hpp"
#include "MoveType.hpp"

namespace Hive {
    class Move {
    private:
        MoveType moveType;
        AxialPosition startPosition;
        AxialPosition destinationPosition;

    public:
        Move(MoveType moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition);

        MoveType GetMoveType();
        const AxialPosition& GetStartPosition();
        const AxialPosition& GetDestinationPosition();
    };
}  // namespace Hive::Move