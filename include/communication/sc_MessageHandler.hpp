#pragma once

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <cstring>

#include "pugixml.hpp"
#include "color.hpp"
#include "gameState.hpp"
#include "move.hpp"
#include "moveType.hpp"
#include "axialPosition.hpp"
#include "piece.hpp"
#include "pieceType.hpp"
#include "sc_Message.hpp"
#include "xmlStringWriter.hpp"

namespace SC_Communication {
    /**
     * @brief This class works on and with messages from the SC-Server.
     * 
     */
    class SC_MessageHandler {
    private:
        /**
         * @brief Removes all protocol messages from the message received from the SC-Server.
         * 
         * @param inputStream The message received from the SC-Server.
         * @return A vector of SC_Messages that represent possible protocol messages.
         */
        std::vector<SC_Message> FilterProtocolMessages(std::string& inputStream);

    public:
        /**
         * @brief Constructs a new SC_MessageHandler.
         * 
         */
        SC_MessageHandler();

        /**
         * @brief Splits the incoming messages into SC_Messages.
         * 
         * @param inputStream The message received from the SC-Server.
         * @return A vector of SC_Messages.
         */
        std::vector<SC_Message> SplitInputMessagesIntoValidSC_Messages(std::string inputStream);

        /**
         * @brief Creates a protocol SC_Message.
         * 
         * @return A protocol SC_Message.
         */
        SC_Message CreateProtocolMessage();

        /**
         * @brief Creates a protocol end SC_Message.
         * 
         * @return A protocol end SC_Message.
         */
        SC_Message CreateProtocolEndMessage();

        /**
         * @brief Creates a join request SC_Message.
         * 
         * @return A join request SC_Message.
         */
        SC_Message CreateJoinRequestMessage();

        /**
         * @brief Creates a join reserved SC_Message.
         * 
         * @param reservationCode The reservation code.
         * @return A join reserved SC_Message.
         */
        SC_Message CreateJoinReservedRequestMessage(const std::string &reservationCode);

        /**
         * @brief Create a move SC_Message.
         * 
         * @param move The move.
         * @param roomID The room ID.
         * @return A move SC_Message.
         */
        SC_Message CreateMoveMessage(const Hive::Move& move, const std::string& roomID);

        /**
         * @brief Gets the Player Color from welcome SC_Messages.
         * 
         * @param message The welcome SC_Message.
         * @return Player Color in the welcome SC_Message.
         */
        Hive::Color GetPlayerColorFromWelcomeMessage(const SC_Message &message);

        /**
         * @brief Gets the room ID from joined SC_Messages.
         * 
         * @param message The joined SC_Message.
         * @return The room ID.
         */
        std::string GetRoomIDFromJoinedMessage(const SC_Message &message);

        /**
         * @brief Gets the GameState from gameState SC_Messages.
         * 
         * @param message The gameState SC_Message.
         * @return The GameState.
         */
        Hive::GameState GetGameStateFromGameStateMessage(const SC_Message &message);

        /**
         * @brief Gets the Color of the Player that won the game from result SC_Messages.
         * 
         * @param message The result SC_Message.
         * @return The Color of the Player that won the game.
         */
        Hive::Color GetColorOfWinningPlayerFromResultMessage(const SC_Message &message);
    };
}  // namespace Communication