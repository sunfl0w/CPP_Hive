import Hive, random

class HiveLogic(Hive.Logic):
    def __init__(self):
        super(HiveLogic, self).__init__()
    
    def GetNextMove(self, currentGameState, ownPlayerColor):
        return random.choice(currentGameState.GetPossibleMoves())