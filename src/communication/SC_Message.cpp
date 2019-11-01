#include "SC_Message.hpp"

namespace Communication {
    SC_Message::SC_Message(const std::string &messageString, const SC_MessageType &messageType) {
        this->content = messageString;
        this->messageType = messageType;
    }
}  // namespace Communication