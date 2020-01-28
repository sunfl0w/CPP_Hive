#include "hiveClient.hpp"
#include "hiveLogic.hpp"
#include "benchmark.hpp"
#include "board.hpp"
#include "gameState.hpp"
#include "move.hpp"
#include <iostream>

int main(int argc, char *argv[]) {
    AI::HiveLogic logic = AI::HiveLogic();
    Client::HiveClient client(&logic);
    client.Start(argc, argv);
    //Hive::Benchmark::BenchmarkGetPossibleMoves(300000);
    //Hive::Benchmark::BenchmarkGetPossibleMoves(10000);

    /*Hive::GameState gameState;
    gameState.PerformMove(Hive::Move(Hive::MoveType::DeployMove, Hive::Color::Red, Hive::AxialPosition(0, 0), Hive::AxialPosition(0, 0), Hive::PieceType::Ant));
    gameState.PerformMove(Hive::Move(Hive::MoveType::DeployMove, Hive::Color::Blue, Hive::AxialPosition(0, 0), Hive::AxialPosition(0, 1), Hive::PieceType::Ant));
    gameState.PerformMove(Hive::Move(Hive::MoveType::DeployMove, Hive::Color::Red, Hive::AxialPosition(0, 0), Hive::AxialPosition(0, -1), Hive::PieceType::Ant));
    gameState.PerformMove(Hive::Move(Hive::MoveType::DeployMove, Hive::Color::Blue, Hive::AxialPosition(0, 0), Hive::AxialPosition(1, 0), Hive::PieceType::Ant));
    gameState.GetBoard().GetAdjacencyMatrix().ClearAllConnectionsOfNode(Hive::AxialPosition(0, 0));
    std::vector <Hive::AxialPosition> pos1 = gameState.GetBoard().GetAdjacencyMatrix().GetNeighbouringNodes(Hive::AxialPosition(0, 0));
    std::vector <Hive::AxialPosition> pos2 = gameState.GetBoard().GetAdjacencyMatrix().GetNeighbouringNodes(Hive::AxialPosition(0, 1));
    std::vector <Hive::AxialPosition> pos3 = gameState.GetBoard().GetAdjacencyMatrix().GetNeighbouringNodes(Hive::AxialPosition(0, -1));
    std::vector <Hive::AxialPosition> pos4 = gameState.GetBoard().GetAdjacencyMatrix().GetNeighbouringNodes(Hive::AxialPosition(1, 0));

    for(Hive::AxialPosition pos1s : pos1) {
        std::cout << pos1s.x << " " << pos1s.y << std::endl;
    }
    std::cout << "-----" << std::endl;
    for(Hive::AxialPosition pos2s : pos2) {
        std::cout << pos2s.x << " " << pos2s.y << std::endl;
    }
    std::cout << "-----" << std::endl;
    for(Hive::AxialPosition pos3s : pos3) {
        std::cout << pos3s.x << " " << pos3s.y << std::endl;
    }
    std::cout << "-----" << std::endl;
    for(Hive::AxialPosition pos4s : pos4) {
        std::cout << pos4s.x << " " << pos4s.y << std::endl;
    }*/

    /*Hive::Board board;
    board.AddPieceOnTop(Hive::Piece(Hive::PieceType::Ant, Hive::Color::Red), Hive::AxialPosition(0, 0));
    board.AddPieceOnTop(Hive::Piece(Hive::PieceType::Ant, Hive::Color::Red), Hive::AxialPosition(0, 1));
    board.AddPieceOnTop(Hive::Piece(Hive::PieceType::Ant, Hive::Color::Red), Hive::AxialPosition(0, -1));
    board.AddPieceOnTop(Hive::Piece(Hive::PieceType::Obstacle, Hive::Color::Undefined), Hive::AxialPosition(1, -1));

    board.GetAdjacencyMatrix().AddNodeConnection((0 + 5) * 11 + (0 + 5), (0 + 5) * 11 + (1 + 5));
    board.GetAdjacencyMatrix().AddNodeConnection((0 + 5) * 11 + (0 + 5), (0 + 5) * 11 + (-1 + 5));

    int n1 = board.GetNeighbouringPieceStacksExceptObstacles(Hive::AxialPosition(0, 0)).size();
    int n2 = board.GetAdjacencyMatrix().GetNeighbouringNodes(60).size();
    board.GetAdjacencyMatrix().ClearAllConnectionsOfNode(60);
    int n3 = board.GetAdjacencyMatrix().GetNeighbouringNodes(60).size();*/

    return 0;
}