#include "Logic.hpp"

using namespace AI;
using namespace Hive;

Logic::Logic() {}

Hive::Move Logic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
    srand(time(NULL));
    std::vector<Move> possibleMoves = currentGameState.GetPossibleMoves();
    return possibleMoves[rand() % possibleMoves.size()];
}
