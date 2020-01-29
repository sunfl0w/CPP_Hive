#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace Client {
    /**
     * @brief A very basic client for managing TCP connections. It is tailored for use with the HiveCLient.
     * 
     */
    class TCP_Client {
        /**
         * @brief The ioService used by boost asio.
         * 
         */
        boost::asio::io_service ioService;

        /**
         * @brief The socket used by boost asio.
         * 
         */
        boost::asio::ip::tcp::socket socket {ioService};

    public:
        /**
         * @brief Constructs a new TCP_Client.
         * 
         */
        TCP_Client();

        /**
         * @brief Connect to a server.
         * 
         * @param ipAddress The address of the server.
         * @param port The port of the server.
         */
        void ConnectWithIP(std::string ipAddress, unsigned short port);

        /**
         * @brief Disconnetcs from the server.
         * 
         */
        void Disconnect();

        /**
         * @brief Resolves a hostname to a valid IP address.
         * 
         * @param hostname The hostname.
         * @return The IP address as a string. 
         */
        std::string ResolveHostnameToIPAddress(std::string hostname);

        /**
         * @brief Sends a string to the server.
         * 
         * @param message The string to send.
         */
        void SendMessage(std::string message);

        /**
         * @brief Receives a string from the server.
         * 
         * @return The string received from the server. 
         */
        std::string ReadMessage();
    };
}  // namespace Client