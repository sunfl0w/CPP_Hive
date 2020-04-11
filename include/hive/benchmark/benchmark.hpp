#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "gameState.hpp"
#include "move.hpp"

namespace Hive::Benchmark {
    /**
     * @brief A benchmarking method to benchmark the GetPossibleMoves() method.
     * 
     * @param benchmarkingTimeInMs The time to benchmark for in milliseconds.
     */
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs);
    
    /**
     * @brief Runs a perft benchmark to a given depth.
     * 
     * @param depth The depth to reach.
     */
    void PerftBenchmark(int depth);

    /**
     * @brief Recursive perft method for the perft benchmark.
     * 
     * @param depth The depth to reach.
     * @param baseState The GameState for a given depth.
     * @return unsigned long The nodes that were discovered.
     */
    unsigned long Perft(int depth, GameState& baseState);
}