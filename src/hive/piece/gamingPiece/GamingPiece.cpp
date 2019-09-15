#include "GamingPiece.hpp"

namespace Hive::Piece {
    GamingPiece::GamingPiece(Coordinate& coordinate, FieldColor fieldColor) {
        this->coordinate = Coordinate(coordinate);
        this->fieldColor = fieldColor;
    }
}