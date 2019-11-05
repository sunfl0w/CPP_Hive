#include <chrono>
#include <vector>

#include "gameState.hpp"
#include "Move.hpp"

namespace Hive::Benchmark {
    void BenchGetPossibleMoves(unsigned int benchmarkingTimeInMs) {
        int count = 0;
        GameState gameState;
        gameState.GetBoard().PlaceObstacles();

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkingTimeInMs) {
            std::vector<Hive::Move> possibleMoves = gameState.GetPossibleMoves();
            count++;
        }

    }
}