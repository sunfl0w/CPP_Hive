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

        std::vector<Move> possibleQueenBeeDragMoves = GetPossibleQueenBeeDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleQueenBeeDragMoves.begin(), possibleQueenBeeDragMoves.end());
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDragMoves() const {
        std::vector<Move> possibleQueenBeeDragMoves;
        PieceStack queenBeeOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::QueenBee)[0];
        std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(queenBeeOfCurrentPlayer.GetAxialPosition());

        for (AxialPosition emptyNeighbouringPosition : emptyNeighbouringPositions) {
            if (board.CanSlide(queenBeeOfCurrentPlayer.GetAxialPosition(), emptyNeighbouringPosition)) {
                possibleQueenBeeDragMoves.push_back(Move(MoveType::DragMove, queenBeeOfCurrentPlayer.GetAxialPosition(), emptyNeighbouringPosition));
            }
        }
        return possibleQueenBeeDragMoves;
    }

    std::vector<Move> GameState::GetPossibleSpiderDragMoves() const {
        std::vector<Move> possibleSpiderDragMoves;
        std::vector<PieceStack> spidersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::Spider);
        for (PieceStack spider : spidersOfCurrentPlayer) {
            SlidePathNode startNode = SlidePathNode(spider.GetAxialPosition());
            std::vector<SlidePathNode*> currentSlidePathNodes;
            currentSlidePathNodes.push_back(&startNode);
            for (int i = 0; i < 3; i++) {
                std::vector<SlidePathNode*> newSlidePathNodes;
                for (SlidePathNode* currentSlidePathNode : currentSlidePathNodes) {
                    std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(currentSlidePathNode->GetPosition());
                    for (AxialPosition emptyNeighbouringPosition : emptyNeighbouringPositions) {
                        if (board.CanSlide(currentSlidePathNode->GetPosition(), emptyNeighbouringPosition)) {
                            if (i >= 1) {
                                if (currentSlidePathNode->GetParent()->GetPosition() != emptyNeighbouringPosition) {
                                    newSlidePathNodes.push_back(&SlidePathNode(emptyNeighbouringPosition));
                                }
                            } else {
                                newSlidePathNodes.push_back(&SlidePathNode(emptyNeighbouringPosition));
                            }
                        }
                    }
                }
                currentSlidePathNodes = newSlidePathNodes;
            }
            for (SlidePathNode* validEndNodes : currentSlidePathNodes) {
                possibleSpiderDragMoves.push_back(Move(MoveType::DragMove, spider.GetAxialPosition(), validEndNodes->GetPosition()));
            }
        }
        return possibleSpiderDragMoves;
    }

    std::vector<Move> GameState::GetPossibleBeetleDragMoves() const {
        std::vector<Move> possibleBeetleDragMoves;
        std::vector<PieceStack> beetlesOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::Beetle);
        for (PieceStack beetle : beetlesOfCurrentPlayer) {
            std::vector<AxialPosition> neighbouringPositions = beetle.GetAxialPosition().GetNeighbouringPositions();

            for (AxialPosition neighbouringPosition : neighbouringPositions) {
                if (board.PieceStackExists(neighbouringPosition)) {
                    possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, beetle.GetAxialPosition(), neighbouringPosition));
                } else {
                    if (board.CanSlide(beetle.GetAxialPosition(), neighbouringPosition)) {
                        possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, beetle.GetAxialPosition(), neighbouringPosition));
                    }
                }
            }
        }
        return possibleBeetleDragMoves;
    }

    std::vector<Move> GameState::GetPossibleGrasshopperDragMoves() const {
        std::vector<Move> possibleBeetleDragMoves;
        std::vector<PieceStack> grasshoppersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetPlayerColor(), PieceType::Beetle);
        for (PieceStack grasshopper : grasshoppersOfCurrentPlayer) {

        }
    }

}  // namespace Hive