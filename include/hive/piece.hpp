#pragma once

#include "color.hpp"
#include "pieceType.hpp"

namespace Hive {
    /**
     * @brief This class represents a Piece.
     * 
     */
    class Piece {
    private:
        /**
         * @brief The PieceType of this Piece.
         * 
         */
        PieceType type;

        /**
         * @brief The Color of this Piece.
         * 
         */
        Color color;

    public:
        /**
         * @brief Constructs a new and empty Piece.
         * 
         */
        Piece();

        /**
         * @brief Creates a deep copy of the given Piece.
         * 
         * @param piece The Piece to deep copy.
         */
        Piece(const Piece& piece);

        /**
         * @brief Constructs a new Piece with a PieceType and a Color.
         * 
         * @param pieceType The PieceType the Piece should have.
         * @param pieceColor The Color the Piece should have.
         */
        Piece(const PieceType& pieceType, const Color& pieceColor);

        /**
         * @brief Gets the PieceType of the Piece.
         * 
         * @return PieceType The PieceType of the Piece.
         */
        PieceType GetType() const;

        /**
         * @brief Sets the PieceType of the Piece.
         * 
         * @param pieceType The PieceType the Piece should have.
         */
        void SetType(PieceType pieceType);

        /**
         * @brief Gets the Color of the Piece.
         * 
         * @return Color The Color of the Piece.
         */
        Color GetColor() const;
    };
}  // namespace Hive::Piece