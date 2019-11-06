#include "benchmark.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs) {
        int count = 0;
        GameState gameState;
        gameState.GetBoard().PlaceObstacles();
        gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
        gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();
        Util::RandomNumberGenerator rng;

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkingTimeInMs) {
            if(gameState.IsGameOver()) {
                gameState = GameState();
                gameState.GetBoard().PlaceObstacles();
                gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
                gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();
            }
            std::vector<Hive::Move> possibleMoves = gameState.GetPossibleMoves();
            gameState.PerformMove(possibleMoves[rng.GetRandomInt(0, possibleMoves.size() - 1)]);
            
            count++;
        }
        std::cout << "Searched possible moves on random game states " << count << " times in " << benchmarkingTimeInMs << "ms" << std::endl;
    }
}