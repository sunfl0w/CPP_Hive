import Hive, random

class HiveLogic(Hive.Logic):
    def __init__(self):
        Hive.Logic.__init__(self)
    
    def GetNextMove(self, currentGameState: "GameState", ownPlayerColor: "Hive::Color")  -> "Hive::Move":
        print("Hello there.")
        return random.choice(currentGameState.GetPossibleMoves())