#pragma once

#include "Coordinate.hpp"
#include "FieldColor.hpp"

namespace Hive::Piece {
    class GamingPiece {
    private:
        Coordinate coordinate;
        FieldColor fieldColor;

    public:
        GamingPiece(Coordinate& coordinate, FieldColor fieldColor);
    };
}  // namespace Hive::Piece