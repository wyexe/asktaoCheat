from CoreInterface import ReadDWORD,ReadText,PrintLog

class CVecObject:
    # Read Text in Memory Text End is '\0'
    @staticmethod
    def ReadTextWithLen(Addr):
        Text = "EmptyText";
        if ReadDWORD(Addr + 0x14) <= 0xF:
            Text = ReadText(Addr);
        else:
            Text = ReadText(ReadDWORD(Addr));
        
        return Text;

    # Binary Tree Attribute Table
    @staticmethod
    def FindAttributeValue_By_Key(TreeHead, KeyName):
        Vec = [ TreeHead ];

        while(len(Vec) != 0):
            Addr = Vec[0];
            Vec.pop(0);

            # BFS
            if ReadDWORD(Addr + 0x45) & 0xFF == 0:
                # Add Left Tree & Right Tree
                Vec.append(ReadDWORD(Addr + 0x0));
                Vec.append(ReadDWORD(Addr + 0x8));

                if (ReadDWORD(Addr + 0x10) & 0xFF != 0) and (ReadDWORD(Addr + 0x10 + 0x10) & 0xFF != 0) and (ReadDWORD(Addr + 0x10 + 0x10) & 0xFF) < 32 and (ReadDWORD(Addr + 0x2C) & 0xFF != 0) and (ReadDWORD(Addr + 0x2C + 0x10) & 0xFF < 128):
                    AttributeKeyNameText = CVecObject.ReadTextWithLen(Addr + 0x10);
                    if KeyName == "*":
                        PrintLog("KeyName = [{0:s}], KeyValue = [{1:s}] Addr=[{2:x}]".format(AttributeKeyNameText,CVecObject.ReadTextWithLen(Addr + 0x2C),Addr))
                        continue;
                    if AttributeKeyNameText == KeyName:
                        return CVecObject.ReadTextWithLen(Addr + 0x2C);


        return "EmptyText";

    # Player Attribute (Number)
    def FindPlayerAttributeNumberValue_By_Key(KeyName):
        RetValue1 = "";
        TreeHead = ReadDWORD(ReadDWORD(ReadDWORD(0xD09C0C) + 0x104 + 0x4 + 0x4) + 0x4);
        RetValue1 = CVecObject.FindAttributeValue_By_Key(TreeHead,KeyName);
        if not RetValue1.isdigit():
            return 0;
        
        TreeHead = ReadDWORD(ReadDWORD(ReadDWORD(0xD09C0C) + 0xCC + 0x4 + 0x4) + 0x4);
        RetValue2 = CVecObject.FindAttributeValue_By_Key(TreeHead,KeyName);
        if not RetValue2.isdigit():
            return int(RetValue1);

        return int(RetValue1) + int(RetValue2)

    # Player Attribute (Text)
    @staticmethod
    def FindPlayerAttributeTextValue_By_Key(KeyName):
        TreeHead = ReadDWORD(ReadDWORD(ReadDWORD(0xD09C0C) + 0x104 + 0x4 + 0x4) + 0x4);
        RetValue = CVecObject.FindAttributeValue_By_Key(TreeHead,KeyName);
        if RetValue != "EmptyText":
            return RetValue;
        
        TreeHead = ReadDWORD(ReadDWORD(ReadDWORD(0xD09C0C) + 0xCC + 0x4 + 0x4) + 0x4);
        RetValue = CVecObject.FindAttributeValue_By_Key(TreeHead,KeyName);
        if RetValue != "EmptyText":
            return RetValue;

        return "EmptyText";


    @staticmethod
    def GetVecItemObject(VecItem):
        # 0045288F  |.  8B0D 4864D000 mov     ecx, dword ptr [D06448]                          ;  背包遍历基址
        dwTreeHead = ReadDWORD(ReadDWORD(ReadDWORD(0xD06448) + 0x14 + 0x4) + 0x4);
        Vec = [dwTreeHead];

        # Binary 
        Count = 0;
        while len(Vec) != 0 and Count < 100:
            Addr = Vec[0];
            Vec.pop(0);
            Count += 1;
            if ReadDWORD(Addr + 0x15) & 0xFF == 0:
               # Add Left Tree
                Vec.append(ReadDWORD(Addr + 0x0)); 
               # Add Right Tree
                Vec.append(ReadDWORD(Addr + 0x8));

                if(ReadDWORD(Addr + 0xC) != 0):
                    VecItem.append(Addr);


    @staticmethod
    def GetVecTaskObject(VecTask):
        # 004FE9EC   > \8B0D 9091D000 mov     ecx, dword ptr [D09190]
        # 0068BD43  |.  8BB1 8C000000 mov     esi, dword ptr [ecx+8C]

        Addr = ReadDWORD(0xD09190) + 0x8C;
        ArrayHead = ReadDWORD(Addr);
        ArrayCount = (ReadDWORD(Addr + 0x4) - ArrayHead) / 4;
        if(ArrayCount < 100):
            for i in range(int(ArrayCount)):
                TaskObject = ReadDWORD(ArrayHead + i * 4);
                VecTask.append(TaskObject);