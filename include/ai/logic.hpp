#pragma once

#include <vector>
#include <random>
#include <iostream>

#include "gameState.hpp"
#include "move.hpp"
#include "player.hpp"
#include "color.hpp"

namespace AI {
    /**
     * @brief This class defines some virtual methods for creating AIs for the game of Hive.
     * 
     */
    class Logic {
    public:
        /**
         * @brief Constructs a new Logic.
         * 
         */
        Logic();

        /**
         * @brief Destroys a Logic.
         * 
         */
        virtual ~Logic();

        /**
         * @brief Gets the next Move to play. In this method the AI hast to be implemented.
         * 
         * @param currentGameState The GameState to get the next Move for.
         * @param ownPlayerColor The Color of the Player that is played by the AI.
         * @return The next move that should be played.
         */
        virtual Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);

        /**
         * @brief Will be executed when a game of Hive ends.
         * 
         * @param colorOfWinningPlayer The Color of the Player that won.
         */
        virtual void OnGameEnd(Hive::Color colorOfWinningPlayer);
    };
} // namespace Piranhas::Logic