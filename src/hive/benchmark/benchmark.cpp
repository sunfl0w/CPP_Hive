#include "benchmark.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs) {
        srand(time(NULL));

        int count = 0;
        int gamesPlayed = 0;
        GameState gameState;
        gameState.GetBoard().PlaceObstacles();
        gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
        gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();

        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        while (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count() < benchmarkingTimeInMs) {
            if (gameState.IsGameOver()) {
                gamesPlayed++;
                gameState = GameState();
                gameState.GetBoard().PlaceObstacles();
                gameState.GetPlayer(Color::Red).InitializeUndeployedPieces();
                gameState.GetPlayer(Color::Blue).InitializeUndeployedPieces();
            }
            std::vector<Hive::Move> possibleMoves = gameState.GetPossibleMoves();
            gameState.PerformMove(possibleMoves[rand() % possibleMoves.size()]);

            count++;
        }
        std::cout << "Searched possible moves on random game states " << count << " times in " << benchmarkingTimeInMs << "ms"
                  << " || "
                  << "Random games played: " << gamesPlayed << std::endl;
    }

    void PerftBenchmark(int depth) {
        Hive::GameState base = Hive::GameState();
        base.GetBoard().PlaceObstacles();
        base.GetPlayer(Hive::Color::Red).InitializeUndeployedPieces();
        base.GetPlayer(Hive::Color::Blue).InitializeUndeployedPieces();
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        unsigned long numberOfNodes = Hive::Benchmark::Perft(5, base);
        int timeInMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
        std::cout << "Nodes: " << numberOfNodes << " Time: " << timeInMs << "ms" << std::endl;
        std::cout << "Perft: " << numberOfNodes / timeInMs * 1000 << std::endl;
    }

    unsigned long Perft(int depth, GameState& baseState) {
        if (depth == 0) {
            return 1;
        }
        unsigned long numberOfNodes = 0;
        std::vector<Move> possibleMoves = baseState.GetPossibleMoves();

        for (Move move : possibleMoves) {
            baseState.PerformMove(move);
            numberOfNodes += Perft(depth - 1, baseState);
            baseState.UndoLastMove();
        }
        return numberOfNodes;
    }
}  // namespace Hive::Benchmark