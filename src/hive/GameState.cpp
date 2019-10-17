#include "GameState.hpp"

namespace Hive {
    GameState::GameState() : currentPlayer(PlayerColor::Red), pausedPlayer(PlayerColor::Blue) {
        turn = 0;
    }

    GameState::GameState(GameState& gameState) : board(gameState.board), currentPlayer(gameState.GetCurrentPlayer()), pausedPlayer(gameState.GetPausedPlayer()), performedMoves(gameState.performedMoves) {
        turn = gameState.turn;
    }

    const Player& GameState::GetCurrentPlayer() const {
        return currentPlayer;
    }

    const Player& GameState::GetPausedPlayer() const {
        return pausedPlayer;
    }

    std::vector<Move> GameState::GetPossibleMoves() const {
    }

    bool GameState::IsMoveValid(const Move& move) const {
    }

    //Private

    std::vector<Move> GameState::GetPossibleDeployMoves() const {
        std::vector<Move> possibleDeployMoves;

        if (turn == 0) {
            std::vector<AxialPosition> emptyAxialPositions = board.GetEmptyAxialPositionsOnBoard();
            for (Piece undeployedPiece : currentPlayer.GetUndeployedGamePieces()) {
                for (AxialPosition emptyAxialPosition : emptyAxialPositions) {
                    possibleDeployMoves.push_back(Move(MoveType::DeployMove, AxialPosition(0, 0), emptyAxialPosition));
                }
            }
        } else if (turn == 1) {
            std::vector<PieceStack> pieceStacks = board.GetPieceStacks();
            std::vector<AxialPosition> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(pieceStacks[0].GetAxialPosition());

            for (Piece undeployedPiece : currentPlayer.GetUndeployedGamePieces()) {
                for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
                    possibleDeployMoves.push_back(Move(MoveType::DeployMove, AxialPosition(0, 0), neighbouringEmptyPosition));
                }
            }
        } else {
            std::vector<AxialPosition> deployablePositions;

            std::vector<PieceStack> pieceStacksOfCurrentPlayer = board.GetPieceStacksByColor(currentPlayer.GetPlayerColor());
            for (PieceStack gameSpieceStack : pieceStacksOfCurrentPlayer) {
                std::vector<AxialPosition> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(gameSpieceStack.GetAxialPosition());
                for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
                    std::vector<PieceStack> neighbouringStacks = board.GetNeighbouringPieceStacks(neighbouringEmptyPosition);
                    bool enemyStackNeighbouring = false;
                    for (PieceStack neighbouringStack : neighbouringStacks) {
                        if (neighbouringStack.GetPieceOnTop().GetCorrespondingPlayerColor() != currentPlayer.GetPlayerColor()) {
                            enemyStackNeighbouring = true;
                            break;
                        }
                    }
                    if (!enemyStackNeighbouring && std::find(deployablePositions.begin(), deployablePositions.end(), neighbouringEmptyPosition) == deployablePositions.end()) {
                        deployablePositions.push_back(neighbouringEmptyPosition);
                    }
                }
            }

            for (AxialPosition deployablePosition : deployablePositions) {
                possibleDeployMoves.push_back(Move(MoveType::DeployMove, AxialPosition(0, 0), deployablePosition));
            }
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleDragMoves() const {
        std::vector<Move> possibleDragMoves;
        std::vector<SlidePath> slidePaths = board.GetSlidePaths();

        std::vector<Move> possibleQueenBeeDragMoves = GetPossibleQueenBeeDragMoves(slidePaths);
        possibleDragMoves.insert(possibleDragMoves.end(), possibleQueenBeeDragMoves.begin(), possibleQueenBeeDragMoves.end());
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDragMoves(const std::vector<SlidePath>& slidePaths) const {
        std::vector<Move> possibleQueenBeeDragMoves;
        PieceStack moveableQueenBeeOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::QueenBee)[0];
        if (board.IsHiveCoherentIfPieceMovesFromPosition(moveableQueenBeeOfCurrentPlayer.GetAxialPosition())) {
            std::vector<SlidePath> availableSlidePaths;
            for (SlidePath slidePath : slidePaths) {
                if (slidePath.IsValidForPiece(moveableQueenBeeOfCurrentPlayer.GetAxialPosition(), board)) {
                    availableSlidePaths.push_back(slidePath);
                }
            }

            for (SlidePath slidePath : availableSlidePaths) {
                for (AxialPosition slidePathPosition : slidePath.GetContainingPositions()) {
                    if (slidePathPosition.IsNeighbourTo(moveableQueenBeeOfCurrentPlayer.GetAxialPosition())) {
                        possibleQueenBeeDragMoves.push_back(Move(MoveType::DragMove, moveableQueenBeeOfCurrentPlayer.GetAxialPosition(), slidePathPosition));
                    }
                }
            }
        }

        return possibleQueenBeeDragMoves;
    }

    std::vector<Move> GameState::GetPossibleSpiderDragMoves(const std::vector<SlidePath>& slidePaths) const {
        std::vector<Move> possibleSpiderDragMoves;
        std::vector<PieceStack> spidersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::QueenBee);
        for (PieceStack spider : spidersOfCurrentPlayer) {
            if (board.IsHiveCoherentIfPieceMovesFromPosition(spider.GetAxialPosition())) {
                std::vector<SlidePath> availableSlidePaths;
                for (SlidePath slidePath : slidePaths) {
                    if (slidePath.IsValidForPiece(spider.GetAxialPosition(), board)) {
                        availableSlidePaths.push_back(slidePath);
                    }
                }
                
                for (SlidePath slidePath : availableSlidePaths) {
                    for (AxialPosition slidePathPosition : slidePath.GetContainingPositions()) {
                        if (slidePathPosition.IsNeighbourTo(spider.GetAxialPosition())) {
                            possibleSpiderDragMoves.push_back(Move(MoveType::DragMove, spider.GetAxialPosition(), slidePathPosition));
                        }
                    }
                }
            }
        }
        return possibleSpiderDragMoves;
    }
}  // namespace Hive