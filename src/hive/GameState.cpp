#include "GameState.hpp"

namespace Hive {
    GameState::GameState() : currentPlayer(Color::Red), pausedPlayer(Color::Blue) {
        turn = 0;
    }

    GameState::GameState(GameState& gameState) : board(gameState.board), currentPlayer(gameState.GetCurrentPlayer()), pausedPlayer(gameState.GetPausedPlayer()), performedMoves(gameState.performedMoves) {
        turn = gameState.turn;
    }

    Board& GameState::GetBoard() {
        return board;
    }

    Player& GameState::GetCurrentPlayer() {
        return currentPlayer;
    }

    Player& GameState::GetPausedPlayer() {
        return pausedPlayer;
    }

    std::vector<Move> GameState::GetPossibleMoves() const {
        std::vector<Move> possibleMoves;

        std::vector<PieceStack> pieceStacksOnBoard = board.GetPieceStacks();

        bool isQueenBeeOfCurrentPlayerOnBoard = false;
        for (PieceStack pieceStack : pieceStacksOnBoard) {
            for (Piece piece : pieceStack.GetPieces()) {
                if (piece.GetType() == PieceType::QueenBee && piece.GetColor() == currentPlayer.GetColor()) {
                    isQueenBeeOfCurrentPlayerOnBoard = true;
                }
            }
        }

        if (!isQueenBeeOfCurrentPlayerOnBoard) {
            if (turn > 5) {
                possibleMoves = GetPossibleQueenBeeDeployMoves();
            } else {
                possibleMoves = GetPossibleDeployMoves();
            }
        } else {
            std::vector<Move> possibleDepolyMoves = GetPossibleDeployMoves();
            possibleMoves.insert(possibleMoves.end(), possibleDepolyMoves.begin(), possibleDepolyMoves.end());

            std::vector<Move> possibleDragMoves = GetPossibleDragMoves();
            possibleMoves.insert(possibleMoves.end(), possibleDragMoves.begin(), possibleDragMoves.end());
        }

        if (possibleMoves.empty()) {
            possibleMoves.push_back(Move(MoveType::PassMove, AxialPosition(0,0), AxialPosition(0,0), PieceType::Obstacle));
        }

        return possibleMoves;
    }

    bool GameState::IsMoveValid(const Move& move) const {
    }

    //Private

    std::vector<Move> GameState::GetPossibleDeployMoves() const {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            for (Piece piece : currentPlayer.GetUndeployedPieces()) {
                possibleDeployMoves.push_back(Move(MoveType::DeployMove, AxialPosition(0, 0), deployablePosition, piece.GetType()));
            }
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDeployMoves() const {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            possibleDeployMoves.push_back(Move(MoveType::DeployMove, AxialPosition(0, 0), deployablePosition, PieceType::QueenBee));
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleDragMoves() const {
        std::vector<Move> possibleDragMoves;

        std::vector<Move> possibleQueenBeeDragMoves = GetPossibleQueenBeeDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleQueenBeeDragMoves.begin(), possibleQueenBeeDragMoves.end());

        std::vector<Move> possibleSpiderDragMoves = GetPossibleSpiderDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleSpiderDragMoves.begin(), possibleSpiderDragMoves.end());

        std::vector<Move> possibleBeetleDragMoves = GetPossibleBeetleDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleBeetleDragMoves.begin(), possibleBeetleDragMoves.end());

        std::vector<Move> possibleGrasshopperDragMoves = GetPossibleGrasshopperDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleGrasshopperDragMoves.begin(), possibleGrasshopperDragMoves.end());

        std::vector<Move> possibleAntDragMoves = GetPossibleAntDragMoves();
        possibleDragMoves.insert(possibleDragMoves.end(), possibleAntDragMoves.begin(), possibleAntDragMoves.end());

        return possibleDragMoves;
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDragMoves() const {
        std::vector<Move> possibleQueenBeeDragMoves;
        PieceStack queenBeeOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::QueenBee)[0];
        std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(queenBeeOfCurrentPlayer.GetAxialPosition());

        for (AxialPosition emptyNeighbouringPosition : emptyNeighbouringPositions) {
            if (board.CanSlide(queenBeeOfCurrentPlayer.GetAxialPosition(), emptyNeighbouringPosition)) {
                possibleQueenBeeDragMoves.push_back(Move(MoveType::DragMove, queenBeeOfCurrentPlayer.GetAxialPosition(), emptyNeighbouringPosition, PieceType::QueenBee));
            }
        }
        return possibleQueenBeeDragMoves;
    }

    std::vector<Move> GameState::GetPossibleSpiderDragMoves() const {
        std::vector<Move> possibleSpiderDragMoves;
        std::vector<PieceStack> spidersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Spider);
        for (PieceStack spider : spidersOfCurrentPlayer) {
            SlidePathNode startNode = SlidePathNode(spider.GetAxialPosition());
            std::vector<SlidePathNode> currentSlidePathNodes;
            currentSlidePathNodes.push_back(startNode);
            for (int i = 0; i < 3; i++) {
                std::vector<SlidePathNode> newSlidePathNodes;
                for (SlidePathNode currentSlidePathNode : currentSlidePathNodes) {
                    std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(currentSlidePathNode.GetPosition());
                    for (AxialPosition emptyNeighbouringPosition : emptyNeighbouringPositions) {
                        if (board.CanSlide(currentSlidePathNode.GetPosition(), emptyNeighbouringPosition)) {
                            if (i >= 1) {
                                if (currentSlidePathNode.GetParent()->GetPosition() != emptyNeighbouringPosition) {
                                    newSlidePathNodes.push_back(SlidePathNode(emptyNeighbouringPosition));
                                }
                            } else {
                                newSlidePathNodes.push_back(SlidePathNode(emptyNeighbouringPosition));
                            }
                        }
                    }
                }
                currentSlidePathNodes = newSlidePathNodes;
            }
            for (SlidePathNode validEndNodes : currentSlidePathNodes) {
                possibleSpiderDragMoves.push_back(Move(MoveType::DragMove, spider.GetAxialPosition(), validEndNodes.GetPosition(), PieceType::Spider));
            }
        }
        return possibleSpiderDragMoves;
    }

    std::vector<Move> GameState::GetPossibleBeetleDragMoves() const {
        std::vector<Move> possibleBeetleDragMoves;
        std::vector<PieceStack> beetlesOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Beetle);
        for (PieceStack beetle : beetlesOfCurrentPlayer) {
            std::vector<AxialPosition> neighbouringPositions = beetle.GetAxialPosition().GetNeighbouringPositions();

            for (AxialPosition neighbouringPosition : neighbouringPositions) {
                if (board.PieceStackExists(neighbouringPosition)) {
                    possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, beetle.GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                } else {
                    if (board.CanSlide(beetle.GetAxialPosition(), neighbouringPosition)) {
                        possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, beetle.GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                    }
                }
            }
        }
        return possibleBeetleDragMoves;
    }

    std::vector<Move> GameState::GetPossibleGrasshopperDragMoves() const {
        std::vector<Move> possibleGrasshopperDragMoves;
        std::vector<PieceStack> grasshoppersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Grasshopper);
        for (PieceStack grasshopper : grasshoppersOfCurrentPlayer) {
            std::vector<PieceStack> neighbouringPieceStacks = board.GetNeighbouringPieceStacks(grasshopper.GetAxialPosition());
            for (PieceStack neighbouringPieceStack : neighbouringPieceStacks) {
                AxialPosition translation = grasshopper.GetAxialPosition().GetTranslationToOtherPosition(neighbouringPieceStack.GetAxialPosition());
                AxialPosition searchPos = grasshopper.GetAxialPosition();
                searchPos = searchPos.Add(translation);
                while (board.IsAxialPositionOnBoard(searchPos)) {
                    if (!board.PieceStackExists(searchPos)) {
                        possibleGrasshopperDragMoves.push_back(Move(MoveType::DragMove, grasshopper.GetAxialPosition(), searchPos, PieceType::Grasshopper));
                    }
                    searchPos = searchPos.Add(translation);
                }
            }
        }
    }

    std::vector<Move> GameState::GetPossibleAntDragMoves() const {
        std::vector<Move> possibleAntDragMoves;
        std::vector<PieceStack> antsOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Ant);
        for (PieceStack ant : antsOfCurrentPlayer) {
            std::vector<AxialPosition> searchedPositions;
            std::vector<AxialPosition> slideEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(ant.GetAxialPosition(), searchedPositions);

            while (!slideEndPositions.empty()) {
                for (AxialPosition position : slideEndPositions) {
                    possibleAntDragMoves.push_back(Move(MoveType::DragMove, ant.GetAxialPosition(), position, PieceType::Ant));
                }
                searchedPositions.insert(searchedPositions.end(), slideEndPositions.begin(), slideEndPositions.end());
                slideEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(ant.GetAxialPosition(), searchedPositions);
            }
        }
    }

    //Private

    std::vector<AxialPosition> GameState::GetDeployablePositions() const {
        std::vector<AxialPosition> deployablePositions;

        if (turn == 0) {
            std::vector<AxialPosition> emptyAxialPositions = board.GetEmptyAxialPositionsOnBoard();
            for (AxialPosition emptyAxialPosition : emptyAxialPositions) {
                deployablePositions.push_back(emptyAxialPosition);
            }
        } else if (turn == 1) {
            std::vector<PieceStack> pieceStacks = board.GetPieceStacksByColorAndType(Color::Red, PieceType::QueenBee);
            std::vector<AxialPosition> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(pieceStacks[0].GetAxialPosition());
            for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
                deployablePositions.push_back(neighbouringEmptyPosition);
            }
        } else {
            std::vector<PieceStack> pieceStacksOfCurrentPlayer = board.GetPieceStacksByColor(currentPlayer.GetColor());
            for (PieceStack gameSpieceStack : pieceStacksOfCurrentPlayer) {
                std::vector<AxialPosition> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(gameSpieceStack.GetAxialPosition());
                for (AxialPosition neighbouringEmptyPosition : neighbouringEmptyPositions) {
                    std::vector<PieceStack> neighbouringStacks = board.GetNeighbouringPieceStacks(neighbouringEmptyPosition);
                    bool enemyStackNeighbouring = false;
                    for (PieceStack neighbouringStack : neighbouringStacks) {
                        if (neighbouringStack.GetPieceOnTop().GetColor() != currentPlayer.GetColor()) {
                            enemyStackNeighbouring = true;
                            break;
                        }
                    }
                    if (!enemyStackNeighbouring && std::find(deployablePositions.begin(), deployablePositions.end(), neighbouringEmptyPosition) == deployablePositions.end()) {
                        deployablePositions.push_back(neighbouringEmptyPosition);
                    }
                }
            }
        }
        return deployablePositions;
    }
}  // namespace Hive