#pragma once

#include <vector>

#include "GamePiece.hpp"

namespace Hive::Piece {
    class GamePieceStack {
    private:
        std::vector<GamePiece> gamePieces;
    public:
        GamePieceStack();

        void AddGamePieceOnTop(GamePiece& gamePiece);
        void RemoveGamePieceOnTop();
        GamePiece& GetGamePieceByLayer(int layer);
        GamePiece& GetGamePieceOnTop();
        std::vector<GamePiece>& GetGamePieces();
    };
}  // namespace Hive::GamingPiece