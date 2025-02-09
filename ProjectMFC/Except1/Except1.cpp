// Except1.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Except1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CExcept1App

BEGIN_MESSAGE_MAP(CExcept1App, CWinApp)
END_MESSAGE_MAP()


// CExcept1App construction

CExcept1App::CExcept1App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	ptrWnd = NULL;
	ptrDat = NULL;
}


// The one and only CExcept1App object

CExcept1App theApp;


// CExcept1App initialization

BOOL CExcept1App::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


void CExcept1App::PutMessage(UINT ID_Message)
{
	HINSTANCE hInstance = GetModuleHandleA(NULL);
	char str[1024];
	int ret = LoadStringA(hInstance, ID_Message, str, sizeof(str));
	if (ptrWnd)
		ptrWnd->SendMessage(WM_DIS_MSG, (WPARAM)str, (LPARAM)ptrDat);
	else if (!ptrWnd && str[0] == 'E')
	{
		CString sstr(str);
		AfxMessageBox(sstr);
		UINT uExitCode = 0;
		HANDLE hHandle = GetCurrentProcess();
		TerminateProcess(GetCurrentProcess(), uExitCode);
	}
}

void CExcept1App::ClearOutWnd()
{
	if (ptrWnd)
		ptrWnd->SendMessage(WM_CLEAR_OUTPUT, 0, 0);
}

extern "C" CExcept1App * PASCAL EXPORT GetExceptPtr()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return &theApp;
}