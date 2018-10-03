#ifndef __ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_SCRIPT_IPYTHON_H__
#define __ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_SCRIPT_IPYTHON_H__

#include <vector>
#include <Python.h>
#include <Core/Common/GameStruct.h>

PyMODINIT_FUNC PyInit_GameDLL();

class CIPython
{
private:
	enum em_InvokeCALL_Type
	{
		emType_UseItem,
		emType_Tranfer,
		emType_ClickNpcMenuItem
	};
private:
	struct module_state
	{
		PyObject *error;
	};
public:
	CIPython() = default;
	~CIPython() = default;

	static CIPython& GetInstance();

	BOOL Initialize();
private:
	static PyObject* Py_Error_Out(_In_ PyObject* m);

	static int Py_myextension_traverse(PyObject *m, visitproc visit, void *arg);

	static int Py_myextension_clear(PyObject* m);

	static PyObject* Py_ReadDWORD(_In_ PyObject* Self, _In_ PyObject* Args);

	static PyObject* Py_MessageBox(_In_ PyObject* Self, _In_ PyObject* Args);

	static PyObject* Py_InvokeCALL(_In_ PyObject* Self, _In_ PyObject* Args);

	static PyObject* Py_ReadText(_In_ PyObject* Self, _In_ PyObject* Args);

	static PyObject* Py_PrintLog(_In_ PyObject* Self, _In_ PyObject* Args);

	static PyObject* Py_IsRunning(_In_ PyObject* Self, _In_ PyObject* Args);

	static VOID PrintPyError();
private:
	static PyObject* EchoInvokeCALL(_In_ em_InvokeCALL_Type emType, _In_ std::vector<PyObject*>& Vec);

	BOOL ImportUserModule(_In_ CONST std::vector<std::string>& VecModuleName);

	BOOL ImportSystemModule(_In_ CONST std::vector<std::string>& VecModuleName);

	BOOL ImportModule(_In_ CONST std::vector<std::string>& VecModuleName, _Out_ std::vector<PyObject *>& VecModule) CONST;

	VOID ReleaseUserModule();

	VOID ReleaseSystemModule();

	VOID Release();
public:
	static PyModuleDef _ModuleDef;
private:
	static PyMethodDef  _PyMethodArray[];
	static module_state _PyModuleState;
	static BOOL _IsExistPythonError;
private:
	std::vector<PyObject *> _VecSystemModule;
	std::vector<PyObject *> _VecUserModule;
	BOOL _Initialized = FALSE;
};



#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_SCRIPT_IPYTHON_H__
