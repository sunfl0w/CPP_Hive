#include "GamingPieceStack.hpp"

namespace Hive::Piece {
    GamingPieceStack::GamingPieceStack() {}

    void GamingPieceStack::AddGamingPieceOnTop(GamingPiece& gamingPiece) {
        gamingPieces.push_back(gamingPiece);
    }

    void GamingPieceStack::RemoveGamingPieceOnTop() {
        gamingPieces.erase(gamingPieces.begin() + gamingPieces.size() - 1);
    }

    GamingPiece& GamingPieceStack::GetUpmostGamingPiece() {

    }
}  // namespace Hive::Piece