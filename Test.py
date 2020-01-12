import Hive, HiveLogic, sys

hiveLogic = HiveLogic.HiveLogic()
hiveClient = Hive.HiveClient(hiveLogic)
hiveClient.Start(len(sys.argv), str(sys.argv))