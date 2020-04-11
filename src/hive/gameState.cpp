#include "gameState.hpp"

namespace Hive {
    GameState::GameState() {
        turn = 0;
        board = Board();
        redPlayer = Player(Color::Red);
        bluePlayer = Player(Color::Blue);
        currentPlayerColor = Color::Red;
        performedMoves = std::vector<Move>();
    }

    GameState::GameState(const GameState& gameState) : board(gameState.board), redPlayer(gameState.redPlayer), bluePlayer(gameState.bluePlayer), performedMoves(gameState.performedMoves) {
        turn = gameState.turn;
        currentPlayerColor = gameState.currentPlayerColor;
    }

    unsigned int GameState::GetTurn() const {
        return turn;
    }

    void GameState::SetTurn(unsigned int turn) {
        this->turn = turn;
    }

    Move& GameState::GetLastPerformedMove() {
        return performedMoves[performedMoves.size() - 1];
    }

    Board& GameState::GetBoard() {
        return board;
    }

    Player& GameState::GetPlayer(Color color) {
        if (color == Color::Red) {
            return redPlayer;
        } else {
            return bluePlayer;
        }
    }

    Player& GameState::GetCurrentPlayer() {
        if (currentPlayerColor == Color::Red) {
            return redPlayer;
        } else {
            return bluePlayer;
        }
    }

    void GameState::SetCurrentPlayerColor(Color color) {
        currentPlayerColor = color;
    }

    Player& GameState::GetPausedPlayer() {
        if (currentPlayerColor == Color::Red) {
            return bluePlayer;
        } else {
            return redPlayer;
        }
    }

    std::vector<Move> GameState::GetPossibleMoves() {
        std::vector<Move> possibleMoves;

        std::vector<PieceStack*> pieceStacksOnBoard = board.GetPieceStacks();

        bool isQueenBeeOfCurrentPlayerOnBoard = false;
        for (PieceStack* pieceStack : pieceStacksOnBoard) {
            for (Piece piece : pieceStack->GetPieces()) {
                if (piece.GetType() == PieceType::QueenBee && piece.GetColor() == currentPlayerColor) {
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
            possibleMoves.emplace_back(Move(MoveType::PassMove, Color::Undefined, AxialPosition(0, 0), AxialPosition(0, 0), PieceType::Obstacle));
        }

        return possibleMoves;
    }

    void GameState::PerformMove(const Move& move) {
        if (move.GetMoveType() == MoveType::PassMove) {
        } else if (move.GetMoveType() == MoveType::DeployMove) {
            if (currentPlayerColor == Color::Red) {
                redPlayer.RemoveUndeployedPieceType(move.GetMovedPieceType());
                board.AddPieceOnTop(Piece(move.GetMovedPieceType(), redPlayer.GetColor()), move.GetDestinationPosition());
            } else {
                bluePlayer.RemoveUndeployedPieceType(move.GetMovedPieceType());
                board.AddPieceOnTop(Piece(move.GetMovedPieceType(), bluePlayer.GetColor()), move.GetDestinationPosition());
            }
        } else if (move.GetMoveType() == MoveType::DragMove) {
            if (currentPlayerColor == Color::Red) {
                board.RemoveUpmostPiece(move.GetStartPosition());
                board.AddPieceOnTop(Piece(move.GetMovedPieceType(), redPlayer.GetColor()), move.GetDestinationPosition());
            } else {
                board.RemoveUpmostPiece(move.GetStartPosition());
                board.AddPieceOnTop(Piece(move.GetMovedPieceType(), bluePlayer.GetColor()), move.GetDestinationPosition());
            }
        }
        performedMoves.push_back(Move(move));
        turn++;
        if (currentPlayerColor == Color::Red) {
            currentPlayerColor = Color::Blue;
        } else {
            currentPlayerColor = Color::Red;
        }
    }

    void GameState::UndoLastMove() {
        Move lastMove = performedMoves.back();
        if (lastMove.GetMoveType() == MoveType::PassMove) {
        } else if (lastMove.GetMoveType() == MoveType::DeployMove) {
            if (currentPlayerColor == Color::Red) {
                bluePlayer.AddUndeployedPieceType(lastMove.GetMovedPieceType());
                board.RemoveUpmostPiece(lastMove.GetDestinationPosition());
            } else {
                redPlayer.AddUndeployedPieceType(lastMove.GetMovedPieceType());
                board.RemoveUpmostPiece(lastMove.GetDestinationPosition());
            }
        } else if (lastMove.GetMoveType() == MoveType::DragMove) {
            if (currentPlayerColor == Color::Red) {
                board.AddPieceOnTop(Piece(lastMove.GetMovedPieceType(), bluePlayer.GetColor()), lastMove.GetStartPosition());
                board.RemoveUpmostPiece(lastMove.GetDestinationPosition());
            } else {
                board.AddPieceOnTop(Piece(lastMove.GetMovedPieceType(), redPlayer.GetColor()), lastMove.GetStartPosition());
                board.RemoveUpmostPiece(lastMove.GetDestinationPosition());
            }
        }
        performedMoves.pop_back();
        turn--;
        if (currentPlayerColor == Color::Red) {
            currentPlayerColor = Color::Blue;
        } else {
            currentPlayerColor = Color::Red;
        }
    }

    //Private

    std::vector<Move> GameState::GetPossibleDeployMoves() {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            if (currentPlayerColor == Color::Red) {
                for(int type = 0; type < 5; type++) {
                    if(redPlayer.GetUndeployedPieceTypeCounts()[type] > 0) {
                        possibleDeployMoves.emplace_back(Move(MoveType::DeployMove, Color::Red, AxialPosition(0, 0), deployablePosition, static_cast<PieceType>(type)));
                    }
                }
            } else {
                for(int type = 0; type < 5; type++) {
                    if(bluePlayer.GetUndeployedPieceTypeCounts()[type] > 0) {
                        possibleDeployMoves.emplace_back(Move(MoveType::DeployMove, Color::Blue, AxialPosition(0, 0), deployablePosition, static_cast<PieceType>(type)));
                    }
                }
            }
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDeployMoves() {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            possibleDeployMoves.emplace_back(Move(MoveType::DeployMove, currentPlayerColor, AxialPosition(0, 0), deployablePosition, PieceType::QueenBee));
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleDragMoves() {
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

    std::vector<Move> GameState::GetPossibleQueenBeeDragMoves() {
        std::vector<Move> possibleQueenBeeDragMoves;
        std::vector<PieceStack*> queenBeesOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayerColor, PieceType::QueenBee);
        for (PieceStack* queenBeeOfCurrentPlayer : queenBeesOfCurrentPlayer) {
            if (board.IsHiveCoherentIfPieceMovesFromPosition(AxialPosition(queenBeeOfCurrentPlayer->GetAxialPosition()))) {
                std::vector<AxialPosition*> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(queenBeeOfCurrentPlayer->GetAxialPosition());

                for (AxialPosition* emptyNeighbouringPosition : emptyNeighbouringPositions) {
                    if (board.CanSlide(queenBeeOfCurrentPlayer->GetAxialPosition(), *emptyNeighbouringPosition)) {
                        possibleQueenBeeDragMoves.emplace_back(Move(MoveType::DragMove, currentPlayerColor, queenBeeOfCurrentPlayer->GetAxialPosition(), *emptyNeighbouringPosition, PieceType::QueenBee));
                    }
                }
            }
        }
        return possibleQueenBeeDragMoves;
    }

    std::vector<Move> GameState::GetPossibleSpiderDragMoves() {
        std::vector<Move> possibleSpiderDragMoves;
        std::vector<PieceStack*> spidersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayerColor, PieceType::Spider);
        for (PieceStack* spider : spidersOfCurrentPlayer) {
            board.GetPieceStack(spider->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Undefined);
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(AxialPosition(spider->GetAxialPosition()))) {
                board.GetPieceStack(spider->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Spider);
                continue;
            }
            std::vector<AxialPosition> searchedPositions = std::vector<AxialPosition>();
            std::vector<AxialPosition> currentSlidePathEndPositions;
            currentSlidePathEndPositions.push_back(AxialPosition(spider->GetAxialPosition()));
            for (int i = 0; i < 3; i++) {
                std::vector<AxialPosition> newSlidePathEndPositions;
                for (AxialPosition currentSlidePathEndPosition : currentSlidePathEndPositions) {
                    std::vector<AxialPosition*> emptyNeighbouringPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(currentSlidePathEndPosition, searchedPositions);
                    for (AxialPosition* emptyNeighbouringPosition : emptyNeighbouringPositions) {
                        newSlidePathEndPositions.push_back(*emptyNeighbouringPosition);
                    }
                }
                searchedPositions.insert(searchedPositions.end(), currentSlidePathEndPositions.begin(), currentSlidePathEndPositions.end());
                currentSlidePathEndPositions = newSlidePathEndPositions;
            }
            board.GetPieceStack(spider->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Spider);
            for (AxialPosition validEndPosition : currentSlidePathEndPositions) {
                possibleSpiderDragMoves.emplace_back(Move(MoveType::DragMove, currentPlayerColor, spider->GetAxialPosition(), validEndPosition, PieceType::Spider));
            }
        }
        return possibleSpiderDragMoves;
    }

    std::vector<Move> GameState::GetPossibleBeetleDragMoves() {
        std::vector<Move> possibleBeetleDragMoves;
        std::vector<PieceStack*> beetlesOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayerColor, PieceType::Beetle);
        for (PieceStack* beetle : beetlesOfCurrentPlayer) {
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(AxialPosition(beetle->GetAxialPosition()))) {
                continue;
            }
            std::vector<AxialPosition> neighbouringPositions = beetle->GetAxialPosition().GetNeighbouringPositions();

            for (AxialPosition neighbouringPosition : neighbouringPositions) {
                if (board.PieceStackExists(neighbouringPosition)) {
                    if (board.GetPieceStack(neighbouringPosition).GetPieceOnTop().GetType() != PieceType::Obstacle) {
                        possibleBeetleDragMoves.emplace_back(Move(MoveType::DragMove, currentPlayerColor, beetle->GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                    }
                } else {
                    if (board.CanSlide(beetle->GetAxialPosition(), neighbouringPosition)) {
                        possibleBeetleDragMoves.emplace_back(Move(MoveType::DragMove, currentPlayerColor, beetle->GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                    }
                }
            }
        }
        return possibleBeetleDragMoves;
    }

    std::vector<Move> GameState::GetPossibleGrasshopperDragMoves() {
        std::vector<Move> possibleGrasshopperDragMoves;
        std::vector<PieceStack*> grasshoppersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayerColor, PieceType::Grasshopper);
        for (PieceStack* grasshopper : grasshoppersOfCurrentPlayer) {
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(AxialPosition(grasshopper->GetAxialPosition()))) {
                continue;
            }
            std::vector<PieceStack*> neighbouringPieceStacks = board.GetNeighbouringPieceStacks(grasshopper->GetAxialPosition());
            for (PieceStack* neighbouringPieceStack : neighbouringPieceStacks) {
                AxialPosition translation = grasshopper->GetAxialPosition().GetTranslationToOtherPosition(neighbouringPieceStack->GetAxialPosition());
                AxialPosition searchPos = grasshopper->GetAxialPosition();
                searchPos = searchPos.Add(translation);
                while (searchPos.IsOnBoard()) {
                    if (!board.PieceStackExists(searchPos) && !board.GetNeighbouringPieceStacksExceptObstacles(searchPos).empty()) {
                        possibleGrasshopperDragMoves.emplace_back(Move(MoveType::DragMove, currentPlayerColor, grasshopper->GetAxialPosition(), searchPos, PieceType::Grasshopper));
                        break;
                    } else if (board.PieceStackExists(searchPos) && board.GetPieceStack(searchPos).GetPieceOnTop().GetType() == PieceType::Obstacle) {
                        break;  //All moves going further are blocked by obstacle.
                    }
                    searchPos = searchPos.Add(translation);
                }
            }
        }
        return possibleGrasshopperDragMoves;
    }

    std::vector<Move> GameState::GetPossibleAntDragMoves() {
        std::vector<Move> possibleAntDragMoves;
        std::vector<PieceStack*> antsOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayerColor, PieceType::Ant);
        for (PieceStack* ant : antsOfCurrentPlayer) {
            board.GetPieceStack(ant->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Undefined);
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(AxialPosition(ant->GetAxialPosition()))) {
                board.GetPieceStack(ant->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Ant);
                continue;
            }
            std::vector<AxialPosition> searchedPositions;
            std::vector<AxialPosition*> slideEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(ant->GetAxialPosition(), searchedPositions);

            while (!slideEndPositions.empty()) {
                std::vector<AxialPosition*> newSlideEndPositions;
                for (AxialPosition* position : slideEndPositions) {
                    possibleAntDragMoves.push_back(Move(MoveType::DragMove, currentPlayerColor, ant->GetAxialPosition(), *position, PieceType::Ant));
                    std::vector<AxialPosition*> newEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(*position, searchedPositions);
                    newSlideEndPositions.insert(newSlideEndPositions.end(), newEndPositions.begin(), newEndPositions.end());
                    searchedPositions.push_back(*position);
                }
                slideEndPositions = newSlideEndPositions;
            }
            board.GetPieceStack(ant->GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Ant);
        }
        return possibleAntDragMoves;
    }

    bool GameState::IsGameOver() {
        if (currentPlayerColor == Color::Red) {
            if (board.GetPieceStacksContainingPieceByColorAndType(Color::Red, PieceType::QueenBee).empty() && turn > 6) {
                return true;
            } else if (IsQueenBeeBlocked(Color::Red)) {
                return true;
            }
        } else if (currentPlayerColor == Color::Blue) {
            if (board.GetPieceStacksContainingPieceByColorAndType(Color::Blue, PieceType::QueenBee).empty() && turn > 7) {
                return true;
            } else if (IsQueenBeeBlocked(Color::Blue) && turn % 2 == 0) {
                return true;
            }
        }
        if (turn > 60) {
            return true;
        }
        return false;
    }

    //Private

    std::vector<AxialPosition> GameState::GetDeployablePositions() {
        std::vector<AxialPosition> deployablePositions;

        if (turn == 0) {
            std::vector<AxialPosition> emptyAxialPositions = board.GetEmptyAxialPositionsOnBoard();
            for (AxialPosition emptyAxialPosition : emptyAxialPositions) {
                deployablePositions.push_back(emptyAxialPosition);
            }
        } else if (turn == 1) {
            std::vector<PieceStack*> pieceStacks = board.GetPieceStacksByColor(Color::Red);
            std::vector<AxialPosition*> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(pieceStacks[0]->GetAxialPosition());
            for (AxialPosition* neighbouringEmptyPosition : neighbouringEmptyPositions) {
                deployablePositions.push_back(*neighbouringEmptyPosition);
            }
        } else {
            std::vector<PieceStack*> pieceStacksOfCurrentPlayer = board.GetPieceStacksByColor(currentPlayerColor);
            for (PieceStack* gameSpieceStack : pieceStacksOfCurrentPlayer) {
                std::vector<AxialPosition*> neighbouringEmptyPositions = board.GetEmptyNeighbouringAxialPositions(gameSpieceStack->GetAxialPosition());
                for (AxialPosition* neighbouringEmptyPosition : neighbouringEmptyPositions) {
                    std::vector<PieceStack*> neighbouringStacks = board.GetNeighbouringPieceStacks(*neighbouringEmptyPosition);
                    bool enemyStackNeighbouring = false;
                    for (PieceStack* neighbouringStack : neighbouringStacks) {
                        if (neighbouringStack->GetPieceOnTop().GetColor() != currentPlayerColor && neighbouringStack->GetPieceOnTop().GetType() != PieceType::Obstacle) {
                            enemyStackNeighbouring = true;
                            break;
                        }
                    }
                    if (!enemyStackNeighbouring && std::find(deployablePositions.begin(), deployablePositions.end(), *neighbouringEmptyPosition) == deployablePositions.end()) {
                        deployablePositions.emplace_back(*neighbouringEmptyPosition);
                    }
                }
            }
        }
        return deployablePositions;
    }

    bool GameState::IsQueenBeeBlocked(Color color) {
        std::vector<PieceStack*> queenBees = board.GetPieceStacksByColorAndType(color, PieceType::QueenBee);
        if (queenBees.size() > 0) {
            PieceStack* queenBee = queenBees[0];
            std::vector<AxialPosition> neighbouringPositions = queenBee->GetAxialPosition().GetNeighbouringPositionsIncludingOutsideBoardPositions();
            int numberOfBlockingNeighbours = 0;
            for (AxialPosition neighbouringPosition : neighbouringPositions) {
                if (!neighbouringPosition.IsOnBoard()) {
                    numberOfBlockingNeighbours++;
                } else if (board.PieceStackExists(neighbouringPosition)) {
                    numberOfBlockingNeighbours++;
                }
            }
            if (numberOfBlockingNeighbours == 6) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}  // namespace Hive