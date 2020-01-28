#pragma once

namespace SC_Communication {
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