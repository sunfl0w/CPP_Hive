import Hive, HiveLogic, sys, random

print("HI PYTHON!")
hiveLogic = HiveLogic.HiveLogic()
hiveClient = Hive.HiveClient(hiveLogic)
hiveClient.Start(sys.argv)
