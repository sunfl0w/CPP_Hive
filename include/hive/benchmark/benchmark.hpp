#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "gameState.hpp"
#include "move.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs);
}