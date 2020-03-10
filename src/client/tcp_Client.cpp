#include "tcp_Client.hpp"

using namespace Client;

TCP_Client::TCP_Client() {
}

void TCP_Client::ConnectWithIP(std::string address, unsigned short port) {
    socket.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(address), port));
}

std::string TCP_Client::ResolveHostnameToIPAddress(std::string hostname) {
    boost::asio::ip::tcp::resolver resolver(ioService);
    boost::asio::ip::tcp::resolver::query query(hostname, "");
    boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *i;
    return endpoint.address().to_string();
}

void TCP_Client::Disconnect() {
    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();
}

void TCP_Client::SendMessage(std::string message) {
    boost::system::error_code errorCode;
    boost::asio::write(socket, boost::asio::buffer(message), errorCode);
    if (errorCode) {
        std::cout << "Sending failed: " << errorCode.message() << "\n";
    }
}

std::string TCP_Client::ReadMessage() {
    //The fix to this code was provided by Coronon. Thanks!
    boost::system::error_code errorCode;
    std::size_t bytes_transferred = boost::asio::read_until(socket, receiveBuffer, "</room>", errorCode);
    if (errorCode) {
        std::cout << "Receiving failed: " << errorCode.message() << "\n";
        throw "Receiving failed";
    } else {
        std::string message{
            boost::asio::buffers_begin(receiveBuffer.data()),
            boost::asio::buffers_begin(receiveBuffer.data()) + bytes_transferred - 7
        };
        receiveBuffer.consume(bytes_transferred);
        return message;
    }
}