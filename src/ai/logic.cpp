#include "logic.hpp"

namespace AI {
    Logic::Logic() {}

    Logic::~Logic() {}

    Hive::Move Logic::GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor) {
        std::cout << "Using C++ fallback GetNextMove(). Probably no logic was defined.\n";
        srand(time(NULL));
        std::vector<Hive::Move> possibleMoves = currentGameState.GetPossibleMoves();
        return possibleMoves[rand() % possibleMoves.size()];
    }

    void Logic::OnGameEnd(Hive::Color colorOfWinningPlayer) {
        std::cout << "Using C++ fallback OnGameEnd(). Probably no logic was defined.\n";
        std::cout << "Winning player has the color: " + Hive::ColorToString(colorOfWinningPlayer) + "\n";
    }
}  // namespace AI