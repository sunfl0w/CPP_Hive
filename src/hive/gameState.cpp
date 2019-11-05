#include "gameState.hpp"

namespace Hive {
    GameState::GameState() {
        turn = 0;
        board = Board();
        currentPlayer = Player(Color::Red);
        pausedPlayer = Player(Color::Blue);
        performedMoves = std::vector<Move>();
    }

    GameState::GameState(GameState& gameState) : board (gameState.board), currentPlayer(gameState.GetCurrentPlayer()), pausedPlayer(gameState.GetPausedPlayer()), performedMoves(gameState.performedMoves) {
        turn = gameState.turn;
    }

    unsigned int GameState::GetTurn() const {
        return turn;
    }

    void GameState::SetTurn(unsigned int turn) {
        this->turn = turn;
    }

    Board& GameState::GetBoard() {
        return board;
    }

    Player& GameState::GetPlayer(Color color) {
        if(currentPlayer.GetColor() == color) {
            return currentPlayer;
        } else if(pausedPlayer.GetColor() == color) {
            return pausedPlayer;
        }
    }

    Player& GameState::GetCurrentPlayer() {
        return currentPlayer;
    }

    void GameState::SetCurrentPlayer(Player player) {
        currentPlayer = player;
    }

    Player& GameState::GetPausedPlayer() {
        return pausedPlayer;
    }

    void GameState::SetPausedPlayer(Player player) {
        pausedPlayer = player;
    }

    std::vector<Move> GameState::GetPossibleMoves() {
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
            possibleMoves.push_back(Move(MoveType::PassMove, Color::Undefined, AxialPosition(0, 0), AxialPosition(0, 0), PieceType::Obstacle));
        }

        return possibleMoves;
    }

    void GameState::PerformMove(const Move& move) {
        if(move.GetMoveType() == MoveType::PassMove) {
            turn++;
        } else if(move.GetMoveType() == MoveType::DeployMove) {
            board.AddPieceOnTop(Piece(move.GetMovedPieceType(), currentPlayer.GetColor()), move.GetDestinationPosition());
            turn++;
        } else if(move.GetMoveType() == MoveType::DragMove) {
            board.RemoveUpmostPiece(move.GetStartPosition());
            board.AddPieceOnTop(Piece(move.GetMovedPieceType(), currentPlayer.GetColor()), move.GetDestinationPosition());
            turn++;
        }
    }

    //Private

    std::vector<Move> GameState::GetPossibleDeployMoves() const {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            for (Piece piece : currentPlayer.GetUndeployedPieces()) {
                possibleDeployMoves.push_back(Move(MoveType::DeployMove, currentPlayer.GetColor(), AxialPosition(0, 0), deployablePosition, piece.GetType()));
            }
        }
        return possibleDeployMoves;
    }

    std::vector<Move> GameState::GetPossibleQueenBeeDeployMoves() const {
        std::vector<Move> possibleDeployMoves;
        std::vector<AxialPosition> deployablePositions = GetDeployablePositions();
        for (AxialPosition deployablePosition : deployablePositions) {
            possibleDeployMoves.push_back(Move(MoveType::DeployMove, currentPlayer.GetColor(), AxialPosition(0, 0), deployablePosition, PieceType::QueenBee));
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
        std::vector<PieceStack> queenBeeOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::QueenBee);
        if (!board.IsHiveCoherentIfPieceMovesFromPosition(queenBeeOfCurrentPlayer[0].GetAxialPosition())) {
            return possibleQueenBeeDragMoves;
        }
        std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptyNeighbouringAxialPositions(queenBeeOfCurrentPlayer[0].GetAxialPosition());

        for (AxialPosition emptyNeighbouringPosition : emptyNeighbouringPositions) {
            if (board.CanSlide(queenBeeOfCurrentPlayer[0].GetAxialPosition(), emptyNeighbouringPosition)) {
                possibleQueenBeeDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), queenBeeOfCurrentPlayer[0].GetAxialPosition(), emptyNeighbouringPosition, PieceType::QueenBee));
            }
        }
        return possibleQueenBeeDragMoves;
    }

    std::vector<Move> GameState::GetPossibleSpiderDragMoves() {
        std::vector<Move> possibleSpiderDragMoves;
        std::vector<PieceStack> spidersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Spider);
        for (PieceStack spider : spidersOfCurrentPlayer) {
            board.GetPieceStackUnsafe(spider.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Obstacle);
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(spider.GetAxialPosition())) {
                board.GetPieceStackUnsafe(spider.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Spider);
                continue;
            }
            std::vector<AxialPosition> searchedPositions = std::vector<AxialPosition>();
            std::vector<AxialPosition> currentSlidePathEndPositions;
            currentSlidePathEndPositions.push_back(spider.GetAxialPosition());
            for (int i = 0; i < 3; i++) {
                std::vector<AxialPosition> newSlidePathEndPositions;
                for (AxialPosition currentSlidePathEndPosition : currentSlidePathEndPositions) {
                    std::vector<AxialPosition> emptyNeighbouringPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(currentSlidePathEndPosition, searchedPositions);
                    newSlidePathEndPositions.insert(newSlidePathEndPositions.end(), emptyNeighbouringPositions.begin(), emptyNeighbouringPositions.end());
                }
                searchedPositions.insert(searchedPositions.end(), currentSlidePathEndPositions.begin(), currentSlidePathEndPositions.end());
                currentSlidePathEndPositions = newSlidePathEndPositions;
            }
            board.GetPieceStackUnsafe(spider.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Spider);
            for (AxialPosition validEndPosition : currentSlidePathEndPositions) {
                possibleSpiderDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), spider.GetAxialPosition(), validEndPosition, PieceType::Spider));
            }
        }
        return possibleSpiderDragMoves;
    }

    std::vector<Move> GameState::GetPossibleBeetleDragMoves() {
        std::vector<Move> possibleBeetleDragMoves;
        std::vector<PieceStack> beetlesOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Beetle);
        for (PieceStack beetle : beetlesOfCurrentPlayer) {
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(beetle.GetAxialPosition())) {
                continue;
            }
            std::vector<AxialPosition> neighbouringPositions = beetle.GetAxialPosition().GetNeighbouringPositions();

            for (AxialPosition neighbouringPosition : neighbouringPositions) {
                if (board.PieceStackExists(neighbouringPosition) && board.GetPieceStack(neighbouringPosition).GetPieceOnTop().GetType() != PieceType::Obstacle) {
                    possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), beetle.GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                } else {
                    if (board.CanSlide(beetle.GetAxialPosition(), neighbouringPosition)) {
                        possibleBeetleDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), beetle.GetAxialPosition(), neighbouringPosition, PieceType::Beetle));
                    }
                }
            }
        }
        return possibleBeetleDragMoves;
    }

    std::vector<Move> GameState::GetPossibleGrasshopperDragMoves() {
        std::vector<Move> possibleGrasshopperDragMoves;
        std::vector<PieceStack> grasshoppersOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Grasshopper);
        for (PieceStack grasshopper : grasshoppersOfCurrentPlayer) {
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(grasshopper.GetAxialPosition())) {
                continue;
            }
            std::vector<PieceStack> neighbouringPieceStacks = board.GetNeighbouringPieceStacks(grasshopper.GetAxialPosition());
            for (PieceStack neighbouringPieceStack : neighbouringPieceStacks) {
                AxialPosition translation = grasshopper.GetAxialPosition().GetTranslationToOtherPosition(neighbouringPieceStack.GetAxialPosition());
                AxialPosition searchPos = grasshopper.GetAxialPosition();
                searchPos = searchPos.Add(translation);
                while (board.IsAxialPositionOnBoard(searchPos)) {
                    if(board.PieceStackExists(searchPos)) {
                        if(board.GetPieceStack(searchPos).GetPieceOnTop().GetType() == PieceType::Obstacle) {
                            break;
                        }
                    }
                    if (!board.PieceStackExists(searchPos)) {
                        possibleGrasshopperDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), grasshopper.GetAxialPosition(), searchPos, PieceType::Grasshopper));
                        break;
                    }
                    searchPos = searchPos.Add(translation);
                }
            }
        }
        return possibleGrasshopperDragMoves;
    }

    std::vector<Move> GameState::GetPossibleAntDragMoves() {
        std::vector<Move> possibleAntDragMoves;
        std::vector<PieceStack> antsOfCurrentPlayer = board.GetPieceStacksByColorAndType(currentPlayer.GetColor(), PieceType::Ant);
        for (PieceStack ant : antsOfCurrentPlayer) {
            board.GetPieceStackUnsafe(ant.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Obstacle);
            if (!board.IsHiveCoherentIfPieceMovesFromPosition(ant.GetAxialPosition())) {
                board.GetPieceStackUnsafe(ant.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Ant);
                continue;
            }
            std::vector<AxialPosition> searchedPositions;
            std::vector<AxialPosition> slideEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(ant.GetAxialPosition(), searchedPositions);

            while (!slideEndPositions.empty()) {
                std::vector<AxialPosition> newSlideEndPositions;
                for (AxialPosition position : slideEndPositions) {
                    possibleAntDragMoves.push_back(Move(MoveType::DragMove, currentPlayer.GetColor(), ant.GetAxialPosition(), position, PieceType::Ant));
                    std::vector<AxialPosition> newEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(position, searchedPositions);
                    newSlideEndPositions.insert(newSlideEndPositions.end(), newEndPositions.begin(), newEndPositions.end());
                    searchedPositions.push_back(position);
                    //slideEndPositions.erase(std::find(slideEndPositions.begin(), slideEndPositions.end(), position));
                }
                slideEndPositions = newSlideEndPositions;
                //searchedPositions.insert(searchedPositions.end(), slideEndPositions.begin(), slideEndPositions.end());
                //slideEndPositions = board.GetEmptySlideableNeighbouringAxialPositionsExcept(ant.GetAxialPosition(), searchedPositions);
            }
            board.GetPieceStackUnsafe(ant.GetAxialPosition()).GetPieceOnTop().SetType(PieceType::Ant);
        }
        return possibleAntDragMoves;
    }

    bool GameState::IsGameOver() const {
        if(currentPlayer.GetColor() == Color::Red) {
            if(board.GetPieceStacksByColorAndType(Color::Red, PieceType::QueenBee).empty() && turn > 6) {
                return true;
            }
        } else if(currentPlayer.GetColor() == Color::Blue) {
            if(board.GetPieceStacksByColorAndType(Color::Blue, PieceType::QueenBee).empty() && turn > 7) {
                return true;
            }
        } else if(turn > 60) {
            return true;
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
            std::vector<PieceStack> pieceStacks = board.GetPieceStacksByColor(Color::Red);
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
                        if (neighbouringStack.GetPieceOnTop().GetColor() != currentPlayer.GetColor() && neighbouringStack.GetPieceOnTop().GetType() != PieceType::Obstacle) {
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

    bool GameState::IsQueenBeeBlocked(Color color) {
        std::vector<PieceStack> queenBees = board.GetPieceStacksByColorAndType(color, PieceType::QueenBee);
        if(queenBees.size() > 0) {
            PieceStack queenBee = queenBees[0];
            std::vector<AxialPosition> neighbouringPositions = queenBee.GetAxialPosition().GetNeighbouringPositionsIncludingOutsideBoardPositions();
            int numberOfBlockingNeighbours = 0;
            for(AxialPosition neighbouringPosition : neighbouringPositions) {
                if(!board.IsAxialPositionOnBoard(neighbouringPosition)) {
                    numberOfBlockingNeighbours++;
                } else if(board.PieceStackExists(neighbouringPosition)) {
                    numberOfBlockingNeighbours++;
                }
            }
            if(numberOfBlockingNeighbours == 6) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
}  // namespace Hive