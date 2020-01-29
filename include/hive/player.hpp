#pragma once

#include <vector>

#include "color.hpp"
#include "piece.hpp"

namespace Hive {
    /**
     * @brief This class represents a player. Unlike the Java implementation this is not so bloated, but responsible for managing the Pieces that were not played yet.
     * 
     */
    class Player {
    private:
        /**
         * @brief The Color of the player.
         * 
         */
        Color color;

        /**
         * @brief The undeployed Pieces of this Player.
         * 
         */
        std::vector<Piece> undeployedPieces;
    public:
        /**
         * @brief Constructs a new and empty Player.
         * 
         */
        Player();

        /**
         * @brief Constructs a new Player without undeployed Pieces, but with a color.
         * 
         * @param color 
         */
        Player(Color color);

        /**
         * @brief Gets the Color of the Player.
         * 
         * @return Color The Color of the Player.
         */
        Color GetColor() const;

        /**
         * @brief Sets the Color of the Player.
         * 
         * @param color The Color that the Player should have.
         */
        void SetColor(Color color);

        /**
         * @brief Gets the undeployed Pieces of the Player.
         * 
         * @return The Pieces that are undeployed in a vector reference.
         */
        const std::vector<Piece>& GetUndeployedPieces() const;

        /**
         * @brief Adds a new undeployed Piece to the Player.
         * 
         * @param piece The Piece to add.
         */
        void AddUndeployedPiece(Piece piece);

        /**
         * @brief Removes an undeployed Piece from the Player by PieceType.
         * 
         * @param type The PieceType that controls which Piece should be removed.
         */
        void RemoveUndeployedPiece(PieceType type);

        /**
         * @brief Initialized the undeployed Pieces of this Player according to the games rules. Use only when you know what you are doing.
         * 
         */
        void InitializeUndeployedPieces();
    };
}  // namespace Hive::Player