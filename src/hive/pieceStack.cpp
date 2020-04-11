#include "pieceStack.hpp"

namespace Hive {
    PieceStack::PieceStack() {
        this->pieces = std::vector<Piece>();
    }

    PieceStack::PieceStack(const PieceStack& pieceStack) {
        this->position = AxialPosition(pieceStack.position);
        this->pieces = std::vector<Piece>(pieceStack.pieces);
    }

    PieceStack::PieceStack(const AxialPosition& position) {
        this->position = position;
        this->pieces = std::vector<Piece>();
    }

    bool PieceStack::operator==(const PieceStack& pieceStack) const {
        return position == pieceStack.position;
    }

    bool PieceStack::IsStackEmpty() const {
        return pieces.empty();
    }

    AxialPosition& PieceStack::GetAxialPosition() {
        return position;
    }

    void PieceStack::AddPieceOnTop(const Piece& piece) {
        pieces.emplace_back(piece);
    }

    void PieceStack::RemovePieceOnTop() {
        pieces.pop_back();
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

    void PieceStack::SetPieces(std::vector<Piece> pieces) {
        this->pieces = pieces;
    }
}  // namespace Hive