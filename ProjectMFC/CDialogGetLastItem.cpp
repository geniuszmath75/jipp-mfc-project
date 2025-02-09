// CDialogGetLastItem.cpp : implementation file
//

#include "pch.h"
#include "ProjectMFC.h"
#include "afxdialogex.h"
#include "CDialogGetLastItem.h"
#include "Resource.h"


// CDialogGetLastItem dialog

IMPLEMENT_DYNAMIC(CDialogGetLastItem, CDialogEx)

CDialogGetLastItem::CDialogGetLastItem(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GET_LAST_ITEM, pParent)
	, m_last_item(_T(""))
{
	pDocum = pDoc;
	pDat = pDocum->pDat;

	if (pDat->size())
	{
		auto& last_item = (*pDat)[pDat->size() - 1];
		m_last_item.Format("Point %d\nX: %g;\tY: %g\nName: %s\nColor number: %d\nNode number: %d", pDat->size(), last_item.x, last_item.y, last_item.name, last_item.color, last_item.numb);
	}
	else
	{
		m_last_item.SetString("No points found.");
	}
}

CDialogGetLastItem::~CDialogGetLastItem()
{
}

void CDialogGetLastItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_TEXT, m_last_item);
}


BEGIN_MESSAGE_MAP(CDialogGetLastItem, CDialogEx)
END_MESSAGE_MAP()


// CDialogGetLastItem message handlers


BOOL CDialogGetLastItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
