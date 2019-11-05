#include <boost/program_options.hpp>
#include <boost/asio.hpp>
#include <chrono>
#include <iostream>
#include <vector>

#include "HiveClient.hpp"
#include "benchmark.hpp"

using namespace boost::program_options;

int main(int argc, char *argv[]) {
    Hive::Benchmark::BenchmarkGetPossibleMoves(10000);
    /*std::cout << "Hello, World! I am a c++ client!\n";
    std::cout << "Parsing arguments.\n";

    options_description optionsDesribtion("C++ client");
    optionsDesribtion.add_options()("host,h", value<std::string>()->default_value("localhost"), "Host")("port,p", value<unsigned short>()->default_value(13050), "Port")("reservation,r", value<std::string>()->default_value(""), "ReservationCode");

    variables_map varibaleMap;
    store(command_line_parser(argc, argv).options(optionsDesribtion).run(), varibaleMap);

    std::string hostname = "localhost";
    unsigned short hostPort = 13050;
    std::string reservationCode;

    if (varibaleMap.count("host")) {
        hostname = varibaleMap["host"].as<std::string>();
    }
    if (varibaleMap.count("port")) {
        hostPort = varibaleMap["port"].as<unsigned short>();
    }
    if (varibaleMap.count("reservation")) {
        reservationCode = varibaleMap["reservation"].as<std::string>();
    }

    std::cout << "Parsing complete. Arguments are:\n";
    std::cout << "HostName: " + hostname + "\n";
    std::cout << "HostPort: " + std::to_string(hostPort) + "\n";
    std::cout << "ReservationCode: " + reservationCode + "\n";

    boost::asio::io_service ioService;
    Client::HiveClient hiveClient(ioService);

    if (reservationCode.size() == 0) {
        std::cout << "Start.\n";
        hiveClient.Start(ip::address::from_string("127.0.0.1"), hostPort);
    } else {
        std::cout << "Start reserved.\n";
        hiveClient.StartReserved(hostname, hostPort, reservationCode);
    }*/
    return 0;
}