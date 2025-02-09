// MyData.h : main header file for the MyData DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif


#include "resource.h"		// main symbols
#include "Except1.h"

#ifdef MY_DATA_EXPORTS
#define MYDATA_API __declspec(dllexport)
#else
#define MYDATA_API __declspec(dllimport)
#endif // MY_DATA_EXPORTS

// CMyDataApp
// See MyData.cpp for the implementation of this class
//

class CMyDataApp : public CWinApp
{
public:
	CMyDataApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

class CExcept1App;

class MYDATA_API MY_COORDS
{
public:
	double x;
	double y;

public:
	MY_COORDS() : x(0), y(0) {};
};

class MYDATA_API MY_POINT : public MY_COORDS
{
public:
	char* name = NULL;
	COLORREF color;
	int numb;
	CExcept1App* logger;

	MY_POINT();
	MY_POINT(double xx, double yy, COLORREF c_color, int nnumb, const char* nname);
	MY_POINT(const MY_POINT& ob);
	~MY_POINT() 
	{ 
		if (name) 
			delete[] name;
		name = NULL;
	}

	MY_POINT& operator=(const MY_POINT& ob);
	void set(double xx, double yy, COLORREF c_color, const char* nname, int nnumb);
	MY_POINT get() { return *this; }
	bool operator==(const CString& key)
	{ 
		return CString(name) == key; 
	}
};

class MYDATA_API MY_DATA : public MY_POINT
{
protected:
	MY_POINT* pTab;
	int capacity;
	int last;
public:
	CExcept1App* pExcept;
	MY_DATA(int no_it);
	MY_DATA(const MY_DATA& ob);
	~MY_DATA() { Free(); }
	int size() { return last; }
	void Free() { if (pTab) delete[] pTab; pTab = NULL;}
	void Init(int no_it);
	void Push(const MY_POINT& tmp);
	void clear() { last = 0; }

	MY_POINT& operator [] (const int i) {
		return pTab[i];
	}
	void GetMaxMinCoords(double& max_x, double& min_x, double& max_y, double& min_y);


private:
	MY_POINT* allocTab(MY_POINT* pTab, int n);
};
