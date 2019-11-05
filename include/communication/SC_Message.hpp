#pragma once

#include <string>

#include "SC_MessageType.hpp"

namespace Communication {
    struct SC_Message {
        std::string content;
        SC_MessageType messageType;

        SC_Message(const std::string &messageString, const SC_MessageType &messageType);
    };
}