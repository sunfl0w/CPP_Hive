import Hive, random

class HiveLogic(Hive.Logic):
    def __init__(self):
        Hive.Logic.__init__(self)
    
    def GetNextMove(self, currentGameState: "Hive::GameState", ownPlayerColor: "Hive::Color")  -> "Hive::Move":
        print("Hello there.")
        return random.choice(currentGameState.GetPossibleMoves())

    def OnGameEnd(self, colorOfWinningPlayer: "Hive::Color"):
        print("Winning player has the color: " + Hive.ColorToString(colorOfWinningPlayer))