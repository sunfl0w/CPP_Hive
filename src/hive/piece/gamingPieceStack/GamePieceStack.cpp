#include "GamePieceStack.hpp"

namespace Hive::Piece {
    GamePieceStack::GamePieceStack() {}

    void GamePieceStack::AddGamePieceOnTop(GamePiece& gamePiece) {
        gamePieces.push_back(gamePiece);
    }

    void GamePieceStack::RemoveGamePieceOnTop() {
        gamePieces.erase(gamePieces.begin() + gamePieces.size() - 1);
    }

    GamePiece& GamePieceStack::GetGamePieceByLayer(int layer) {
        return gamePieces[layer];
    }

    GamePiece& GamePieceStack::GetGamePieceOnTop() {
        return gamePieces[gamePieces.size() - 1];
    }

    std::vector<GamePiece>& GamePieceStack::GetGamePieces() {
        return gamePieces;
    }
}  // namespace Hive::Piece