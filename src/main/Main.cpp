#include <chrono>
#include <vector>
#include <iostream>

#include "GameState.hpp"

void Bench();

int main() {
    Bench();
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