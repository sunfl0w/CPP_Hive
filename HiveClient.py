import Hive_TCP_Client, argparse, socket, random, time, Hive

class HiveClient:
    def __init__(self):
        self.logic = " "
        self.tcpClient = Hive_TCP_Client.Hive_TCP_Client()
        self.scMessageHandler = Hive.SC_MessageHandler()

        self.host = "localhost"
        self.port = "13050"
        self.reservationCode = "NULL"
        self.roomID = ""
        self.gameOver = False

        self.currentGameState = Hive.GameState()
        self.playerColor = Hive.Color_Undefined

    def Start(self):
        self.scMessageHandler
        print("Hello, I am a python/C++ client!")
        print("Parsing arguments.")
        argumentParser = argparse.ArgumentParser()
        argumentParser = argparse.ArgumentParser(add_help=False)
        argumentParser.add_argument("-h", "--host", default="localhost")
        argumentParser.add_argument("-p", "--port", default="13050")
        argumentParser.add_argument("-r", "--reservation", default="NULL")
        args = argumentParser.parse_args()

        self.host = args.host
        self.port = int(args.port)
        self.reservationCode = args.reservation

        print("Parsing complete.")
        print("Host: {}".format(self.host))
        print("Port: {}".format(self.port))
        print("Reservation code: {}".format(self.reservationCode))

        if(self.reservationCode == "NULL"):
            self.StartConnection()

        pass

    def StartConnection(self):
        self.tcpClient.ConnectWithIP(socket.gethostbyname(self.host), self.port)
        self.tcpClient.SendMessage("<protocol>")
        self.tcpClient.SendMessage(self.scMessageHandler.CreateJoinRequestMessage().GetContent())
        self.ClientLoop()   
        self.ShutdownConnection()
        print("Disconnect complete. Bye.")

    def StartReservedConnection(self):
        self.tcpClient.ConnectWithIP(socket.gethostbyname(self.host), self.port)
        self.tcpClient.SendMessage("<protocol>")
        self.tcpClient.SendMessage(self.scMessageHandler.CreateJoinReservedRequestMessage(self.reservationCode).GetContent())
        self.ClientLoop()   
        self.ShutdownConnection()
        print("Disconnect complete. Bye.")

    def GetNextMove(self):
        return random.choice(self.currentGameState.GetPossibleMoves())

    def ShutdownConnection(self):
        self.tcpClient.SendMessage(self.scMessageHandler.CreateProtocolEndMessage().GetContent())

    def ClientLoop(self):
        while(not self.gameOver):
            messageFromServer = self.tcpClient.ReadMessage()
            messages = self.scMessageHandler.SplitInputMessagesIntoValidSC_Messages(messageFromServer)
            for message in messages:
                print(message.GetContent())

            responses = self.HandleIncomingMessages(messages)
            for response in responses:
                print(response.GetContent())
                self.tcpClient.SendMessage(response.GetContent())
            
            time.sleep(0.01)

    def HandleIncomingMessages(self, messagesFromServer):
        responses = list()
        for message in messagesFromServer:
            if(message.GetMessageType() == Hive.SC_MessageType_Joined):
                self.roomID = self.scMessageHandler.GetRoomIDFromJoinedMessage(message)
            elif(message.GetMessageType() == Hive.SC_MessageType_Welcome):
                self.playerColor = self.scMessageHandler.GetPlayerColorFromWelcomeMessage(message)
            elif(message.GetMessageType() == Hive.SC_MessageType_GameState):
                self.currentGameState = self.scMessageHandler.GetGameStateFromGameStateMessage(message)
            elif(message.GetMessageType() == Hive.SC_MessageType_MoveRequest):
                if(not self.gameOver):
                    nextMove = self.GetNextMove()
                    responses.append(self.scMessageHandler.CreateMoveMessage(nextMove, self.roomID))
            elif(message.GetMessageType() == Hive.SC_MessageType_Result or message.GetMessageType() == Hive.SC_MessageType_Error or message.GetMessageType() == Hive.SC_MessageType_ProtocolEnd):
                self.gameOver = True
        return responses

