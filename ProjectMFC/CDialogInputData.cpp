// CDialogInputData.cpp : implementation file
//

#include "pch.h"
#include "ProjectMFC.h"
#include "CDialogInputData.h"
#include "afxdialogex.h"
#include <iostream>
#include "Except1.h"


// CDialogInputData dialog

IMPLEMENT_DYNAMIC(CDialogInputData, CDialogEx)

CDialogInputData::CDialogInputData(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_INPUTDATA, pParent)
	, m_name(_T(""))
	, m_X(0)
	, m_Y(0)
{
	pDocum = pDoc;
	memset((void*)&lvi, 0, sizeof(LVITEMA));
	pDat = pDocum->pDat;
	pExcept = GetExceptPtr();
	pExcept->ResetDat(pDat);
}

CDialogInputData::~CDialogInputData()
{
	m_smallImageList.DeleteImageList();
}

void CDialogInputData::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CTRL, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_X, m_X);
	DDX_Text(pDX, IDC_EDIT_Y, m_Y);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
}


BEGIN_MESSAGE_MAP(CDialogInputData, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CDialogInputData::OnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CDialogInputData::OnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CDialogInputData::OnClickedButtonDel)
	ON_BN_CLICKED(IDOK, &CDialogInputData::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LIST_CTRL, &CDialogInputData::OnItemchangingListCtrl)
	ON_BN_CLICKED(IDC_BUTTON_DEL_ALL, &CDialogInputData::OnClickedButtonDelAll)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CDialogInputData::OnClickedButtonColor)
END_MESSAGE_MAP()


// CDialogInputData message handlers

BOOL CDialogInputData::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	VERIFY(m_ColorBox.SubclassDlgItem(IDC_STATIC_COLOR, this));
	
	CString strx, stry, name, color;

	lvi.mask = LVIF_TEXT;
	lvi.state = 0;
	lvi.stateMask = 0;
	lvi.iImage = 0;

	HICON hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_ProjectMFCTYPE));

	m_smallImageList.Create(16, 16, FALSE, 1, 0);
	m_smallImageList.Add(hIcon);
	m_ListCtrl.SetImageList(&m_smallImageList, LVSIL_SMALL);

	CRect rectListCtrl;
	memset(rectListCtrl, 0, sizeof(rectListCtrl));
	m_ListCtrl.GetClientRect(&rectListCtrl);

	int list_ctrl_width = rectListCtrl.right - rectListCtrl.left;
	int column_width = list_ctrl_width / 4;

	int ret;
	int nFormat = LVCFMT_LEFT;
	ret = m_ListCtrl.InsertColumn(0, "name", nFormat, column_width, 0);
	ret = m_ListCtrl.InsertColumn(1, "X", nFormat, column_width, 1);
	ret = m_ListCtrl.InsertColumn(2, "Y", nFormat, column_width, 2);
	ret = m_ListCtrl.InsertColumn(3, "color", nFormat, column_width, 3);

	ASSERT(pDat);
	int no_item = pDat->size();

	lvi.iSubItem = 0;
	m_ListCtrl.SetItemCount(no_item);

	for (int i = 0; i < no_item; i++)
	{
		MY_POINT pt = (*pDat)[i];
		lvi.iItem = i;

		name = CString(pt.name);
		size_t Len = strlen(name);
		
		strx.Format("%le", pt.x);
		Len += strlen(strx);

		stry.Format("%le", pt.y);
		Len += strlen(stry);
		
		color.Format("%ld", pt.color);
		Len += strlen(color);

		lvi.pszText = "";
		lvi.cchTextMax = (int)Len;
		ret = m_ListCtrl.InsertItem(&lvi);

		m_ListCtrl.SetItemText(lvi.iItem, 0, name);
		m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 3, color);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDialogInputData::ModifyData()
{
	try
	{
		BOOL ret(0);
		MY_POINT tmp;
		
		UpdateData(TRUE);
		const int no_it(m_ListCtrl.GetItemCount());

		if (pDat)
			delete pDat;
		pDocum->pDat = pDat = new MY_DATA(no_it);

		
		char* buffer;
		for (int nItem = 0; nItem < no_it; ++nItem)
		{
			CString sname;
			char st[512];

			m_ListCtrl.GetItemText(nItem, 0, st, sizeof(st));
			sname = st;
			buffer = new char[sname.GetLength() + 1];
			strcpy_s(buffer, sname.GetLength() + 1, sname);
			tmp.name = buffer;

			m_ListCtrl.GetItemText(nItem, 1, st, sizeof(st));
			tmp.x = atof(st);

			m_ListCtrl.GetItemText(nItem, 2, st, sizeof(st));
			tmp.y = atof(st);

			m_ListCtrl.GetItemText(nItem, 3, st, sizeof(st));
			tmp.color = atol(st);

			tmp.numb = nItem + 1;
			
			pDat->Push(tmp);
			delete[] buffer;
			buffer = NULL;
			tmp.name = NULL;
		}

		UpdateData(FALSE);

		ASSERT_VALID(pDocum);
		pDocum->SetModifiedFlag();
		pDocum->UpdateAllViews(NULL);
	}
	catch (...)
	{
		pExcept->ptrWnd = NULL;
		pExcept->PutMessage(1014);
	}
}

void CDialogInputData::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	ModifyData();
}

void CDialogInputData::OnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	try
	{
		int nItem = m_ListCtrl.GetItemCount();
		int ret = -1;
		CString strx, stry, color, name;

		UpdateData(TRUE);
		name = m_name;
		if (name == "" || name == "P-")
		{
			CString strNumber;
			strNumber.Format(_T("%d"), nItem + 1);
			name = "P-" + strNumber;
		}
		size_t Len = strlen(name);

		strx.Format("%le", m_X);
		Len += strlen(strx);

		stry.Format("%le", m_Y);
		Len += strlen(stry);

		color.Format("%ld", m_ColorBox.color);
		Len += strlen(color);

		lvi.iItem = nItem;
		lvi.pszText = "";
		lvi.cchTextMax = (int)Len;

		ret = m_ListCtrl.InsertItem(&lvi);
		m_ListCtrl.SetItemText(lvi.iItem, 0, name);
		m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 3, color);

		UpdateData(FALSE);
		ASSERT_VALID(pDocum);
		pDocum->SetModifiedFlag();
		pDocum->UpdateAllViews(NULL);

		pExcept->PutMessage(1004);
	}
	catch (...)
	{
		pExcept->ptrWnd = NULL;
		pExcept->PutMessage(1013);
	}
	
}


void CDialogInputData::OnClickedButtonMod()
{
	// TODO: Add your control notification handler code here
	try
	{
		int no_item = m_ListCtrl.GetItemCount();
		int ret = -1;

		if (m_SelItem < 0 || m_SelItem >= no_item)
			return;

		CString strx, stry, color, name;
		int nItem = m_SelItem;

		UpdateData(TRUE);

		name = m_name;
		size_t Len = strlen(name);

		strx.Format("%le", m_X);
		Len += strlen(strx);

		stry.Format("%le", m_Y);
		Len += strlen(stry);

		color.Format("%ld", m_ColorBox.color);
		Len += strlen(color);

		

		lvi.iItem = nItem;
		m_ListCtrl.SetItemText(lvi.iItem, 0, name);
		m_ListCtrl.SetItemText(lvi.iItem, 1, strx);
		m_ListCtrl.SetItemText(lvi.iItem, 2, stry);
		m_ListCtrl.SetItemText(lvi.iItem, 3, color);

		UpdateData(FALSE);
		ModifyData();
		pExcept->PutMessage(1005);
	}
	catch (...)
	{
		pExcept->ptrWnd = NULL;
		pExcept->PutMessage(1014);
	}
	
}


void CDialogInputData::OnClickedButtonDel()
{
	// TODO: Add your control notification handler code here
	try
	{
		int ret = -1;
		UpdateData(TRUE);

		int no_item = m_ListCtrl.GetItemCount();

		if (m_SelItem < 0 || m_SelItem >= no_item)
			return;

		m_ListCtrl.DeleteItem(m_SelItem);
		UpdateData(FALSE);

		ASSERT_VALID(pDocum);
		pDocum->SetModifiedFlag();
		pDocum->UpdateAllViews(NULL);
		pExcept->PutMessage(1006);
	}
	catch (...)
	{
		pExcept->ptrWnd = NULL;
		pExcept->PutMessage(1015);
	}
	
}

void CDialogInputData::OnClickedButtonDelAll()
{
	// TODO: Add your control notification handler code here
	if (m_ListCtrl.GetItemCount() == 0) return;

	try
	{
		int ret = -1;
		UpdateData(TRUE);
		m_ListCtrl.DeleteAllItems();
		UpdateData(FALSE);

		ASSERT_VALID(pDocum);
		pDocum->SetModifiedFlag();
		pDocum->UpdateAllViews(NULL);
		pExcept->PutMessage(1007);
	}
	catch (...)
	{
		pExcept->ptrWnd = NULL;
		pExcept->PutMessage(1016);
	}
}

void CDialogInputData::OnItemchangingListCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	UpdateData(TRUE);

	int nItem = m_SelItem = pNMLV->iItem;
	int no_item = m_ListCtrl.GetItemCount();

	if (m_SelItem < 0 || m_SelItem >= no_item)
		return;

	int ncol = 0;
	char st[512];
	CString name;

	BOOL ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	name = st;
	char* buffer = new char[name.GetLength() + 1];
	strcpy_s(buffer, name.GetLength() + 1, name);
	m_name = buffer;

	delete[] buffer;
	buffer = NULL;

	ncol = 1;
	m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	m_X = atof(st);

	ncol = 2;
	ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	m_Y = atof(st);
	
	ncol = 3;
	ret = m_ListCtrl.GetItemText(nItem, ncol, st, sizeof(st));
	m_ColorBox.color = atol(st);

	m_ColorBox.SetColor(m_ColorBox.color);
	m_ColorBox.Invalidate();

	UpdateData(FALSE);
}

void CDialogInputData::OnClickedButtonColor()
{
	// TODO: Add your control notification handler code here
	CColorDialog dlg;

	if (dlg.DoModal())
	{
		m_ColorBox.SetColor(dlg.GetColor());
		m_ColorBox.Invalidate();
	}
}
BEGIN_MESSAGE_MAP(CColorBox, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CColorBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CStatic::OnPaint() for painting messages

	CRect rect;
	this->GetClientRect(&rect);

	CBrush newbrush;
	CBrush* oldbrush;
	newbrush.CreateSolidBrush(color);
	oldbrush = dc.SelectObject(&newbrush);

	dc.Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));

	dc.SelectObject(oldbrush);
	newbrush.DeleteObject();
}