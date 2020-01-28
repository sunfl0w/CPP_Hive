#pragma once

#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "logic.hpp"
#include "sc_Message.hpp"
#include "sc_MessageHandler.hpp"
#include "sc_MessageType.hpp"
#include "tcp_Client.hpp"

#include "color.hpp"
#include "move.hpp"
#include "gameState.hpp"

namespace Client {
    class HiveClient {
        Client::TCP_Client tcpClient;
        SC_Communication::SC_MessageHandler scMessageHandler;
        std::string roomID;
        Hive::Color ownPlayerColor;
        Hive::GameState currentGameState;
        bool gameOver = false;
        AI::Logic* logic;
        bool verboseOutputEnabled = false;

    public:
        HiveClient(AI::Logic* logic);
        void Start(int argc, char *argv[]);

    private:
        std::vector<SC_Communication::SC_Message> HandleIncomingMessagesAndGenerateRespones(const std::vector<SC_Communication::SC_Message> &incomingMessages);
        void ClientLoop();
        void Shutdown();
        Hive::Move GetNextMove(Hive::GameState currentGameState, Hive::Color ownPlayerColor);
        void StartConnection(const std::string &address, const unsigned short &port);
        void StartReservedConnection(const std::string &hostanme, const unsigned short &port, const std::string &reservationCode);
    };
}  // namespace Client