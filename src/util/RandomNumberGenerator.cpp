#include "RandomNumberGenerator.hpp"

#include <limits>
#include <random>

namespace Util {
    int RandomNumberGenerator::GetRandomInt(int min, int max) {
        std::random_device randomDevice;
        std::mt19937 randomNumberGenerator(randomDevice());
        std::uniform_int_distribution<> distribution(min, max);
        return distribution(randomNumberGenerator);
    }
}  // namespace Util