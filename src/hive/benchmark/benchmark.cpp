#include "benchmark.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs) {
        srand (time(NULL));

        int count = 0;
        int gamesPlayed = 0;
        GameState gameState;
        gameState.GetBoard().PlaceObstacles();
        gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
        gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkingTimeInMs) {
            if(gameState.IsGameOver()) {
                gamesPlayed++;
                gameState = GameState();
                gameState.GetBoard().PlaceObstacles();
                gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
                gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();
            }
            std::vector<Hive::Move> possibleMoves = gameState.GetPossibleMoves();

            if(gameState.GetTurn() == 0) {
                AxialPosition center(0,0);
                for(Move move : possibleMoves) {
                    if(move.GetDestinationPosition().GetDistanceTo(center) < 2) {
                         gameState.PerformMove(move);
                         break;
                    }
                }
            } else {
                gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);
            }
            
            count++;
        }
        std::cout << "Searched possible moves on random game states " << count << " times in " << benchmarkingTimeInMs << "ms" << " || " << "Random games played: " << gamesPlayed << std::endl;
    }
}