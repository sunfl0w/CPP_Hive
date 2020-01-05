#include "HiveClient.hpp"
#include "Logic.hpp"

int main(int argc, char *argv[]) {
    AI::Logic logic = AI::Logic();
    Client::HiveClient client(logic);
    client.Start(argc, argv);
    return 0;
}