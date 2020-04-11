#pragma once

#include <vector>
#include <algorithm>

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
        std::vector<int> undeployedPieceCounts;
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
         * @brief Gets the undeployed Pieces of the Player. At position 0 int he vector the amount of QueenBees are stored. For reference look at PieceType.
         * 
         * @return The PieceType amounts that are undeployed in a vector reference.
         */
        const std::vector<int>& GetUndeployedPieceTypeCounts() const;

        /**
         * @brief Adds a new undeployed PieceType to the Player.
         * 
         * @param piece The PieceType to add.
         */
        void AddUndeployedPieceType(PieceType type);

        /**
         * @brief Removes an undeployed PieceType from the Player by PieceType.
         * 
         * @param type The PieceType that controls which Piece should be removed.
         */
        void RemoveUndeployedPieceType(PieceType type);

        /**
         * @brief Initialized the undeployed Pieces of this Player according to the games rules. Use only when you know what you are doing.
         * 
         */
        void InitializeUndeployedPieces();
    };
}  // namespace Hive::Player