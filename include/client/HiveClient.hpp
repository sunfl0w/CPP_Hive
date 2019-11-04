#pragma once

#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "SC_Message.hpp"
#include "SC_MessageHandler.hpp"
#include "SC_MessageType.hpp"
#include "TCP_Client.hpp"
#include "HiveLogic.hpp"

#include "Color.hpp"
#include "gameState.hpp"
#include "Move.hpp"

namespace Client {
    class HiveClient {
        Client::TCP_Client tcpClient;
        Communication::SC_MessageHandler scMessageHandler;
        std::string roomID;
        Hive::Color ownPlayerColor;
        Hive::GameState currentGameState;
        bool gameOver = false;
        AI::HiveLogic *logic = new AI::HiveLogic();

        void ClientLoop();
        void Shutdown();

        std::vector<Communication::SC_Message> HandleIncomingMessagesAndGenerateRespones(const std::vector<Communication::SC_Message> &incomingMessages);

        Hive::Move GetNextMove();

    public:
        HiveClient(io_service &ioService);
        void Start(const ip::address &address, const unsigned short &port);
        void StartReserved(const std::string &hostanme, const unsigned short &port, const std::string &reservationCode);
    };
}  // namespace Client