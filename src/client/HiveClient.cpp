#include "HiveClient.hpp"

using namespace boost::program_options;

namespace Client {
    HiveClient::HiveClient(AI::Logic& logic) {
        this->logic = logic;
    }

    void HiveClient::Start(int argc, char argv[]) {
        std::cout << "Hello, World! I am a c++ client!\n";
        std::cout << "Parsing arguments.\n";

        options_description optionsDesribtion("C++ client");
        optionsDesribtion.add_options()("host,h", value<std::string>()->default_value("localhost"), "Host")("port,p", value<unsigned short>()->default_value(13050), "Port")("reservation,r", value<std::string>()->default_value(""), "ReservationCode");

        variables_map varibaleMap;
        store(command_line_parser(argc, &argv).options(optionsDesribtion).run(), varibaleMap);

        std::string hostname = "localhost";
        unsigned short hostPort = 13050;
        std::string reservationCode;

        if (varibaleMap.count("host")) {
            hostname = varibaleMap["host"].as<std::string>();
        }
        if (varibaleMap.count("port")) {
            hostPort = varibaleMap["port"].as<unsigned short>();
        }
        if (varibaleMap.count("reservation")) {
            reservationCode = varibaleMap["reservation"].as<std::string>();
        }

        std::cout << "Parsing complete. Arguments are:\n";
        std::cout << "HostName: " + hostname + "\n";
        std::cout << "HostPort: " + std::to_string(hostPort) + "\n";
        std::cout << "ReservationCode: " + reservationCode + "\n";

        if (reservationCode.size() == 0) {
            std::cout << "Starting a connection.\n";
            StartConnection("127.0.0.1", hostPort);
        } else {
            std::cout << "Starting a reserved connection.\n";
            StartReservedConnection(hostname, hostPort, reservationCode);
        }
    }

    void HiveClient::ClientLoop() {
        while (!gameOver) {
            //std::cout << "Listening" << "\n";
            std::string inputStream = tcpClient.ReadMessage();
            std::vector<SC_Communication::SC_Message> messages = scMessageHandler.SplitInputMessagesIntoValidSC_Messages(inputStream);
            for (SC_Communication::SC_Message message : messages) {
                std::cout << message.GetContent() << "\n";
                //std::cerr << message.content << "\n";
            }
            std::vector<SC_Communication::SC_Message> responses = HandleIncomingMessagesAndGenerateRespones(messages);
            for (SC_Communication::SC_Message response : responses) {
                std::cout << response.GetContent() << "\n";
                //std::cerr << response.content << "\n";
                tcpClient.SendMessage(response.GetContent());
            }
            //std::cout << "Message: " << tcpClient.ReadMessage() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void HiveClient::Shutdown() {
        tcpClient.SendMessage(scMessageHandler.CreateProtocolEndMessage().GetContent());
    }

    std::vector<SC_Communication::SC_Message> HiveClient::HandleIncomingMessagesAndGenerateRespones(const std::vector<SC_Communication::SC_Message> &incomingMessages) {
        std::vector<SC_Communication::SC_Message> responseMessages;
        for (SC_Communication::SC_Message message : incomingMessages) {
            if (message.GetMessageType() == SC_Communication::SC_MessageType::Joined) {
                std::string roomId = scMessageHandler.GetRoomIDFromJoinedMessage(message);
                roomID = roomId;
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::Welcome) {
                ownPlayerColor = scMessageHandler.GetPlayerColorFromWelcomeMessage(message);
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::GameState) {
                //Hive::GameState gameState = scMessageHandler.GetGameStateFromGameStateMessage(message);
                currentGameState = scMessageHandler.GetGameStateFromGameStateMessage(message);
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::MoveRequest) {
                if (!gameOver) {
                    Hive::Move nextMove = GetNextMove();
                    responseMessages.push_back(scMessageHandler.CreateMoveMessage(nextMove, roomID));
                }
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::Left) {
                //gameOver = true;
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::Result) {
                gameOver = true;
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::Error) {
                gameOver = true;
            } else if (message.GetMessageType() == SC_Communication::SC_MessageType::ProtocolEnd) {
                gameOver = true;
            }
        }
        return responseMessages;
    }

    Hive::Move HiveClient::GetNextMove() {
        return logic.GetNextMove(currentGameState, ownPlayerColor);
    }

    void HiveClient::StartConnection(const std::string &address, const unsigned short &port) {
        tcpClient.ConnectWithIP(address, port);
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageHandler.CreateJoinRequestMessage().GetContent());
        ClientLoop();
        Shutdown();
        std::cout << "Disconnect complete. Bye.\n";
    }

    void HiveClient::StartReservedConnection(const std::string &hostname, const unsigned short &port, const std::string &reservationCode) {
        if (hostname == "localhost") {
            tcpClient.ConnectWithIP("127.0.0.1", port);
        } else {
            tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIPAddress(hostname), port);
        }
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageHandler.CreateJoinReservedRequestMessage(reservationCode).GetContent());
        ClientLoop();
        Shutdown();
        std::cout << "Disconnect complete. Bye.\n";
    }
}  // namespace Client