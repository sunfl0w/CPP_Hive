#include "SC_MessageHandler.hpp"
namespace Communication {
    SC_MessageHandler::SC_MessageHandler() {}

    std::vector<SC_Message> SC_MessageHandler::FilterProtocolMessages(std::string &inputStream) {
        std::vector<SC_Message> protocolMessages;

        //Removing non xml-compliant messages. Duhhh!
        std::size_t protocolPos = inputStream.find("<protocol>");
        if (protocolPos != std::string::npos) {
            std::string protocolMessage = inputStream.substr(protocolPos, 10);
            inputStream.erase(protocolPos, 10);
            protocolMessages.push_back(SC_Message(protocolMessage, SC_MessageType::Protocol));
        }

        std::size_t protocolEndPos = inputStream.find("</protocol>");
        if (protocolEndPos != std::string::npos) {
            std::string protocolEndMessage = inputStream.substr(protocolEndPos, 11);
            inputStream.erase(protocolEndPos, 11);
            protocolMessages.push_back(SC_Message(protocolEndMessage, SC_MessageType::ProtocolEnd));
        }

        return protocolMessages;
    }

    std::vector<SC_Message> SC_MessageHandler::SplitInputMessagesIntoValidSC_Messages(std::string inputStream) {
        std::vector<SC_Message> messages;

        std::vector<SC_Message> protocolMessages = FilterProtocolMessages(inputStream);
        messages.insert(std::end(messages), std::begin(protocolMessages), std::end(protocolMessages));

        //Wrapping xml-compliant messages for easy parsing
        inputStream.insert(0, "<SC_Message>");
        inputStream.append("</SC_Message>");

        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(inputStream.data());
        for (pugi::xml_node scMessageNode : scMessageDoc.children()) {
            for (pugi::xml_node childNode : scMessageNode.children()) {
                SC_MessageType scMessageType;
                /*std::cout << childNode.name() << "\n";
            xmlStringWriter xmlStringWriter;
            childNode.print(xmlStringWriter, " ", pugi::format_default);
            std::cout << xmlStringWriter.stringData << "\n";*/
                std::string childNodeName(childNode.name());

                //childNodeName.erase(childNodeName.find_last_not_of("\n\r") + 1);
                //childNodeName.erase(std::remove(childNodeName.begin(), childNodeName.end(), ' '), childNodeName.end());

                if (childNodeName == "join") {
                    scMessageType = SC_MessageType::JoinRequest;
                } else if (childNodeName == "joinPrepared") {
                    scMessageType = SC_MessageType::JoinRequestPrepared;
                } else if (childNodeName == "joined") {
                    scMessageType = SC_MessageType::Joined;
                } else if (childNodeName == "left") {
                    scMessageType = SC_MessageType::Left;
                } else if (childNodeName == "room") {
                    std::string classAttributeValue = childNode.child("data").attribute("class").value();
                    if (classAttributeValue == "welcomeMessage") {
                        scMessageType = SC_MessageType::Welcome;
                    } else if (classAttributeValue == "memento") {
                        scMessageType = SC_MessageType::GameState;
                    } else if (classAttributeValue == "sc.framework.plugins.protocol.MoveRequest") {
                        scMessageType = SC_MessageType::MoveRequest;
                    } else if (classAttributeValue == "result") {
                        scMessageType = SC_MessageType::Result;
                    } else if (classAttributeValue == "MSG") {
                        scMessageType = SC_MessageType::Error;
                    }
                }
                Util::XMLStringWriter xmlStringWriter;
                childNode.print(xmlStringWriter, " ", pugi::format_default);
                messages.push_back(SC_Message(xmlStringWriter.stringData, scMessageType));
            }
        }

        return messages;
    }

    SC_Message SC_MessageHandler::CreateProtocolMessage() {
        return SC_Message("<protocol>", SC_MessageType::Protocol);
    }

    SC_Message SC_MessageHandler::CreateProtocolEndMessage() {
        return SC_Message("</protocol>", SC_MessageType::ProtocolEnd);
    }

    SC_Message SC_MessageHandler::CreateJoinRequestMessage() {
        return SC_Message("<join gameType=\"swc_2020_hive\" />", SC_MessageType::JoinRequest);
    }

    SC_Message SC_MessageHandler::CreateJoinReservedRequestMessage(const std::string &reservationCode) {
        return SC_Message("<joinPrepared reservationCode=\"" + reservationCode + "\" />", SC_MessageType::JoinRequestPrepared);
    }

    SC_Message SC_MessageHandler::CreateMoveMessage(const Hive::Move &move, const std::string &roomID) {
        pugi::xml_document moveMessageDoc;

        pugi::xml_node roomNode = moveMessageDoc.append_child("room");
        roomNode.append_attribute("roomId").set_value(roomID.c_str());
        if (move.GetMoveType() == Hive::MoveType::DeployMove) {
            pugi::xml_node dataNode = roomNode.append_child("data");
            dataNode.append_attribute("class").set_value("setmove");

            pugi::xml_node pieceNode = dataNode.append_child("piece");
            pieceNode.append_attribute("owner").set_value(Hive::ColorToString(move.GetColor()).c_str());
            pieceNode.append_attribute("type").set_value(Hive::PieceTypeToString(move.GetMovedPieceType()).c_str());

            pugi::xml_node destinationNode = dataNode.append_child("destination");
            destinationNode.append_attribute("x").set_value(move.GetDestinationPosition().x);
            destinationNode.append_attribute("y").set_value(move.GetDestinationPosition().y);
            destinationNode.append_attribute("z").set_value(move.GetDestinationPosition().GetZCoordinate());
        } else if (move.GetMoveType() == Hive::MoveType::DragMove) {
            pugi::xml_node dataNode = roomNode.append_child("data");
            dataNode.append_attribute("class").set_value("dragmove");

            pugi::xml_node startNode = dataNode.append_child("start");
            startNode.append_attribute("x").set_value(move.GetStartPosition().x);
            startNode.append_attribute("y").set_value(move.GetStartPosition().y);
            startNode.append_attribute("z").set_value(move.GetStartPosition().GetZCoordinate());

            pugi::xml_node destinationNode = dataNode.append_child("destination");
            destinationNode.append_attribute("x").set_value(move.GetDestinationPosition().x);
            destinationNode.append_attribute("y").set_value(move.GetDestinationPosition().y);
            destinationNode.append_attribute("z").set_value(move.GetDestinationPosition().GetZCoordinate());
        } else if (move.GetMoveType() == Hive::MoveType::DragMove) {
            pugi::xml_node dataNode = roomNode.append_child("data");
            dataNode.append_attribute("class").set_value("missmove");
        }

        Util::XMLStringWriter xmlStringWriter;
        moveMessageDoc.print(xmlStringWriter, " ", pugi::format_default);

        return SC_Message(xmlStringWriter.stringData, SC_MessageType::Move);
    }

    Hive::Color SC_MessageHandler::GetPlayerColorFromWelcomeMessage(const SC_Message &message) {
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.content.data());
        std::string color(scMessageDoc.child("room").child("data").attribute("color").value());

        if (color == "red") {
            return Hive::Color::Red;
        } else {
            return Hive::Color::Blue;
        }
    }
    std::string SC_MessageHandler::GetRoomIDFromJoinedMessage(const SC_Message &message) {
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.content.data());
        std::string roomID(scMessageDoc.child("joined").attribute("roomId").value());
        return roomID;
    }
    Hive::GameState SC_MessageHandler::GetGameStateFromGameStateMessage(const SC_Message &message) {
        Hive::GameState gameState;
        pugi::xml_document scMessageDoc;
        scMessageDoc.load_string(message.content.data());
        pugi::xml_node roomNode = scMessageDoc.child("room");

        for (pugi::xml_attribute stateAttribute : roomNode.child("data").child("state").attributes()) {
            std::string stateAttributeName(stateAttribute.name());
            if (stateAttributeName == "turn") {
                gameState.SetTurn(std::stoi(std::string(stateAttribute.value())));
            } else if (stateAttributeName == "currentPlayerColor") {
                std::string currentPlayerColor = std::string(stateAttribute.value());
                std::string pausedPlayerColor = "UNDEFINED";
                if (currentPlayerColor == "RED") {
                    pausedPlayerColor = "BLUE";
                } else if (currentPlayerColor == "BLUE") {
                    pausedPlayerColor = "RED";
                }

                if(currentPlayerColor == "RED") {
                    gameState.SetCurrentPlayer(Hive::Player(Hive::Color::Red));
                    gameState.SetPausedPlayer(Hive::Player(Hive::Color::Blue));
                } else {
                    gameState.SetCurrentPlayer(Hive::Player(Hive::Color::Blue));
                    gameState.SetPausedPlayer(Hive::Player(Hive::Color::Red));
                }
            }
        }

        for (pugi::xml_node fieldsNode : roomNode.child("data").child("state").child("board").children()) {
            for (pugi::xml_node fieldNode : fieldsNode.children("field")) {
                Hive::AxialPosition position;
                for (pugi::xml_attribute fieldAttribute : fieldNode.attributes()) {
                    std::string fieldAttributeName(fieldAttribute.name());
                    if (fieldAttributeName == "x") {
                        std::string x = std::string(fieldAttribute.value());
                        position.x = std::stoi(x);
                    } else if (fieldAttributeName == "y") {
                        std::string y = std::string(fieldAttribute.value());
                        position.y = std::stoi(y);
                    }
                }

                for (pugi::xml_node pieceNode : fieldNode.children("piece")) {
                    std::string pieceColor = pieceNode.attribute("owner").value();
                    std::string pieceType = pieceNode.attribute("type").value();

                    gameState.GetBoard().AddPieceOnTop(Hive::Piece(Hive::PieceTypeFromString(pieceType), Hive::ColorFromString(pieceColor)), position);
                }
            }
        }

        for (pugi::xml_node pieceNode : roomNode.child("data").child("state").child("undeployedRedPieces").children("piece")) {
            std::string pieceColor = pieceNode.attribute("owner").value();
            std::string pieceType = pieceNode.attribute("type").value();

            gameState.GetPlayer(Hive::Color::Red).AddUndeployedPiece(Hive::Piece(Hive::PieceTypeFromString(pieceType), Hive::ColorFromString(pieceColor)));
        }

        for (pugi::xml_node pieceNode : roomNode.child("data").child("state").child("undeployedBluePieces").children("piece")) {
            std::string pieceColor = pieceNode.attribute("owner").value();
            std::string pieceType = pieceNode.attribute("type").value();

            gameState.GetPlayer(Hive::Color::Blue).AddUndeployedPiece(Hive::Piece(Hive::PieceTypeFromString(pieceType), Hive::ColorFromString(pieceColor)));
        }

        return gameState;
    }
}  // namespace Communication