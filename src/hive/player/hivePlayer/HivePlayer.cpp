#include "HivePlayer.hpp"

namespace Hive::Player {
    HivePlayer::HivePlayer(std::string playerName, PlayerColor playerColor) {
        this->playerName = playerName;
        this->playerColor = playerColor;
    }
}  // namespace Hive