#include "IPython.h"
#include <frameobject.h>
#include <ProcessLib/Memory/Memory.h>
#include <LogLib/Log.h>
#include <CharacterLib/Character.h>
#include <Core/Command/Command.h>
#include <Core/Feature/CALL/GameCALL.h>

#ifdef _DEBUG
#pragma comment(lib,"ProcessLib_Debug.lib")
#pragma comment(lib,"LogLib_Debug.lib")
#pragma comment(lib,"CharacterLib_Debug.lib")
#else
#pragma comment(lib,"ProcessLib.lib")
#pragma comment(lib,"LogLib.lib")
#pragma comment(lib,"CharacterLib.lib")
#endif // _DEBUG


#define _SELF L"IPython.cpp"

BOOL CIPython::_IsExistPythonError = FALSE;
CIPython::module_state CIPython::_PyModuleState;
PyModuleDef CIPython::_ModuleDef =
{
	PyModuleDef_HEAD_INIT,
	"asktaoAPI",
	NULL,
	sizeof(CIPython::module_state),
	CIPython::_PyMethodArray,
	NULL,
	CIPython::Py_myextension_traverse,
	CIPython::Py_myextension_clear,
	NULL
};

PyMethodDef CIPython::_PyMethodArray[] =
{
	{ "ReadDWORD", CIPython::Py_ReadDWORD, METH_VARARGS, NULL },
	{ "MessageBox", CIPython::Py_MessageBox, METH_VARARGS, NULL },
	{ "ReadText", CIPython::Py_ReadText, METH_VARARGS, NULL },
	{ "PrintLog", CIPython::Py_PrintLog, METH_VARARGS, NULL },
	{ "InvokeCALL", CIPython::Py_InvokeCALL, METH_VARARGS, NULL },
	{ "IsRunning", CIPython::Py_IsRunning, METH_VARARGS, NULL },
	{ NULL, NULL, NULL, NULL }
};

CIPython& CIPython::GetInstance()
{
	static CIPython Instance;
	return Instance;
}

BOOL CIPython::Initialize()
{
	PyImport_AppendInittab("asktaoAPI", PyInit_GameDLL);
	Py_Initialize();
	auto pyBnsAPIModule = PyImport_ImportModule("asktaoAPI");
	if (pyBnsAPIModule == nullptr)
	{
		LOG_MSG_CF(L"python初始化asktaoAPI失败");
		Py_Finalize();
		return FALSE;
	}

	CONST static std::vector<std::string> VecModuleName =
	{
		"sys","traceback","time"
	};

	std::vector<PyObject *> VecModule;
	for (auto& itm : VecModuleName)
	{
		auto pyModule = PyImport_ImportModule(itm.c_str());
		if (pyModule == nullptr)
		{
			LOG_MSG_CF(L"导入[%s]模块失败", libTools::CCharacter::ASCIIToUnicode(itm).c_str());
			Py_Finalize();
			return FALSE;
		}
		VecModule.push_back(pyModule);
	}

	PySys_SetPath(L"G:\\asktao\\Script\\");
	auto pyModule = PyImport_ImportModule("Run");
	if (pyModule == nullptr)
	{
		// 
		PrintPyError();
		LOG_MSG_CF(L"python读取bns文件失败,或语法错误");
		Py_Finalize();
		return FALSE;
	}

	auto pyMain = PyObject_GetAttrString(pyModule, "EntryPoint");
	if (pyMain == nullptr)
	{
		LOG_MSG_CF(L"python入口函数错误");
		Py_Finalize();
		return FALSE;
	}


	auto pyResult = PyObject_CallObject(pyMain, nullptr);
	if (pyResult == nullptr)
	{
		LOG_MSG_CF(L"python语法错误");
	}



	for(auto& itm : VecModule)
		Py_DECREF(itm);


	Py_DECREF(pyModule);
	Py_XDECREF(pyMain);
	Py_DECREF(pyResult);
	Py_Finalize();
	return TRUE;
}

PyObject* CIPython::Py_Error_Out(_In_ PyObject*)
{
	PyErr_SetString(_PyModuleState.error, "something bad happened");
	_IsExistPythonError = TRUE;
	return nullptr;
}

int CIPython::Py_myextension_traverse(PyObject *, visitproc visit, void *arg)
{
	Py_VISIT(_PyModuleState.error);
	return 0;
}

int CIPython::Py_myextension_clear(PyObject*)
{
	Py_CLEAR(_PyModuleState.error);
	return 0;
}

PyObject* CIPython::Py_ReadDWORD(_In_ PyObject*, _In_ PyObject* Args)
{
	DWORD dwAddr = 0;
	if (!PyArg_ParseTuple(Args, "k", &dwAddr))
	{
		return nullptr;
	}

	return Py_BuildValue("k", RD(dwAddr));
}

PyObject* CIPython::Py_MessageBox(_In_ PyObject*, _In_ PyObject* Args)
{
	WCHAR* pszText = nullptr;
	if (!PyArg_ParseTuple(Args, "u", &pszText))
	{
		return nullptr;
	}

	::MessageBoxW(NULL, pszText, L"", NULL);
	return PyLong_FromLong(0);
}

PyObject* CIPython::Py_InvokeCALL(_In_ PyObject*, _In_ PyObject* Args)
{
	PyObject* pyTuple = nullptr;
	if (!PyArg_ParseTuple(Args, "O", &pyTuple))
	{
		LOG_MSG_CF(L"");
		return nullptr;
	}

	auto tupleSize = PyTuple_Size(pyTuple);
	if (tupleSize < 1 || tupleSize == -1)
	{
		LOG_MSG_CF(L"");
		return nullptr;
	}

	std::vector<PyObject *> Vec;
	for (Py_ssize_t i = 1; i < tupleSize; ++i)
	{
		Vec.push_back(PyTuple_GetItem(pyTuple, i));
	}


	// 如果取不到就是0xFFFFFFFF
	DWORD dwEnumType = PyLong_AsUnsignedLong(PyTuple_GetItem(pyTuple, 0));
	return EchoInvokeCALL(static_cast<em_InvokeCALL_Type>(dwEnumType), Vec);
}

PyObject* CIPython::Py_ReadText(_In_ PyObject*, _In_ PyObject* Args)
{
	PyObject* pyRetObject = nullptr;
	libTools::CException::InvokeAction(__FUNCTIONW__, [&] 
	{
		DWORD dwTextPtr = 0;
		if (!PyArg_ParseTuple(Args, "k", &dwTextPtr))
		{
			LOG_CF_E(L"读取Python参数失败");
			return;
		}


		if (::IsBadCodePtr((FARPROC)dwTextPtr))
		{
			LOG_CF_E(L"无效文本指针");
			return;
		}


		CONST CHAR* pszText = reinterpret_cast<CONST CHAR*>(dwTextPtr);
		std::wstring wsText = libTools::CCharacter::ASCIIToUnicode(pszText);
		wsText = libTools::CCharacter::Replace(wsText, std::wstring(L"%"), std::wstring(L""));
		pyRetObject = Py_BuildValue("u", wsText.c_str());
	});
	return pyRetObject;
}

PyObject* CIPython::Py_PrintLog(_In_ PyObject* , _In_ PyObject* Args)
{
	WCHAR* pszText = nullptr;
	if (!PyArg_ParseTuple(Args, "u", &pszText))
	{
		LOG_CF_E(L"读取Python参数失败");
		return nullptr;
	}

	LOG_C_D(pszText);
	return PyLong_FromLong(0);
}

PyObject* CIPython::Py_IsRunning(_In_ PyObject* , _In_ PyObject* )
{
	return PyLong_FromLong(g_emScriptStatus == em_Script_Status_Running ? 1 : 0);
}

VOID CIPython::PrintPyError()
{
	PyObject *type = NULL, *value = NULL, *traceback = NULL;
	PyErr_Fetch(&type, &value, &traceback);

	if (type)
	{
		MessageBoxA(NULL, PyExceptionClass_Name(type), "ErrorType", NULL);
	}

	if (value)
	{
		PyObject *line = PyObject_Str(value);
		if (line && (PyUnicode_Check(line)))
			MessageBoxA(NULL, (CHAR *)PyUnicode_1BYTE_DATA(line), "ErrorValue", NULL);
	}


	if (traceback)
	{
		for (PyTracebackObject *tb = (PyTracebackObject *)traceback;
			NULL != tb;
			tb = tb->tb_next)
		{
			PyObject *line = PyUnicode_FromFormat("  File \"%U\", line %d, in %U\n",
				tb->tb_frame->f_code->co_filename,
				tb->tb_lineno,
				tb->tb_frame->f_code->co_name);


			MessageBoxA(NULL, (CHAR *)PyUnicode_1BYTE_DATA(line), "ErrorTraceback", NULL);
		}
	}
}

PyObject* CIPython::EchoInvokeCALL(_In_ em_InvokeCALL_Type emType, _In_ std::vector<PyObject*>& Vec)
{
	static DWORD dwParam1 = 0;
	static DWORD dwParam2 = 0;
	static DWORD dwParam3 = 0;
	static DWORD dwParam4 = 0;
	DWORD dwRetCode = 0;
	WCHAR* pwszParam = nullptr;
	Py_ssize_t TextSize = 0;
	static CHAR szText[32] = { 0 };
	switch (emType)
	{
	case CIPython::emType_UseItem:
		dwParam1 = PyLong_AsUnsignedLong(Vec.at(0));
		CCommand::GetInstance().ExcutePtrToGame([&] {CGameCALL::UseItem_NoFight(dwParam1); });
		break;
	case CIPython::emType_Tranfer:
		if (Vec.size() != 5)
		{
			LOG_MSG_CF(L"参数不够!");
		}
		// ID
		dwParam1 = PyLong_AsUnsignedLong(Vec.at(0));
		// ItemId
		dwParam4 = PyLong_AsUnsignedLong(Vec.at(1));
		// PosX, PosY
		dwParam2 = PyLong_AsUnsignedLong(Vec.at(3));
		dwParam3 = PyLong_AsUnsignedLong(Vec.at(4));
		// MapName
		pwszParam = PyUnicode_AsWideCharString(Vec.at(2), &TextSize);
		if (pwszParam == nullptr)
		{
			LOG_MSG_CF(L"无效的地图名");
			return nullptr;
		}

		
		wsprintfA(szText, "%s(%d,%d)", libTools::CCharacter::UnicodeToASCII(pwszParam).c_str(), dwParam2, dwParam3);
		CCommand::GetInstance().ExcutePtrToGame([&] { CGameCALL::Tranfer(dwParam1, dwParam4, szText); });
		PyMem_Free(pwszParam);
		pwszParam = nullptr;
		break;
	default:
		break;
	}
	
	return PyLong_FromLong(dwRetCode);
}

PyMODINIT_FUNC PyInit_GameDLL()
{
	return PyModule_Create(&CIPython::_ModuleDef);
}
