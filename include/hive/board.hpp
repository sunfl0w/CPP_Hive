#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <iostream>
#include <deque>

#include "RandomNumberGenerator.hpp"
#include "Piece.hpp"
#include "PieceStack.hpp"
#include "Move.hpp"
#include "AxialPosition.hpp"
#include "PieceType.hpp"
#include "Color.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, PieceStack> pieceStacks;

    public:
        //std::vector<AxialPosition> hiveBorderPositions;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        Board(const Board& board);

        bool PieceStackExists(const AxialPosition& coordinate) const;
        bool PieceStackExists(int x, int y) const;

        PieceStack GetPieceStack(const AxialPosition& position) const;
        PieceStack GetPieceStack(int x, int y) const;
        PieceStack& GetPieceStackUnsafe(const AxialPosition& position);

        std::vector<PieceStack> GetPieceStacks() const;
        std::vector<PieceStack> GetPieceStacksWithoutObstacles() const;
        std::vector<PieceStack> GetPieceStacksByColor(Color color) const;
        std::vector<PieceStack> GetPieceStacksByColorAndType(Color color, PieceType pieceType) const;

        Piece GetPiece(const AxialPosition& position, int layer) const;
        Piece GetPiece(int x, int y, int layer) const;

        std::vector<PieceStack> GetNeighbouringPieceStacks(const AxialPosition& position) const;
        std::vector<PieceStack> GetNeighbouringPieceStacksExceptObstacles(const AxialPosition& position) const;

        std::vector<AxialPosition> GetEmptyNeighbouringAxialPositions(const AxialPosition& position) const;
        std::vector<AxialPosition> GetEmptySlideableNeighbouringAxialPositions(const AxialPosition& position) const;
        std::vector<AxialPosition> GetEmptySlideableNeighbouringAxialPositionsExcept(const AxialPosition& position, const std::vector<AxialPosition>& ignoredPositions) const;

        void AddPieceOnTop(const Piece& piece, const AxialPosition& position);
        void RemoveUpmostPiece(const AxialPosition& position);

        bool IsAxialPositionAtBorderOfBoard(AxialPosition& position) const;
        bool IsAxialPositionOnBoard(AxialPosition& position) const;

        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard() const;

        bool IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position);

        std::vector<PieceStack> GetCommonNeighbouringPieceStacks(const AxialPosition& pos1, const AxialPosition& pos2) const;

        bool CanSlide(const AxialPosition& slideStartPos, const AxialPosition& slideEndPos) const;

        void PlaceObstacles();

    private:
        int GetCoherentHiveSize() const;
        int GetCoherentHiveSize(const AxialPosition& ignorePosition) const;

        int GetDirectionOfNeighbouringPositions(const AxialPosition& startPos, const AxialPosition& destinationPos) const;
    };
}  // namespace Hive