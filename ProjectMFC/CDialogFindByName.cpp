// CDialogFindByName.cpp : implementation file
//

#include "pch.h"
#include "ProjectMFC.h"
#include "afxdialogex.h"
#include "CDialogFindByName.h"


// CDialogFindByName dialog

template <class T, class Key>
T* find(const T* p_begin, const T* p_end, const Key& k)
{
	if (p_begin >= p_end)
		return NULL;

	T* p_tmp = const_cast<T*>(p_begin);
	for (p_tmp; p_tmp != p_end; p_tmp++)
	{
		if (*p_tmp == k)
			return p_tmp;
	}
	return NULL;
}

MY_POINT* findMyPoint(MY_POINT* first, MY_POINT* last, const CString& name)
{
	MY_POINT* point = find(first, last + 1, name);
	return point;
}

IMPLEMENT_DYNAMIC(CDialogFindByName, CDialogEx)

CDialogFindByName::CDialogFindByName(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_FIND_BY_NAME, pParent)
	, m_name(_T(""))
	, m_found_point(_T(""))
{
	pDocum = pDoc;
	pDat = pDocum->pDat;
}

CDialogFindByName::~CDialogFindByName()
{
}

void CDialogFindByName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME_TO_FIND, m_name);
	DDX_Text(pDX, IDC_FOUND_POINT, m_found_point);
}


BEGIN_MESSAGE_MAP(CDialogFindByName, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FIND, &CDialogFindByName::OnClickedButtonFind)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CDialogFindByName::OnClickedButtonClear)
END_MESSAGE_MAP()


// CDialogFindByName message handlers


BOOL CDialogFindByName::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDialogFindByName::OnClickedButtonFind()
{
	UpdateData(TRUE);

	if (m_name.IsEmpty())
	{
		m_found_point = _T("Enter a node name.");
		UpdateData(FALSE);
		return;
	}

	if (pDat->size())
	{
		auto& first_item = (*pDat)[0];
		auto& last_item = (*pDat)[pDat->size() - 1];

		MY_POINT* points = findMyPoint(&first_item, &last_item, m_name);


		if (points != NULL)
		{
			m_found_point.Format(_T("Found element:\r\nx: %g, y: %g\r\n color: %d\r\n name: %s\r\n numb: %d\r\n\r\n"), points->x, points->y, points->color, points->name, points->numb);
		}
		if (points == NULL)
		{
			m_found_point = _T("Element not found.");
		}
	}
	else
	{
		m_found_point = _T("Add some points.");
	}

	UpdateData(FALSE);
}


void CDialogFindByName::OnClickedButtonClear()
{
	UpdateData(TRUE);
	if (!m_name.IsEmpty() || !m_found_point.IsEmpty())
	{
		m_name = _T("");
		m_found_point = _T("");
	}
	UpdateData(FALSE);
}
