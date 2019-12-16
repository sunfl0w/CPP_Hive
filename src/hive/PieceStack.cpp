#include "PieceStack.hpp"

namespace Hive {
    PieceStack::PieceStack(const AxialPosition& position) {
        this->position = position;
        this->pieces = std::vector<Piece>();
        isEmpty = true;
    }

    bool PieceStack::operator==(const PieceStack &pieceStack) const {
        return position == pieceStack.position;
    }

    /*bool& PieceStack::IsStackEmpty() {
        //return pieces.empty();
        return isEmpty;
    }*/

    const AxialPosition& PieceStack::GetAxialPosition() const {
        return position;
    }

    void PieceStack::AddPieceOnTop(const Piece& piece) {
        pieces.push_back(piece);
        isEmpty = false;
    }

    void PieceStack::RemovePieceOnTop() {
        pieces.erase(pieces.begin() + pieces.size() - 1);
        isEmpty = pieces.empty();
    }

    Piece& PieceStack::GetPieceByLayer(int layer) {
        return pieces[layer];
    }

    Piece& PieceStack::GetPieceOnTop() {
        return pieces[pieces.size() - 1];
    }

    std::vector<Piece> PieceStack::GetPieces() {
        return pieces;
    }

    void PieceStack::SetPieces(std::vector<Piece> pieces) {
        this->pieces = pieces;
        isEmpty = pieces.empty(); 
    }
}  // namespace Hive::Piece