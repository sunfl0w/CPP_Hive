#pragma once

#include <vector>

#include "GamePiece.hpp"
#include "AxialPosition.hpp"

namespace Hive::Piece {
    class GamePieceStack {
    private:
        std::vector<GamePiece> gamePieces;
        AxialPosition position;
    public:
        GamePieceStack(AxialPosition& position);

        const AxialPosition& GetAxialPosition() const;
        void AddGamePieceOnTop(GamePiece& gamePiece);
        void RemoveGamePieceOnTop();
        GamePiece& GetGamePieceByLayer(int layer);
        GamePiece& GetGamePieceOnTop();
        std::vector<GamePiece>& GetGamePieces();
    };
}  // namespace Hive::GamingPiece