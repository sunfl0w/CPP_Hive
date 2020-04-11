#pragma once

#include <algorithm>
#include <vector>

#include "board.hpp"
#include "move.hpp"
#include "player.hpp"

namespace Hive {
    /**
     * @brief This class represents a game state.
     * 
     */
    class GameState {
    private:
        /**
         * @brief The current turn of the GameState.
         * 
         */
        unsigned int turn;

        /**
         * @brief The underlying Board of the GameState.
         * 
         */
        Board board;

        /**
         * @brief The current Player of the GameState.
         * 
         */
        Player redPlayer;

        /**
         * @brief The pausing Player of the GameState.
         * 
         */
        Player bluePlayer;

        Color currentPlayerColor;

        /**
         * @brief The Moves that were performed on this GameState previously.
         * 
         */
        std::vector<Move> performedMoves;

    public:
        /**
         * @brief Constructs a new GameState with the turn set to zero.
         * 
         */
        GameState();

        /**
         * @brief Creates a deep copy of the given GameState.
         * 
         * @param gameState The GameState to deep copy.
         */
        GameState(const GameState& gameState);

        /**
         * @brief Gets the current turn.
         * 
         * @return The current turn.
         */
        unsigned int GetTurn() const;

        /**
         * @brief Sets the current turn.
         * 
         * @param turn The turn to set the GameState's turn to.
         */
        void SetTurn(unsigned int turn);

        /**
         * @brief Gets the last performed Move that was performed on the GameState.
         * 
         * @return The last performed Move by reference.
         */
        Move& GetLastPerformedMove();

        /**
         * @brief Gets the underlying Board of the GameState.
         * 
         * @return The underlying Board by reference.
         */
        Board& GetBoard();

        /**
         * @brief Gets a Player by Color.
         * 
         * @param color The Color the searched Player has.
         * @return The Player with the given Color by reference.
         */
        Player& GetPlayer(Color color);

        /**
         * @brief Gets the current Player.
         * 
         * @return The current Player by reference.
         */
        Player& GetCurrentPlayer();

        /**
         * @brief Sets the current Player.
         * 
         * @param player The Player the current Player should be set to.
         */
        void SetCurrentPlayerColor(Color color);

        /**
         * @brief Gets the paused Player.
         * 
         * @return The paused Player by reference.
         */
        Player& GetPausedPlayer();

        /**
         * @brief Gets the Moves that could be performed on the GameState.
         * 
         * @return The valid Moves that could be perfomed on the GameState in a vector.
         */
        std::vector<Move> GetPossibleMoves();

        /**
         * @brief Performs a Move on the GameState. THIS DOES NOT CHECK THE MOVES VALIDITY FOR PERFORMANCE REASONS, YOU WERE WARNED!
         * 
         * @param move The Move to perform.
         */
        void PerformMove(const Move& move);

        /**
         * @brief Reverts that Move that was last performed.
         * 
         */
        void UndoLastMove();

        /**
         * @brief Gets all valid deploy Moves for the GameState.
         * 
         * @return All valid deploy Moves in a vector.
         */
        std::vector<Move> GetPossibleDeployMoves();

        /**
         * @brief Gets all possible deploy Moves for the QueenBee of the current Player.
         * 
         * @return All valid QueenBee deploy Moves in a vector.
         */
        std::vector<Move> GetPossibleQueenBeeDeployMoves();

        /**
         * @brief Gets all possible drag Moves for the GameState.
         * 
         * @return All valid drag Moves in a vector.
         */
        std::vector<Move> GetPossibleDragMoves();

        /**
         * @brief Gets all valid QueenBee drag Moves.
         * 
         * @return All valid QueenBee drag Moves in a vector.
         */
        std::vector<Move> GetPossibleQueenBeeDragMoves();

         /**
         * @brief Gets all valid Spider drag Moves.
         * 
         * @return All valid Spider drag Moves in a vector.
         */
        std::vector<Move> GetPossibleSpiderDragMoves();

         /**
         * @brief Gets all valid Beetle drag Moves.
         * 
         * @return All valid Beetle drag Moves in a vector.
         */
        std::vector<Move> GetPossibleBeetleDragMoves();

         /**
         * @brief Gets all valid Grasshopper drag Moves.
         * 
         * @return All valid Grasshopper drag Moves in a vector.
         */
        std::vector<Move> GetPossibleGrasshopperDragMoves();

         /**
         * @brief Gets all valid Ant drag Moves.
         * 
         * @return All valid Ant drag Moves in a vector.
         */
        std::vector<Move> GetPossibleAntDragMoves();

        /**
         * @brief Checks whether the GameState is terminal. This means whether the game is over.
         * 
         * @return true If the GameState is terminal.
         * @return false If the GameState is not terminal.
         */
        bool IsGameOver();

    private:
        /**
         * @brief Gets all deployable Positions of the GameState.
         * 
         * @return All deployable Positions of the GameState in a vector.
         */
        std::vector<AxialPosition> GetDeployablePositions();

        /**
         * @brief Checks whether the QueenBee is blocked.
         * 
         * @param color The Color of the QueenBee to check.
         * @return true If the QueenBee is blocked.
         * @return false If the QueenBee is not blocked.
         */
        bool IsQueenBeeBlocked(Color color);
    };
}  // namespace Hive