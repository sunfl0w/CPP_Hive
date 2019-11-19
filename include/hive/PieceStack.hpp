#pragma once

#include <vector>

#include "Piece.hpp"
#include "AxialPosition.hpp"

namespace Hive {
    class PieceStack {
    private:
        std::vector<Piece> pieces;
        AxialPosition position;
    public:
        PieceStack(const AxialPosition& position);

        bool operator==(const PieceStack &pieceStack) const;

        const AxialPosition& GetAxialPosition() const;
        void AddPieceOnTop(const Piece& piece);
        void RemovePieceOnTop();
        Piece& GetPieceByLayer(int layer);
        Piece& GetPieceOnTop();

        std::vector<Piece> GetPieces();
        void SetPieces(std::vector<Piece> pieces);
    };
}  // namespace Hive::GamingPiece