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

    std::vector<Move::HiveMove> GameState::GetPossibleMoves() const {
    }

    bool GameState::IsMoveValid(const Move::HiveMove& move) const {
    }

    //Private

    std::vector<Move::HiveMove> GameState::GetPossibleDeployMoves() const {
        std::vector<Move::HiveMove> possibleDeployMoves;

        if (turn == 0) {
            std::vector<AxialPosition> emptyAxialPositions = board.GetEmptyAxialPositionsOnBoard();
            for (Piece::GamePiece undeployedGamePiece : currentPlayer.GetUndeployedGamePieces()) {
                for (AxialPosition emptyAxialPosition : emptyAxialPositions) {
                    possibleDeployMoves.push_back(Move::HiveMove(Move::MoveType::DeployMove, AxialPosition(0, 0), emptyAxialPosition));
                }
            }
        } else if (turn == 1) {
            std::vector<Piece::GamePieceStack> gameSpieceStacks = board.GetGamePieceStacks();
            std::vector<AxialPosition> neighbouringEmptyPositions = board.GetNeighbouringEmptyAxialPositions(gameSpieceStacks[0].GetAxialPosition);

            for (Piece::GamePiece undeployedGamePiece : currentPlayer.GetUndeployedGamePieces()) {
                for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
                    possibleDeployMoves.push_back(Move::HiveMove(Move::MoveType::DeployMove, AxialPosition(0, 0), neighbouringEmptyPosition));
                }
            }
        } else {
            
        }

        return possibleDeployMoves;
    }
}  // namespace Hive