#pragma once

#include <vector>
#include <unordered_map>
#include <map>
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
#include "robin_hood.h"
#include "phmap.h"

#include "globals.hpp"

namespace Hive {
    class Board {
    private:
        //robin_hood::unordered_map<int, PieceStack> pieceStacks;
        //phmap::node_hash_map<int, PieceStack> pieceStacks;
        //std::unordered_map<int, PieceStack> pieceStacks;
        //std::map<int, PieceStack> pieceStacks;

        //std::vector<phmap::node_hash_map<int, PieceStack>> pieceStacks;

        std::vector<std::vector<PieceStack>> pieceStacks;

    public:
        //std::vector<AxialPosition> hiveBorderPositions;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        Board(const Board& board);

        bool PieceStackExists(const AxialPosition& coordinate) const;
        bool PieceStackExists(int x, int y) const;

        PieceStack& GetPieceStack(const AxialPosition& position);
        PieceStack& GetPieceStack(int x, int y);
        PieceStack& GetPieceStackUnsafe(const AxialPosition& position);

        std::vector<PieceStack*> GetPieceStacks();
        std::vector<PieceStack*> GetPieceStacksWithoutObstacles();
        std::vector<PieceStack*> GetPieceStacksByColor(Color color);
        std::vector<PieceStack*> GetPieceStacksByColorAndType(Color color, PieceType pieceType);

        Piece& GetPiece(const AxialPosition& position, int layer);
        Piece& GetPiece(int x, int y, int layer);

        std::vector<PieceStack*> GetNeighbouringPieceStacks(const AxialPosition& position);
        std::vector<PieceStack*> GetNeighbouringPieceStacksExceptObstacles(const AxialPosition& position);

        std::vector<AxialPosition> GetEmptyNeighbouringAxialPositions(const AxialPosition& position);
        std::vector<AxialPosition> GetEmptySlideableNeighbouringAxialPositions(const AxialPosition& position);
        std::vector<AxialPosition> GetEmptySlideableNeighbouringAxialPositionsExcept(const AxialPosition& position, const std::vector<AxialPosition>& ignoredPositions);

        void AddPieceOnTop(const Piece& piece, const AxialPosition& position);
        void RemoveUpmostPiece(const AxialPosition& position);

        bool IsAxialPositionAtBorderOfBoard(AxialPosition& position) const;
        bool IsPositionOnBoard(AxialPosition& position) const;
        bool IsPositionOnBoard(int x, int y) const;

        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard() const;

        bool IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position);

        bool CanSlide(const AxialPosition& slideStartPos, const AxialPosition& slideEndPos);

        void PlaceObstacles();

    private:
        bool GetCoherentHiveSize(const AxialPosition& pos);

        int GetDirectionOfNeighbouringPositions(const AxialPosition& startPos, const AxialPosition& destinationPos) const;
        bool AreNeighbouringFieldsCoherent(const AxialPosition& pos);
    };
}  // namespace Hive