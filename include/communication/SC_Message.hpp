#pragma once

#include <string>

#include "SC_MessageType.hpp"

namespace SC_Communication {
    class SC_Message {
        private:
        std::string content;
        SC_MessageType messageType;

        public:
        SC_Message();
        SC_Message(const std::string &messageString, const SC_MessageType &messageType);
        
        std::string GetContent() const;
        SC_MessageType GetMessageType() const;
    };
}