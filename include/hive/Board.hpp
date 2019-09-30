#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <random>
#include <iostream>

#include "RandomNumberGenerator.hpp"
#include "GamePiece.hpp"
#include "GamePieceStack.hpp"
#include "HiveMove.hpp"
#include "AxialPosition.hpp"
#include "PieceType.hpp"

namespace Hive {
    class Board {
    private:
        std::unordered_map<int, Piece::GamePieceStack> gamePieceStacks;
        //std::vector<Piece::GamingPiece> pieces;

    public:
        Board();
        void PerformMove(Move::HiveMove& move);

        bool GamePieceStackExists(const AxialPosition& coordinate) const;
        bool GamePieceStackExists(int x, int y) const;

        Piece::GamePieceStack& GetGamePieceStack(const AxialPosition& position) const;
        Piece::GamePieceStack& GetGamePieceStack(int x, int y) const;

        std::vector<Piece::GamePieceStack>& GetGamePieceStacks() const;

        Piece::GamePiece& GetGamePiece(const AxialPosition& position, int layer) const;
        Piece::GamePiece& GetGamePiece(int x, int y, int layer) const;

        std::vector<Piece::GamePieceStack> GetNeighbouringGamePieceStacks(const AxialPosition& position) const;
        std::vector<AxialPosition> GetNeighbouringEmptyAxialPositions(const AxialPosition& position) const;

        void AddGamePieceOnTop(Piece::GamePiece& gamePiece, AxialPosition& position);
        void RemoveUpmostGamePiece(AxialPosition& position);

        bool IsAxialPositionAtBorderOfBoard(AxialPosition& position) const;
        bool IsAxialPositionOnBoard(AxialPosition& position) const;

        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard() const;

    private:
        void PlaceObstacles();
    };
}  // namespace Hive