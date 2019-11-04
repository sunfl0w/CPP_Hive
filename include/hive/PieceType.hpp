#pragma once

#include <string>

namespace Hive {
    enum class PieceType {
        QueenBee,
        Spider,
        Beetle,
        Grasshopper,
        Ant,
        Obstacle,
    };

    static const std::string pieceTypeStrings[] = {"BEE", "SPIDER", "BEETLE", "GRASSHOPPER", "ANT", "OBSTACLE"};

    std::string PieceTypeToString(Hive::PieceType type);

    PieceType PieceTypeFromString(std::string pieceTypeAsString);
}  // namespace Hive