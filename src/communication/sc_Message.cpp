#include "sc_Message.hpp"

namespace SC_Communication {
    SC_Message::SC_Message() {}
    
    SC_Message::SC_Message(const std::string &messageString, const SC_MessageType &messageType) {
        this->content = messageString;
        this->messageType = messageType;
    }

    std::string SC_Message::GetContent() const{
        return content;
    }

    SC_MessageType SC_Message::GetMessageType() const {
        return messageType;
    }
}  // namespace Communication