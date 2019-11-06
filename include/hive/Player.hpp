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
        Player();
        Player(Color color);

        Color GetColor() const;
        void SetColor(Color color);

        const std::vector<Piece>& GetUndeployedPieces() const;
        void AddUndeployedPiece(Piece piece);

        void InitializeUndeployedPieces();
    };
}  // namespace Hive::Player