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

        bool GamePieceStackExistsAtPosition(const AxialPosition& coordinate) const;
        bool GamePieceStackExistsAtPosition(int x, int y) const;

        Piece::GamePieceStack& GetGamePieceStackAtPosition(AxialPosition& position);
        Piece::GamePieceStack& GetGamePieceStackAtPosition(int x, int y);

        Piece::GamePiece& GetGamePieceAtPositionAndLayer(AxialPosition& position, int layer);
        Piece::GamePiece& GetGamePieceAtPositionAndLayer(int x, int y, int layer);

        std::vector<Piece::GamePieceStack> GetNeighbouringGamePieceStacksAtPosition(AxialPosition& position);

        void AddGamePieceOnTopAtPosition(Piece::GamePiece& gamePiece, AxialPosition& position);
        void RemoveUpmostGamePieceAtPosition(AxialPosition& position);

        bool IsAxialPositionAtBorderOfBoard(AxialPosition& position) const;
        bool IsAxialPositionOnBoard(AxialPosition& position) const;

        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard() const;

    private:
        void PlaceObstacles();
    };
}  // namespace Hive