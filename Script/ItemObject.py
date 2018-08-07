from CoreInterface import ReadDWORD,PrintLog,InvokeCALL;
from VecObject import CVecObject;

'''
KeyName = [name], KeyValue = [九天龙腾套装·男]       #名字
KeyName = [color], KeyValue = [金色]                # 颜色
KeyName = [item_type], KeyValue = [1]               # 物品类型
KeyName = [req_level], KeyValue = [0]               # 要求等级
KeyName = [server_count], KeyValue = [1]
KeyName = [type], KeyValue = [8]
KeyName = [durability], KeyValue = [0]
KeyName = [max_durability], KeyValue = [0]
KeyName = [pos], KeyValue = [31]
'''

class CItemObject:
    def __init__(this,dwBase):
        this._dwBase = dwBase;


    def GetBase(this):
        return this._dwBase;


    def GetAttributeTreeHead(this):
        return ReadDWORD(ReadDWORD(ReadDWORD(this.GetBase() + 0x10) + 0x4 + 0x4 + 0x4) + 0x4);


    def PrintToLog(this):
        PrintLog("------------Item[{0:x}, Obj=[{1:x}] TreeHead[{2:x}]]----------------".format(this.GetBase(),ReadDWORD(this.GetBase() + 0x10), this.GetAttributeTreeHead()))
        CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"*");


    def GetPercentDurability(this):
        MaxDurability = int(CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"durability"));
        if MaxDurability == 0:
            return 0;

        CurDurability = int(CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"max_durability"));
        return CurDurability * 100 / MaxDurability;


    def GetName(this):
        return CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"name");

    
    @staticmethod
    def GetMaxItemCount():
        return 5 * 4 * 4; # 5行 * 4列 * 4个背包(2个普通背包 + 1个会员背包 + 1个坐骑背包)

    def GetPos(this):
        return int(CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"pos"));
    
    def UseItem(this):
        InvokeCALL((0x0, this.GetPos()))

    def GetItemUnique(this):
        return int(CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"item_unique"));