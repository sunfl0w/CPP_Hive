#include <chrono>
#include <vector>
#include <iostream>

#include "GameState.hpp"

void Bench();
void Test1();

int main() {
    Test1();
    return 0;
}

void Bench() {
    Hive::GameState gameState;

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int count = 0;
    while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 1600) {
        std::vector<Hive::Move> deployMoves = gameState.GetPossibleDeployMoves();
        count++;
    }
    std::cout << "Count: " << count << "\n";
}

void Test1() {
    Hive::GameState gameState;

    Hive::Piece piece0 = Hive::Piece(Hive::PieceType::QueenBee, Hive::Color::Red);
    Hive::AxialPosition pos0 = Hive::AxialPosition(-1, -3);
    gameState.GetBoard().AddPieceOnTop(piece0, pos0);

    Hive::Piece piece1 = Hive::Piece(Hive::PieceType::Spider, Hive::Color::Red);
    Hive::AxialPosition pos1 = Hive::AxialPosition(-1, -4);
    gameState.GetBoard().AddPieceOnTop(piece1, pos1);

    Hive::Piece piece2 = Hive::Piece(Hive::PieceType::Grasshopper, Hive::Color::Red);
    Hive::AxialPosition pos2 = Hive::AxialPosition(-2, -2);
    gameState.GetBoard().AddPieceOnTop(piece2, pos2);

    Hive::Piece piece3 = Hive::Piece(Hive::PieceType::Ant, Hive::Color::Red);
    Hive::AxialPosition pos3 = Hive::AxialPosition(-2, -1);
    gameState.GetBoard().AddPieceOnTop(piece3, pos3);


    Hive::Piece piece4 = Hive::Piece(Hive::PieceType::QueenBee, Hive::Color::Blue);
    Hive::AxialPosition pos4 = Hive::AxialPosition(0, -3);
    gameState.GetBoard().AddPieceOnTop(piece4, pos4);

    Hive::Piece piece5 = Hive::Piece(Hive::PieceType::Grasshopper, Hive::Color::Blue);
    Hive::AxialPosition pos5 = Hive::AxialPosition(1, -3);
    gameState.GetBoard().AddPieceOnTop(piece5, pos5);

    Hive::Piece piece6 = Hive::Piece(Hive::PieceType::Beetle, Hive::Color::Blue);
    Hive::AxialPosition pos6 = Hive::AxialPosition(2, -3);
    gameState.GetBoard().AddPieceOnTop(piece6, pos6);

    Hive::Piece piece7 = Hive::Piece(Hive::PieceType::Beetle, Hive::Color::Blue);
    Hive::AxialPosition pos7 = Hive::AxialPosition(3, -3);
    gameState.GetBoard().AddPieceOnTop(piece7, pos7);


    Hive::Piece piece8 = Hive::Piece(Hive::PieceType::Obstacle, Hive::Color::Undefined);
    Hive::AxialPosition pos8 = Hive::AxialPosition(-2, -3);
    gameState.GetBoard().AddPieceOnTop(piece8, pos8);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    int count = 0;
    while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < 100) {
        std::vector<Hive::Move> dragMoves = gameState.GetPossibleDragMoves();
        count++;
        std::cout << "Moves calculated: " << dragMoves.size() << "\n";
    }
    std::cout << "Count: " << count << "\n";
}