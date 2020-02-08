%module(directors="1") Hive

 %{
    #define SWIG_FILE_WITH_INIT
    #include "include/ai/logic.hpp"
    #include "include/client/hiveClient.hpp"
    #include "include/client/tcp_Client.hpp"
    #include "include/hive/pieceType.hpp"
    #include "include/hive/moveType.hpp"
    #include "include/hive/axialPosition.hpp"
    #include "include/hive/color.hpp"
    #include "include/hive/neighbourMap.hpp"
    #include "include/hive/piece.hpp"
    #include "include/hive/player.hpp"
    #include "include/hive/pieceStack.hpp"
    #include "include/hive/globals.hpp"
    #include "include/hive/move.hpp"
    #include "include/hive/board.hpp"
    #include "include/hive/gameState.hpp"
    #include "include/communication/sc_MessageType.hpp"
    #include "include/communication/sc_Message.hpp"
    #include "include/communication/sc_MessageHandler.hpp"
    #include "include/hive/benchmark/benchmark.hpp"
    %}

%feature("director") AI::Logic;

%include <argcargv.i>

%apply (int ARGC, char **ARGV) { (int argc, char *argv[]) }

void Client::HiveClient::Start(int argc, char *argv[]);


%include "typemaps.i"
%include "std_string.i"
%include "std_array.i"
%include "std_pair.i"
%include "std_vector.i"
%include "include/ai/logic.hpp"
%include "include/client/hiveClient.hpp"
%include "include/client/tcp_Client.hpp"
%include "include/hive/pieceType.hpp"
%include "include/hive/moveType.hpp"
%include "include/hive/axialPosition.hpp"
%include "include/hive/color.hpp"
%include "include/hive/neighbourMap.hpp"
%include "include/hive/piece.hpp"
%include "include/hive/player.hpp"
%include "include/hive/pieceStack.hpp"
%include "include/hive/globals.hpp"
%include "include/hive/move.hpp"
%include "include/hive/board.hpp"
%include "include/hive/gameState.hpp"
%include "include/communication/sc_MessageType.hpp"
%include "include/communication/sc_Message.hpp"
%include "include/communication/sc_MessageHandler.hpp"
%include "include/hive/benchmark/benchmark.hpp"

%template(SC_Message_Vector) std::vector<SC_Communication::SC_Message>;
%template(Move_Vector) std::vector<Hive::Move>;
%template(Position_Vector) std::vector<Hive::AxialPosition>;
%template(Piece_Vector) std::vector<Hive::Piece>;
%template(PieceStack_Vector) std::vector<Hive::PieceStack>;
%template(PieceStackPointer_Vector) std::vector<Hive::PieceStack*>;