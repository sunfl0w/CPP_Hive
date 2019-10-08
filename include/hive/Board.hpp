#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <iostream>

#include "RandomNumberGenerator.hpp"
#include "Piece.hpp"
#include "PieceStack.hpp"
#include "Move.hpp"
#include "AxialPosition.hpp"
#include "PieceType.hpp"
#include "PlayerColor.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, PieceStack> pieceStacks;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        void PerformMove(Move& move);

        bool PieceStackExists(const AxialPosition& coordinate) const;
        bool PieceStackExists(int x, int y) const;

        PieceStack& GetPieceStack(const AxialPosition& position) const;
        PieceStack& GetPieceStack(int x, int y) const;

        std::vector<PieceStack>& GetPieceStacks() const;
        std::vector<PieceStack>& GetPieceStacksByColor(PlayerColor playerColor) const;

        Piece& GetPiece(const AxialPosition& position, int layer) const;
        Piece& GetPiece(int x, int y, int layer) const;

        std::vector<PieceStack> GetNeighbouringPieceStacks(const AxialPosition& position) const;
        std::vector<AxialPosition> GetNeighbouringEmptyAxialPositions(const AxialPosition& position) const;

        void AddPieceOnTop(Piece& piece, AxialPosition& position);
        void RemoveUpmostPiece(AxialPosition& position);

        bool IsAxialPositionAtBorderOfBoard(AxialPosition& position) const;
        bool IsAxialPositionOnBoard(AxialPosition& position) const;

        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard() const;

        bool IsHiveCoherentIfPieceMoves(const Piece& piece) const;

    private:
        void PlaceObstacles();

        int GetCoherentHiveSize() const;
    };
}  // namespace Hive