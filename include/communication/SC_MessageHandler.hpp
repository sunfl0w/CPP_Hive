#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "pugixml.hpp"
#include "Color.hpp"
#include "gameState.hpp"
#include "Move.hpp"
#include "MoveType.hpp"
#include "AxialPosition.hpp"
#include "Piece.hpp"
#include "PieceType.hpp"
#include "SC_Message.hpp"
#include "XmlStringWriter.hpp"

namespace Communication {
    class SC_MessageHandler {
    private:
        std::vector<SC_Message> FilterProtocolMessages(std::string& inputStream);

    public:
        SC_MessageHandler();

        std::vector<SC_Message> SplitInputMessagesIntoValidSC_Messages(std::string inputStream);

        SC_Message CreateProtocolMessage();
        SC_Message CreateProtocolEndMessage();
        SC_Message CreateJoinRequestMessage();
        SC_Message CreateJoinReservedRequestMessage(const std::string &reservationCode);
        SC_Message CreateMoveMessage(const Hive::Move& move, const std::string& roomID);

        Hive::Color GetPlayerColorFromWelcomeMessage(const SC_Message &message);
        std::string GetRoomIDFromJoinedMessage(const SC_Message &message);
        Hive::GameState GetGameStateFromGameStateMessage(const SC_Message &message);
    };
}  // namespace Communication