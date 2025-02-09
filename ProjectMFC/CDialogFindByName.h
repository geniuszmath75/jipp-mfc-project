#pragma once
#include "afxdialogex.h"
#include "ProjectMFCDoc.h"
#include "MyData.h"

// CDialogFindByName dialog

class CDialogFindByName : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogFindByName)

public:
	CDialogFindByName(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogFindByName();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FIND_BY_NAME };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	CProjectMFCDoc* pDocum;
	MY_DATA* pDat;
	CString m_name;
	CString m_found_point;

	afx_msg void OnClickedButtonFind();
	afx_msg void OnClickedButtonClear();
};
