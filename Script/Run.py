import sys;
import traceback;
from CoreInterface import MessageBox,ReadDWORD,PrintLog;
from VecObject import CVecObject;
from ItemObject import CItemObject;
from TaskObject import CTaskObject
import ExcuteTreasureMapTask

# 任务遍历
# 使用物品
def PrintItem():
    CVecObject.FindPlayerAttributeNumberValue_By_Key("*");
    Vec = []
    CVecObject.GetVecItemObject(Vec);
    for itm in Vec:
        Item = CItemObject(itm);
        Item.PrintToLog();

def EntryPoint():
    try:
        # Vec = []
        # CVecObject.GetVecTaskObject(Vec);
        # for itm in Vec:
        #     Obj = CTaskObject(itm);
        #     if Obj.IsTreasureMapTask():
        #         MapName,PosX,PosY = Obj.GetTreasureMapPos();
        #         PrintLog("MapName=[{0:s}], Pos=[{1:s},{2:s}]".format(MapName, PosX, PosY))
        
        ExcuteTreasureMapTask.Run()
        #PrintItem();
    except Exception as e:
        MessageBox("存在异常:" + str(e));
        excType, excValue, excTraceBack = sys.exc_info();
        Text = ''.join(traceback.format_exception(excType, excValue, excTraceBack))
        MessageBox(Text)

