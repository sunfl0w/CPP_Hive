#pragma once

#include <vector>

#include "AxialPosition.hpp"
#include "Piece.hpp"

namespace Hive {
    class PieceStack {
    private:
        std::vector<Piece> pieces;
        AxialPosition position;

        bool isEmpty = true;

    public:
        PieceStack(const AxialPosition& position);

        bool operator==(const PieceStack& pieceStack) const;
        inline bool& IsStackEmpty() {
            return isEmpty;
        }

        const AxialPosition& GetAxialPosition() const;
        void AddPieceOnTop(const Piece& piece);
        void RemovePieceOnTop();
        Piece& GetPieceByLayer(int layer);
        Piece& GetPieceOnTop();

        std::vector<Piece> GetPieces();
        void SetPieces(std::vector<Piece> pieces);
    };
}  // namespace Hive