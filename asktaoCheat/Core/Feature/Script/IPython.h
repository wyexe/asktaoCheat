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
public:
	static PyModuleDef _ModuleDef;
private:
	static PyMethodDef  _PyMethodArray[];
	static module_state _PyModuleState;
	static BOOL _IsExistPythonError;
};



#endif // !__ASKTAOCHEAT_GAMEDLL_CORE_FEATURE_SCRIPT_IPYTHON_H__
