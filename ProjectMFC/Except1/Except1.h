// Except1.h : main hseader file for the Except1 DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

//class MY_DATA;

#include "resource.h"		// main symbols
//#include "MyData.h"

#ifdef EXCEPT1_EXPORT
#define EXCEPT1_API __declspec(dllexport)
#else
#define EXCEPT1_API __declspec(dllimport)
#endif

// CExcept1App
// See Except1.cpp for the implementation of this class
//

#define APP_START_MESSAGE WM_USER+100

enum ITS_APP_MESSAGE
{
	WM_START = APP_START_MESSAGE,
	WM_DIS_MSG,
	WM_CLEAR_OUTPUT,
	WM_DIS_TOTALMES
};

class MY_DATA;

class EXCEPT1_API CExcept1App : public CWinApp
{
public:
	CWnd* ptrWnd;
	MY_DATA* ptrDat;

public:
	CExcept1App();
	void SetWnd(CWnd* ptrwnd, MY_DATA* pdat) { ptrWnd = ptrwnd; ptrDat = pdat; }
	void ResetDat(MY_DATA* pdat) { ptrDat = pdat; }
	void PutMessage(UINT ID_MESSAGE);
	void ClearOutWnd();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern "C" EXCEPT1_API CExcept1App * PASCAL EXPORT GetExceptPtr();