from CoreInterface import ReadDWORD,PrintLog;
from VecObject import CVecObject;

'''
KeyName = [refresh], KeyValue = [0] Addr=[10844960]
KeyName = [difficulty], KeyValue = [1] Addr=[108447e0]
KeyName = [task_class], KeyValue = [日常] Addr=[108454a0]
KeyName = [common_type], KeyValue = [0] Addr=[10844720]
KeyName = [owner_type], KeyValue = [0] Addr=[108448a0]
KeyName = [suggest_team], KeyValue = [1人] Addr=[10844a80]
KeyName = [task_prompt], KeyValue = [在#Z官道南(156,68)#Z似乎有宝藏出现，快带上#R锄头#n前去挖宝！锄头可在#Z天墉城#Z的#P杂货店老板|杂货店老板1#P处购买。] Addr=[10844fc0]
KeyName = [count], KeyValue = [1] Addr=[10844780]
KeyName = [need_show_tip], KeyValue = [0] Addr=[10844840]
KeyName = [raw_type], KeyValue = [超级宝藏] Addr=[10844900]
KeyName = [suggest_level], KeyValue = [40级及以上] Addr=[10844a20]
KeyName = [syn_msg], KeyValue = [0] Addr=[10844f60]
KeyName = [task_desc], KeyValue = [在游戏中根据超级藏宝图进行寻宝。（下线后任务不消失）] Addr=[10845080]
KeyName = [task_reward], KeyValue = [任务结束时有几率获得：#I金钱奖励|金钱奖励#I#I变异精魄|变异精魄#I#I神兽精魄|神兽精魄#I#I其它奖励|神兽#I] Addr=[10845440]
KeyName = [task_class_ex], KeyValue = [1] Addr=[10845020]
KeyName = [task_prop], KeyValue = [0] Addr=[108457a0]
KeyName = [task_tips], KeyValue = [在游戏中根据超级藏宝图进行寻宝。（下线后任务不消失）] Addr=[10845140]
KeyName = [task_type], KeyValue = [超级宝藏] Addr=[10844f00]
'''
class CTaskObject:
    def __init__(this,dwBase):
        this._dwBase = dwBase;

    def GetBase(this):
        return this._dwBase;

    def GetAttributeTreeHead(this):
        return ReadDWORD(ReadDWORD(this.GetBase() + 0x4 + 0x4) + 0x4);

    def PrintToLog(this):
        PrintLog("------------Task[{0:x}, TreeHead[{1:x}]]----------------".format(this.GetBase(), this.GetAttributeTreeHead()))
        CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"*");

    def GetTaskType(this):
        return CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"task_type")

    def GetRawType(this):
        return CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"raw_type")

    def GetTaskPrompt(this):
        return CVecObject.FindAttributeValue_By_Key(this.GetAttributeTreeHead(),"task_prompt")

    def GetTreasureMapPos(this):
        TaskPrompt = this.GetTaskPrompt();
        MapName = TaskPrompt[TaskPrompt.find(u"在#Z") + 3 :TaskPrompt.find(u"(")];
        PosX = TaskPrompt[TaskPrompt.find(u"(") + 1 :TaskPrompt.find(u",")];
        PosY = TaskPrompt[TaskPrompt.find(u",") + 1 :TaskPrompt.find(u")")];
        return [MapName, PosX, PosY];

    def IsTreasureMapTask(this):
        return this.GetTaskType() == "超级宝藏";