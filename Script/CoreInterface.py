import asktaoAPI;

# Read Current Process Memory
def ReadDWORD(Addr):
    return asktaoAPI.ReadDWORD(Addr);

# API. MessageBoxW
def MessageBox(Text):
    asktaoAPI.MessageBox(Text);

# Read Current Process Memory Ptr ASCII => Unicode
def ReadText(Addr):
    return asktaoAPI.ReadText(Addr);

# asm CALL
def InvokeCALL(args):
    return asktaoAPI.InvokeCALL(args);

# Log
def PrintLog(Text):
    return asktaoAPI.PrintLog(Text);

def IsRunning():
    return asktaoAPI.IsRunning();