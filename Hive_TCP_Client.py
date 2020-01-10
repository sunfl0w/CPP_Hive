import socket

class Hive_TCP_Client: 
    def __init__(self):
        self.tcpSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def ConnectWithIP(self, ip, port):
        print(ip)
        print(port)
        self.tcpSocket.connect((ip, port))

    def Disconnect(self):
        self.tcpSocket.close()

    def SendMessage(self, message):
        self.tcpSocket.sendall(message.encode())

    def ReadMessage(self):
        isReceivedDataCoherent = False
        incomingData = ""
        while (not isReceivedDataCoherent):
            incomingData += self.tcpSocket.recv(2048).decode('utf-8')
            if(incomingData.endswith("</room>")):
                isReceivedDataCoherent = True
        return incomingData