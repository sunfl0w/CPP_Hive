#pragma once

#include <algorithm>
#include <array>
#include <deque>
#include <iostream>
#include <random>
#include <vector>

#include "axialPosition.hpp"
#include "color.hpp"
#include "globals.hpp"
#include "move.hpp"
#include "piece.hpp"
#include "pieceStack.hpp"
#include "pieceType.hpp"

namespace Hive {
    /**
     * @brief This class represents the physical board of the game Hive.
     * 
     */
    class Board {
    private:
        /**
         * @brief The PieceStacks of the board. Some of the Stacks are actually not on the Board as the board only consists of 91 tiles. Empty PieceStacks are treated as not existent.
         * 
         */
        std::array<PieceStack, 121> pieceStacks;

    public:
        /**
         * @brief Constructs a new and empty Board.
         * 
         */
        Board();

        /**
         * @brief Creates a deep copy of a given Board.
         * 
         * @param board The Board to deep copy.
         */
        Board(const Board& board);

        /**
         * @brief Checks whether a PiceStack exists at a given Position.
         * 
         * @param position The position to check.
         * @return true When a PieceStacks exists at the given position.
         * @return false When no PieceStacks exists at the given position.
         */
        bool PieceStackExists(const AxialPosition& position);

        /**
         * @brief Checks whether a PiceStack exists at a given Position.
         * 
         * @param x The x-coordinate of the position to check.
         * @param y The y-coordinate of the position to check.
         * @return true When a PieceStacks exists at the given position.
         * @return false When no PieceStacks exists at the given position.
         */
        bool PieceStackExists(int x, int y);

        /**
         * @brief Gets a PieceStack at a given Position.
         * 
         * @param position The position to get the PieceStack from.
         * @return PieceStack& A reference to the PieceStack. This might also be empty when there is no PieceStack at the given position.
         */
        PieceStack& GetPieceStack(const AxialPosition& position);

        /**
         * @brief Gets a PieceStack at a given position.
         * 
         * @param x The x-coordinate of the position to get the PieceStack from.
         * @param y The y-coordinate of the position to get the PieceStack from.
         * @return PieceStack& A reference to the PieceStack. This might also be empty when there is no PieceStack at the given position.
         */
        PieceStack& GetPieceStack(int x, int y);

        /**
         * @brief Gets all PieceStacks on the board.
         * 
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetPieceStacks();

        /**
         * @brief Gets all PieceStacks on the board except obstacles. Only the upmost Piece counts.
         * 
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetPieceStacksWithoutObstacles();

        /**
         * @brief Gets all PieceStacks on the board by a Color. Only the upmost Piece counts.
         * 
         * @param color The Color used to filter the PieceStacks.
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetPieceStacksByColor(Color color);

        /**
         * @brief Gets all PieceStacks on the board by a Color and PieceType. Only the upmost Piece counts.
         * 
         * @param color The Color used to filter the PieceStacks.
         * @param pieceType The PieceType used to filter the PieceStacks.
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetPieceStacksByColorAndType(Color color, PieceType pieceType);

        /**
         * @brief Get the Piece Stacks Containing Piece By Color And Type. All Pieces in a PieceStack will be evaluated.
         * 
         * @param color The Color used to filter the PieceStacks.
         * @param pieceType The PieceType used to filter the PieceStacks.
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetPieceStacksContainingPieceByColorAndType(Color color, PieceType pieceType);

        /**
         * @brief Gets the neighbouring PieceStacks of a given Position.
         * 
         * @param position The Position to get the neighbouring PieceStacks from.
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetNeighbouringPieceStacks(const AxialPosition& position);

        /**
         * @brief Gets the neighbouring PieceStacks of a given Position except obstacles.
         * 
         * @param position The Position to get the neighbouring PieceStacks from.
         * @return A vector of pointers to PieceStacks.
         */
        std::vector<PieceStack*> GetNeighbouringPieceStacksExceptObstacles(const AxialPosition& position);

        /**
         * @brief Gets the empty neighbouring Positions of a given Position.
         * 
         * @param position The Position to get the empty neighbouring Positions from.
         * @return A vector of pointers to Positions.
         */
        std::vector<AxialPosition*> GetEmptyNeighbouringAxialPositions(const AxialPosition& position);

        /**
         * @brief Gets the empty neighbouring Positions of a given Position that can be slided on by a moving Piece that starts its move from the given Position.
         * 
         * @param position The Position to get the empty and slideable neighbouring Positions from.
         * @return A vector of pointers to Positions.
         */
        std::vector<AxialPosition*> GetEmptySlideableNeighbouringAxialPositions(const AxialPosition& position);

        /**
         * @brief Gets the empty neighbouring Positions of a given Position that can be slided on by a moving Piece that starts its move from the given Position. It ignores specified Positions.
         * 
         * @param position The Position to get the empty and slideable neighbouring Positions from that were not filtered out.
         * @param ignoredPositions The vector Positions to ignore.
         * @return A vector of pointers to Positions.
         */
        std::vector<AxialPosition*> GetEmptySlideableNeighbouringAxialPositionsExcept(const AxialPosition& position, const std::vector<AxialPosition>& ignoredPositions);

        /**
         * @brief Adds a Piece on top of a PieceStack or an empty Position.
         * 
         * @param piece The Piece to add on top.
         * @param position The position to add the Piece on top to.
         */
        void AddPieceOnTop(const Piece& piece, const AxialPosition& position);

        /**
         * @brief Removes a Piece on top of a PieceStack.
         * 
         * @param position The position to remove the Piece on top of.
         */
        void RemoveUpmostPiece(const AxialPosition& position);

        /**
         * @brief Gets all Positions that are empty.
         * 
         * @return A vector of Positions.
         */
        std::vector<AxialPosition> GetEmptyAxialPositionsOnBoard();

        /**
         * @brief Checks whether a Hive is coherent (all Pieces are connected) if a Piece moves from the given position.
         * 
         * @param position The Position to check coherency for.
         * @return true If the Hive would be coherent of a Piece moves from the given Position.
         * @return false If the Hive would not be coherent of a Piece moves from the given Position.
         */
        bool IsHiveCoherentIfPieceMovesFromPosition(const AxialPosition& position);

        /**
         * @brief Checks whether a Piece could slide from one Position to the other.
         * 
         * @param slideStartPos The starting Position of the slide.
         * @param slideEndPos The terminating Position of the slide.
         * @return true When a slide is possible.
         * @return false When a slide is not possible.
         */
        bool CanSlide(const AxialPosition& slideStartPos, const AxialPosition& slideEndPos);

        /**
         * @brief Places random obstacles on the board according to the rules of the game. Use thsi only when you know what you are doing.
         * 
         */
        void PlaceObstacles();
    };
}  // namespace Hive