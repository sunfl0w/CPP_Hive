#include "hiveLogic.hpp"

namespace AI {
    HiveLogic::HiveLogic() {}
    HiveLogic::~HiveLogic() {}
    Hive::Move HiveLogic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
        srand (time(NULL));
        std::vector<Hive::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }
}  // namespace AI