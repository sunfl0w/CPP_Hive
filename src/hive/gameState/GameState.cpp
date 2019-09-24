#include "GameState.hpp"

namespace Hive {
    GameState::GameState() : currentPlayer(Player::PlayerColor::Red), pausedPlayer(Player::PlayerColor::Blue) {
        turn = 0;
    }

    GameState::GameState(GameState& gameState) : board(gameState.board), currentPlayer(gameState.GetCurrentPlayer()), pausedPlayer(gameState.GetPausedPlayer()), performedMoves(gameState.performedMoves) {
        turn = gameState.turn;
    }

    const Player::HivePlayer& GameState::GetCurrentPlayer() const {
        return currentPlayer;
    }

    const Player::HivePlayer& GameState::GetPausedPlayer() const {
        return pausedPlayer;
    }

    const std::vector<Move> GameState::GetPossibleMoves() const {
        
    }

    const bool GameState::IsMoveValid(const Move& move) const {

    }
}  // namespace Hive