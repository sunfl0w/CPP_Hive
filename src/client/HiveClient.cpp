#include "HiveClient.hpp"

namespace Client {
    HiveClient::HiveClient(io_service &ioService) : tcpClient(ioService) {}

    void HiveClient::ClientLoop() {
        while (!gameOver) {
            //std::cout << "Listening" << "\n";
            boost::system::error_code receiveErrorCode;
            std::string inputStream = tcpClient.ReadMessage(receiveErrorCode);
            if (receiveErrorCode) {
                std::cout << "Receive failed. Shutting down."
                          << "\n";
                gameOver = true;
            }
            std::vector<Communication::SC_Message> messages = scMessageHandler.SplitInputMessagesIntoValidSC_Messages(inputStream);
            for (Communication::SC_Message message : messages) {
                //std::cout << message.content << "\n";
                //std::cerr << message.content << "\n";
            }
            std::vector<Communication::SC_Message> responses = HandleIncomingMessagesAndGenerateRespones(messages);
            for (Communication::SC_Message response : responses) {
                //std::cout << response.content << "\n";
                //std::cerr << response.content << "\n";
                tcpClient.SendMessage(response.content);
            }
            //std::cout << "Message: " << tcpClient.ReadMessage() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    void HiveClient::Shutdown() {
        tcpClient.SendMessage(scMessageHandler.CreateProtocolEndMessage().content);
    }

    std::vector<Communication::SC_Message> HiveClient::HandleIncomingMessagesAndGenerateRespones(const std::vector<Communication::SC_Message> &incomingMessages) {
        std::vector<Communication::SC_Message> responseMessages;
        for (Communication::SC_Message message : incomingMessages) {
            if (message.messageType == Communication::SC_MessageType::Joined) {
                std::string roomId = scMessageHandler.GetRoomIDFromJoinedMessage(message);
                roomID = roomId;
            } else if (message.messageType == Communication::SC_MessageType::Welcome) {
                ownPlayerColor = scMessageHandler.GetPlayerColorFromWelcomeMessage(message);
            } else if (message.messageType == Communication::SC_MessageType::GameState) {
                Hive::GameState gameState = scMessageHandler.GetGameStateFromGameStateMessage(message);
                currentGameState = gameState;
            } else if (message.messageType == Communication::SC_MessageType::MoveRequest) {
                if (!gameOver) {
                    Hive::Move nextMove = GetNextMove();
                    std::string direction = "??";
                    switch (nextMove.GetDirection()) {
                        case Direction::Up_Right:
                            direction = "Up_Right";
                            break;
                        case Direction::Up:
                            direction = "Up";
                            break;
                        case Direction::Down_Right:
                            direction = "Down_Right";
                            break;
                        case Direction::Right:
                            direction = "Right";
                            break;
                        case Direction::Down_Left:
                            direction = "Down_Left";
                            break;
                        case Direction::Down:
                            direction = "Down";
                            break;
                        case Direction::Up_Left:
                            direction = "Up_Left";
                            break;
                        case Direction::Left:
                            direction = "Left";
                            break;
                    }
                    responseMessages.push_back(scMessageHandler.CreateMoveMessage(nextMove, roomID));
                }
            } else if (message.messageType == Communication::SC_MessageType::Left) {
                //gameOver = true;
            } else if (message.messageType == Communication::SC_MessageType::Result) {
                gameOver = true;
            } else if (message.messageType == Communication::SC_MessageType::Error) {
                gameOver = true;
            } else if (message.messageType == Communication::SC_MessageType::ProtocolEnd) {
                gameOver = true;
            }
        }
        return responseMessages;
    }

    Hive::Move HiveClient::GetNextMove() {
        //std::vector<Move> possibleMoves = currentGameState.GetPossibleMoves();
        //return possibleMoves[0];
        return logic->GetNextMove(currentGameState, ownPlayerColor);
    }

    void HiveClient::Start(const ip::address &address, const unsigned short &port) {
        tcpClient.ConnectWithIP(address, port);
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageHandler.CreateJoinRequestMessage().content);
        ClientLoop();
        Shutdown();
        std::cout << "Disconnect complete. Bye."
                  << "\n";
    }

    void HiveClient::StartReserved(const std::string &hostname, const unsigned short &port, const std::string &reservationCode) {
        if (hostname == "localhost") {
            tcpClient.ConnectWithIP(ip::address::from_string("127.0.0.1"), port);
            //tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIP(hostname), port);
        } else {
            tcpClient.ConnectWithIP(tcpClient.ResolveHostnameToIP(hostname), port);
        }
        tcpClient.SendMessage("<protocol>");
        tcpClient.SendMessage(scMessageHandler.CreateJoinReservedRequestMessage(reservationCode).content);
        ClientLoop();
        Shutdown();
        std::cout << "Disconnect complete. Bye."
                  << "\n";
    }
}  // namespace Client