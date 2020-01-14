#include "Logic.hpp"

namespace AI {
    Logic::Logic() {}

    Logic::~Logic() {}

    Hive::Move Logic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
        std::cout << "Using C++ fallback GetNextMove(). Probably no logic was defined.\n";
        srand(time(NULL));
        std::vector<Hive::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }
}  // namespace AI