#pragma once

#include "AxialPosition.hpp"
#include "MoveType.hpp"
#include "PieceType.hpp"
#include "Color.hpp"

namespace Hive {
    class Move {
    private:
        MoveType moveType;
        Color color;
        AxialPosition startPosition;
        AxialPosition destinationPosition;
        PieceType movedPieceType;

    public:
        Move();
        Move(const MoveType &moveType, const Color &color, const AxialPosition &startPosition, const AxialPosition &destinationPosition, const PieceType &movedPieceType);

        MoveType GetMoveType() const;
        Color GetColor() const;
        PieceType GetMovedPieceType() const;
        AxialPosition GetStartPosition() const;
        AxialPosition GetDestinationPosition() const;
    };
}  // namespace Hive::Move