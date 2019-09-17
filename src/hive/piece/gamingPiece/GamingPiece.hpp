#pragma once

#include "FieldColor.hpp"

namespace Hive::Piece {
    class GamingPiece {
    private:
        FieldColor fieldColor;

    public:
        GamingPiece(FieldColor fieldColor);
    };
}  // namespace Hive::Piece