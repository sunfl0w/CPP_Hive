#pragma once

#include "AxialPosition.hpp"
#include "Color.hpp"
#include "MoveType.hpp"
#include "PieceType.hpp"

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
        Move(const Move &move);
        Move(const MoveType &moveType, const Color &color, const AxialPosition &startPosition, const AxialPosition &destinationPosition, const PieceType &movedPieceType);

        MoveType GetMoveType() const;
        Color GetColor() const;
        PieceType GetMovedPieceType() const;
        AxialPosition GetStartPosition() const;
        AxialPosition GetDestinationPosition() const;
    };
}  // namespace Hive