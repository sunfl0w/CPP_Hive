#include "benchmark.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs) {
        //std::random_device randomDevice;
        //std::mt19937 randomNumberGenerator(randomDevice());
        srand (time(NULL));

        int count = 0;
        GameState gameState;
        gameState.GetBoard().PlaceObstacles();
        gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
        gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkingTimeInMs) {
            if(gameState.IsGameOver()) {
                gameState = GameState();
                gameState.GetBoard().PlaceObstacles();
                gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
                gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();
            }
            std::vector<Hive::Move> possibleMoves = gameState.GetPossibleMoves();

            //std::uniform_int_distribution<> distribution(0, possibleMoves.size() - 1);
            gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);
            
            count++;
        }
        std::cout << "Searched possible moves on random game states " << count << " times in " << benchmarkingTimeInMs << "ms" << std::endl;
    }
}