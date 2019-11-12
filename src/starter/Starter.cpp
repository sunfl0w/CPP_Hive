#include <boost/asio.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <vector>

#include "HiveClient.hpp"
#include "benchmark.hpp"

#include "AxialPosition.hpp"
#include "Color.hpp"
#include "Piece.hpp"
#include "PieceStack.hpp"
#include "PieceType.hpp"
#include "board.hpp"
#include "gameState.hpp"

using namespace boost::program_options;
using namespace Hive;

int main(int argc, char *argv[]) {
    //You might run the benchmark here
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

    /*GameState gameState;
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Red), AxialPosition(0, 4));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Beetle, Color::Red), AxialPosition(0, 4));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::QueenBee, Color::Red), AxialPosition(1, 3));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Red), AxialPosition(2, 2));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Red), AxialPosition(2, 3));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Red), AxialPosition(3, 1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Red), AxialPosition(4, 0));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Grasshopper, Color::Red), AxialPosition(3, 0));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Red), AxialPosition(1, 1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Grasshopper, Color::Red), AxialPosition(1, -2));

    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Blue), AxialPosition(3, -1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Grasshopper, Color::Blue), AxialPosition(4, -2));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Blue), AxialPosition(1, -0));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Beetle, Color::Blue), AxialPosition(1, -0));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Beetle, Color::Blue), AxialPosition(1, -1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::QueenBee, Color::Blue), AxialPosition(2, -1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Blue), AxialPosition(3, -2));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Blue), AxialPosition(4, -3));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Spider, Color::Blue), AxialPosition(3, -3));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Grasshopper, Color::Blue), AxialPosition(2, -3));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Ant, Color::Blue), AxialPosition(1, -3));

    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Obstacle, Color::Undefined), AxialPosition(0, 5));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Obstacle, Color::Undefined), AxialPosition(0, 1));
    gameState.GetBoard().AddPieceOnTop(Piece(PieceType::Obstacle, Color::Undefined), AxialPosition(4, -4));

    std::vector<Move> possibleMoves = gameState.GetPossibleMoves();
    int i = 0;*/

    return 0;
}