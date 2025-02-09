#pragma once
#include "afxdialogex.h"
#include "ProjectMFCDoc.h"
#include "MyData.h"


// CDialogGetLastItem dialog

class CDialogGetLastItem : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGetLastItem)

public:
	CDialogGetLastItem(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogGetLastItem();

	MY_DATA* pDat;
	CProjectMFCDoc* pDocum;


// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GET_LAST_ITEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CString m_last_item;

};
