#pragma once

#include "AxialPosition.hpp"
#include "MoveType.hpp"

namespace Hive::Move {
    class HiveMove {
    private:
        MoveType moveType;
        AxialPosition startPosition;
        AxialPosition destinationPosition;

    public:
        HiveMove(MoveType moveType, const AxialPosition &startPosition, const AxialPosition &destinationPosition);

        MoveType GetMoveType();
        const AxialPosition& GetStartPosition();
        const AxialPosition& GetDestinationPosition();
    };
}  // namespace Hive::Move