#pragma once

namespace SC_Communication {
    /**
     * @brief This enum class lists all possible MessageTypes when communicating to the SC-Server.
     * 
     */
    enum class SC_MessageType
    {
        Protocol,
        ProtocolEnd,
        Welcome,
        JoinRequest,
        JoinRequestPrepared,
        Joined,
        GameState,
        Move,
        MoveRequest,
        Left,
        Result,
        Error,
        Undefined,
    };
}