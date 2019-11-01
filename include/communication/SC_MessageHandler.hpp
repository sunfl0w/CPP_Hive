#pragma once

#include <algorithm>
#include <iostream>
#include <pugixml.hpp>
#include <string>
#include <vector>

#include "Color.hpp"
#include "GameState.hpp"
#include "Move.hpp"
#include "SC_Message.hpp"
#include "XmlStringWriter.hpp"

namespace Communication {
    class SC_MessageHandler {
    private:
        std::vector<SC_Message> FilterProtocolMessages(const std::string& inputStream);

    public:
        SC_MessageHandler();

        std::vector<SC_Message> SplitInputMessagesIntoValidSC_Messages(const std::string& inputStream);

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