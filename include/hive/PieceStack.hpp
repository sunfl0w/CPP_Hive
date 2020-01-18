#pragma once

#include <vector>

#include "AxialPosition.hpp"
#include "Piece.hpp"

namespace Hive {
    class PieceStack {
    private:
        AxialPosition position;
        std::vector<Piece> pieces;

        bool isEmpty = true;

    public:
        PieceStack();
        PieceStack(const PieceStack& pieceStack);
        PieceStack(const AxialPosition& position);

        bool operator==(const PieceStack& pieceStack) const;
        /*inline bool& IsStackEmpty() {
            return isEmpty;
        }*/
        bool IsStackEmpty() const;
        const AxialPosition& GetAxialPosition() const;
        void AddPieceOnTop(const Piece& piece);
        void RemovePieceOnTop();
        Piece& GetPieceByLayer(int layer);
        Piece& GetPieceOnTop();

        std::vector<Piece> GetPieces();
        void SetPieces(std::vector<Piece> pieces);
    };
}  // namespace Hive