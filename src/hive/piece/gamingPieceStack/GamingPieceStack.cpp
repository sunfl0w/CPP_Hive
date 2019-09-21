#include "GamingPieceStack.hpp"

namespace Hive::Piece {
    GamingPieceStack::GamingPieceStack() {}

    void GamingPieceStack::AddGamingPieceOnTop(GamingPiece& gamingPiece) {
        gamingPieces.push_back(gamingPiece);
    }

    void GamingPieceStack::RemoveGamingPieceOnTop() {
        gamingPieces.erase(gamingPieces.begin() + gamingPieces.size() - 1);
    }

    GamingPiece& GamingPieceStack::GetGamingPieceByLayer(int layer) {
        return gamingPieces[layer];
    }

    GamingPiece& GamingPieceStack::GetGamingPieceOnTop() {
        return gamingPieces[gamingPieces.size() - 1];
    }

    std::vector<GamingPiece>& GamingPieceStack::GetGamingPieces() {
        return gamingPieces;
    }
}  // namespace Hive::Piece