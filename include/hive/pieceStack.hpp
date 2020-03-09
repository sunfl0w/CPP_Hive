#pragma once

#include <vector>

#include "axialPosition.hpp"
#include "piece.hpp"

namespace Hive {
    /**
     * @brief This class represents a Stack of Pieces.
     * 
     */
    class PieceStack {
    private:
        /**
         * @brief The position of the PieceStack.
         * 
         */
        AxialPosition position;

        /**
         * @brief The Pieces in the PieceStack.
         * 
         */
        std::vector<Piece> pieces;

    public:
        /**
         * @brief Constructs a new and empty PieceStack.
         * 
         */
        PieceStack();

        /**
         * @brief Constructs a deep copy of a given PieceStack.
         * 
         * @param pieceStack The PieceStack to copy.
         */
        PieceStack(const PieceStack& pieceStack);

        /**
         * @brief Constructs a new and empty PieceStack with a given Position.
         * 
         * @param position The Position the PieceStack should be at.
         */
        PieceStack(const AxialPosition& position);

        /**
         * @brief Compares two PieceStacks for Equality.
         * 
         * @param pieceStack The PieceStack to compare against.
         * @return true If the PieceStacks are at the same Position.
         * @return false If the PieceStacks are not at the same Position.
         */
        bool operator==(const PieceStack& pieceStack) const;

        /**
         * @brief Checks whether a PieceStack is empty.
         * 
         * @return true If the PieceStack is empty.
         * @return false If the PieceStack is not empty.
         */
        bool IsStackEmpty() const;

        /**
         * @brief Gets the Position of the PieceStack.
         * 
         * @return The Position of the PieceStack as a reference.
         */
        AxialPosition& GetAxialPosition();

        /**
         * @brief Adds a new Piece on top of the PieceStack.
         * 
         * @param piece The Piece to add on top.
         */
        void AddPieceOnTop(const Piece& piece);

        /**
         * @brief Removes the Piece on top of the PieceStack.
         * 
         */
        void RemovePieceOnTop();

        /**
         * @brief Gets a Piece of the PieceStack by layer.
         * 
         * @param layer The layer to get the Piece from. 0 would get the Piece at the bottom of the PieceStack.
         * @return The Piece in the given layer as a reference.
         */
        Piece& GetPieceByLayer(int layer);

        /**
         * @brief Gets the Piece on top of the PieceStack.
         * 
         * @return The Piece on top of the PieceStack as a reference.
         */
        Piece& GetPieceOnTop();

        /**
         * @brief Gets the Pieces of the PieceStack.
         * 
         * @return A vector of the Pieces of the PieceStack.
         */
        std::vector<Piece>& GetPieces();

        /**
         * @brief Sets the Pieces of the PieceStack.
         * 
         * @param pieces The vector of Pieces that should replace the ones of the PieceStack.
         */
        void SetPieces(std::vector<Piece> pieces);
    };
}  // namespace Hive