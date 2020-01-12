#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <string>

namespace Client {
    class TCP_Client {
        boost::asio::io_service ioService;
        boost::asio::ip::tcp::socket socket {ioService};

    public:
        TCP_Client();

        void ConnectWithIP(std::string ipAddress, unsigned short port);

        void Disconnect();

        std::string ResolveHostnameToIPAddress(std::string hostname);

        void SendMessage(std::string message);

        std::string ReadMessage();
    };
}  // namespace Client