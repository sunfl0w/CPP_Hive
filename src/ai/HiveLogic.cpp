#include "HiveLogic.hpp"

using namespace AI;
using namespace Hive;

HiveLogic::HiveLogic() {}

Hive::Move HiveLogic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
    Util::RandomNumberGenerator randomNumberGenerator = Util::RandomNumberGenerator();
    std::vector<Move> possibleMoves = currentGameState.GetPossibleMoves();
    return possibleMoves[randomNumberGenerator.GetRandomInt(0, possibleMoves.size() - 1)];
}