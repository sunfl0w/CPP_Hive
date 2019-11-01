#include "PieceStack.hpp"

namespace Hive {
    PieceStack::PieceStack(const AxialPosition& position) {
        this->position = position;
        this->pieces = std::vector<Piece>();
    }

    const AxialPosition& PieceStack::GetAxialPosition() const {
        return position;
    }

    void PieceStack::AddPieceOnTop(const Piece& piece) {
        pieces.push_back(piece);
    }

    void PieceStack::RemovePieceOnTop() {
        pieces.erase(pieces.begin() + pieces.size() - 1);
    }

    Piece& PieceStack::GetPieceByLayer(int layer) {
        return pieces[layer];
    }

    Piece& PieceStack::GetPieceOnTop() {
        return pieces[pieces.size() - 1];
    }

    std::vector<Piece>& PieceStack::GetPieces() {
        return pieces;
    }
}  // namespace Hive::Piece