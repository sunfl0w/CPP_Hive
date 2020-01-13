#include "HiveClient.hpp"
#include "hiveLogic.hpp"

int main(int argc, char *argv[]) {
    AI::HiveLogic logic = AI::HiveLogic();
    Client::HiveClient client(logic);
    client.Start(argc, *argv);
    return 0;
}