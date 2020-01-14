%module(directors="1") Hive
    %{
    #define SWIG_FILE_WITH_INIT
    #include "include/ai/Logic.hpp"
    #include "include/client/HiveClient.hpp"
    #include "include/client/TCP_Client.hpp"
    #include "include/hive/PieceType.hpp"
    #include "include/hive/MoveType.hpp"
    #include "include/hive/AxialPosition.hpp"
    #include "include/hive/Color.hpp"
    #include "include/hive/neighbourMap.hpp"
    #include "include/hive/Piece.hpp"
    #include "include/hive/Player.hpp"
    #include "include/hive/PieceStack.hpp"
    #include "include/hive/globals.hpp"
    #include "include/hive/Move.hpp"
    #include "include/hive/board.hpp"
    #include "include/hive/gameState.hpp"
    #include "include/communication/SC_MessageType.hpp"
    #include "include/communication/SC_Message.hpp"
    #include "include/communication/SC_MessageHandler.hpp"
    #include "include/hive/benchmark/benchmark.hpp"
    %}
%feature("director") AI::Logic;

%include <argcargv.i>

%apply (int ARGC, char **ARGV) { (int argc, char *argv[]) }

void Hive::HiveClient::Start(int argc, char *argv[]);

%include "typemaps.i"
%include "std_string.i"
%include "std_array.i"
%include "std_pair.i"
%include "std_vector.i"
%include "include/ai/Logic.hpp"
%include "include/client/HiveClient.hpp"
%include "include/client/TCP_Client.hpp"
%include "include/hive/PieceType.hpp"
%include "include/hive/MoveType.hpp"
%include "include/hive/AxialPosition.hpp"
%include "include/hive/Color.hpp"
%include "include/hive/neighbourMap.hpp"
%include "include/hive/Piece.hpp"
%include "include/hive/Player.hpp"
%include "include/hive/PieceStack.hpp"
%include "include/hive/globals.hpp"
%include "include/hive/Move.hpp"
%include "include/hive/board.hpp"
%include "include/hive/gameState.hpp"
%include "include/communication/SC_MessageType.hpp"
%include "include/communication/SC_Message.hpp"
%include "include/communication/SC_MessageHandler.hpp"
%include "include/hive/benchmark/benchmark.hpp"

%template(SC_Message_Vector) std::vector<SC_Communication::SC_Message>;
%template(Move_Vector) std::vector<Hive::Move>;
%template(Position_Vector) std::vector<Hive::AxialPosition>;
%template(Piece_Vector) std::vector<Hive::Piece>;
%template(PieceStack_Vector) std::vector<Hive::PieceStack>;