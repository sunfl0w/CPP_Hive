#include "hiveLogic.hpp"

namespace AI {
    HiveLogic::HiveLogic() {}
    HiveLogic::~HiveLogic() {}
    Hive::Move HiveLogic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
        srand (time(NULL));
        std::vector<Hive::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }

    void HiveLogic::OnGameEnd(Hive::Color colorOfWinningPlayer) {
        std::cout << "Winning player has the color: " + Hive::ColorToString(colorOfWinningPlayer) + "\n";
    }
}  // namespace AI