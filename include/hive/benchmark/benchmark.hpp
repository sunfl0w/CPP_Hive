#pragma once

#include <chrono>
#include <vector>
#include <iostream>

#include "gameState.hpp"
#include "Move.hpp"
#include "RandomNumberGenerator.hpp"

namespace Hive::Benchmark {
    void BenchmarkGetPossibleMoves(unsigned int benchmarkingTimeInMs);
}