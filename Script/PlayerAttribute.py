from VecObject import CVecObject;

'''
KeyName = [mag_power], KeyValue = [1862]    # 基础法伤
KeyName = [phy_power], KeyValue = [6959]    # 基础物伤
KeyName = [speed], KeyValue = [443]         # 基础速度
KeyName = [double_hit_rate], KeyValue = [18]# 爆击几率?
KeyName = [max_mana], KeyValue = [31970]    # 基础最大蓝
KeyName = [str], KeyValue = [54]            # 基础力量
KeyName = [max_life], KeyValue = [2555]     # 基础最大血
KeyName = [def], KeyValue = [1793]          # 基础防御
KeyName = [all_polar], KeyValue = [55]      # 基础所有相性
'''

'''
KeyName = [mag_power], KeyValue = [2448]    # 增益的法伤
KeyName = [privilege], KeyValue = [0]       # GM权限?
KeyName = [title], KeyValue = [新入道途]     # 称谓
KeyName = [extra_life], KeyValue = [70362974]   # 血池的HP
KeyName = [max_life], KeyValue = [18780]     # 增益的最大血
KeyName = [party/level], KeyValue = [0]      # 帮派等级?
KeyName = [str], KeyValue = [439]           # 增益的力量
KeyName = [tao], KeyValue = [901624]        # 道行(按照360算一年)
KeyName = [title_effect], KeyValue = [新入道途] # 激活效果的称谓
KeyName = [vip_info/level], KeyValue = [6]  # VIP等级?
KeyName = [voucher], KeyValue = [496703]    # 代金卷
KeyName = [master], KeyValue = [彩云童子]    # 师父名称
KeyName = [max_cash], KeyValue = [55546605] # 最大金币上限
KeyName = [speed], KeyValue = [496]         # 增益的速度
KeyName = [tao_ex], KeyValue = [1112]       # 额外的道行?
KeyName = [vip_info/next_vip_score], KeyValue = [5000000]   # VIP积分?
KeyName = [x], KeyValue = [67]              # 坐标
KeyName = [family], KeyValue = [骷髅山白骨洞]   # 门派
KeyName = [hide], KeyValue = [0]                # GM功能, 是否隐藏自己?
KeyName = [life], KeyValue = [20043]            # 增益的HP
KeyName = [map_id], KeyValue = [16000]          # 当前地图ID
KeyName = [max_mana], KeyValue = [10991]        # 增益的MP
KeyName = [name], KeyValue = [无忧无求]         # 当前人物的名字
KeyName = [phy_power], KeyValue = [23363]       # 当前物伤
KeyName = [pot], KeyValue = [196955]            # 潜能
KeyName = [total_score], KeyValue = [14590]     # 潜能
KeyName = [y], KeyValue = [221]                 #坐标 Y
KeyName = [exp], KeyValue = [1409105]           # 经验
KeyName = [exp_to_next_level], KeyValue = [2929878] # MAX经验
KeyName = [extra_mana], KeyValue = [70152225]   # 蓝池
KeyName = [id], KeyValue = [38643]              # 人物ID
KeyName = [level], KeyValue = [89]              # 等级
KeyName = [mana], KeyValue = [42315]            # 增益的蓝
KeyName = [map_name], KeyValue = [骷髅山]       # 所在地图
KeyName = [silver_coin], KeyValue = [71593106]  # 银元宝
KeyName = [cash], KeyValue = [20999471]         # 金币
KeyName = [gold_coin], KeyValue = [99180231]    # 金元宝
KeyName = [account_name], KeyValue = [1]        # 账号
'''

class CPlayerAttribute:
    @staticmethod
    def GetPercentHP():
        MaxHP = CVecObject.FindPlayerAttributeNumberValue_By_Key("max_life");
        if MaxHP == 0:
            return 0;

        HP = CVecObject.FindPlayerAttributeNumberValue_By_Key("life");
        return HP * 100 / MaxHP;


    @staticmethod
    def GetPercentMP():
        MaxMP = CVecObject.FindPlayerAttributeNumberValue_By_Key("max_mana");
        if MaxMP == 0:
            return 0;

        MP = CVecObject.FindPlayerAttributeNumberValue_By_Key("mana");
        return MP * 100 / MaxMP;


    # 战绩
    @staticmethod
    def GetTotalScore():
        return CVecObject.FindPlayerAttributeNumberValue_By_Key("total_score");

    @staticmethod
    def GetCurrentMapName():
        return CVecObject.FindPlayerAttributeTextValue_By_Key("map_name");

    @staticmethod
    def GetCurrentPoint():
        return [CVecObject.FindPlayerAttributeNumberValue_By_Key("x"),CVecObject.FindPlayerAttributeNumberValue_By_Key("y")]

    @staticmethod
    def GetId():
        return CVecObject.FindPlayerAttributeNumberValue_By_Key("id");