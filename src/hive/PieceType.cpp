#include "PieceType.hpp"

namespace Hive {
    std::string PieceTypeToString(Hive::PieceType type) {
        return pieceTypeStrings[(int)type];
    }

    PieceType PieceTypeFromString(std::string pieceTypeAsString) {
        if(pieceTypeAsString == "BEE") {
            return PieceType::QueenBee;
        } else if(pieceTypeAsString == "SPIDER") {
            return PieceType::Spider;
        } else if(pieceTypeAsString == "BEETLE") {
            return PieceType::Beetle;
        } else if(pieceTypeAsString == "GRASSHOPPER") {
            return PieceType::Grasshopper;
        } else if(pieceTypeAsString == "ANT") {
            return PieceType::Ant;
        } else {
            return PieceType::Obstacle;
        }
    }
}