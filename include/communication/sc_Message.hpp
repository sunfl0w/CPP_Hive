#pragma once

#include <string>

#include "sc_MessageType.hpp"

namespace SC_Communication {
    /**
     * @brief A class that represents SC_Messages.
     * 
     */
    class SC_Message {
        private:
        /**
         * @brief The content of the message.
         * 
         */
        std::string content;

        /**
         * @brief The type of the message.
         * 
         */
        SC_MessageType messageType;

        public:
        /**
         * @brief Constructs a new and empty SC_Message.
         * 
         */
        SC_Message();

        /**
         * @brief Constructs a new SC_Message with given content and type.
         * 
         * @param messageString The content of the SC_Message.
         * @param messageType The type of the SC_Message.
         */
        SC_Message(const std::string &messageString, const SC_MessageType &messageType);
        
        /**
         * @brief Gets the content of the SC_Message.
         * 
         * @return The content of the SC_Message.
         */
        std::string GetContent() const;

        /**
         * @brief Gets the MessageType of the SC_Message.
         * 
         * @return he MessageType of the SC_Message.
         */
        SC_MessageType GetMessageType() const;
    };
}