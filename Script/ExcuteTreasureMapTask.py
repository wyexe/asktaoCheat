from ItemObject import CItemObject;
from TaskObject import CTaskObject
from CoreInterface import MessageBox,InvokeCALL,IsRunning,PrintLog
from VecObject import CVecObject;
from PlayerAttribute import CPlayerAttribute;
import time;

def GetItemObject(ItemName):
    Vec = []
    CVecObject.GetVecItemObject(Vec);
    for itm in Vec:
        Item = CItemObject(itm);
        if Item.GetName() == ItemName:
            return Item;

    return None;

def IsExistItem(ItemName):
    Item = GetItemObject(ItemName);
    if(Item != None):
        return True;

    return False;

# 检查特级藏宝图和特级八卦阴阳令
def CheckItem():
    return IsExistItem("特级藏宝图") and IsExistItem("特级八卦阴阳令")

# 获取藏宝图任务
def GetTreasureMapTask():
    Vec = []
    CVecObject.GetVecTaskObject(Vec);
    for itm in Vec:
        Obj = CTaskObject(itm);
        if Obj.IsTreasureMapTask():
            return Obj;

    return None;

# 使用藏宝图
def UseTreasureMap():
    Item = GetItemObject("特级藏宝图");
    if Item == None:
        return None;

    Item.UseItem();
    time.sleep(1)
    
    return GetTreasureMapTask();

# 使用锄头
def UseHoe():
    Item = GetItemObject("锄头");
    if Item == None:
        return False;

    Item.UseItem();
    time.sleep(1)
    
    return True;

# 获取特级阴阳八卦令的ID
def GetTranferTokenId():
    Item = GetItemObject("特级八卦阴阳令");
    if Item == None:
        return 0;

    return Item.GetItemUnique();

def Run():
    while CheckItem() and IsRunning():
        #MessageBox("检查藏宝图任务");
        TreasureMapTask = GetTreasureMapTask();
        if TreasureMapTask == None:
            # Use Item
            #MessageBox("不存在藏宝图任务, 准备使用藏宝图");
            TreasureMapTask = UseTreasureMap();
            if TreasureMapTask == None:
                break;

        #MessageBox("正在获取藏宝图终点");
        MapPos = TreasureMapTask.GetTreasureMapPos();
        dwTranferTokenId = GetTranferTokenId();
        if dwTranferTokenId == 0:
            MessageBox("特级八卦阴阳令没了");
            break;
        #MessageBox("藏宝图终点[{0:s},{1:s},{2:s}]".format(MapPos[0],MapPos[1],MapPos[2]));
        # 腾云驾雾传送
        PlayerId = CPlayerAttribute.GetId()
        PrintLog("PlayerId={0:X}, ItemId={1:X}".format(PlayerId, dwTranferTokenId) )
        InvokeCALL((1, PlayerId , dwTranferTokenId, MapPos[0], int(MapPos[1]),int(MapPos[2])));
        time.sleep(1);
        # 使用锄头
        UseHoe()


    MessageBox("身上的藏宝图或者八卦用完了")