#pragma once

#include <vector>

#include "Color.hpp"
#include "Piece.hpp"

namespace Hive {
    class Player {
    private:
        Color color;

        std::vector<Piece> undeployedPieces;
    public:
        Player(Color color);

        const Color& GetColor() const;

        const std::vector<Piece>& GetUndeployedPieces() const;

    private:
        void InitializeUndeployedPieces();
    };
}  // namespace Hive::Player