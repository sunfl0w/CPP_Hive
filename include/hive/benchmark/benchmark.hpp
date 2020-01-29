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
}