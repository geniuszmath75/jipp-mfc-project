// CDialogGraphWind.cpp : implementation file
//

#include "pch.h"
#include "ProjectMFC.h"
#include "afxdialogex.h"
#include "CDialogGraphWind.h"


// CDialogGraphWind dialog

IMPLEMENT_DYNAMIC(CDialogGraphWind, CDialogEx)

CDialogGraphWind::CDialogGraphWind(CProjectMFCDoc* pDoc, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_GRAPHWIND, pParent)
	, m_radius(8)
	, m_lineWeight(2)
	, m_fontColor(RGB(0, 0, 0))
{
	pExcept = GetExceptPtr();
	pDocum = pDoc;
	memset(&m_lf, 0, sizeof(LOGFONT));
	m_lf.lfHeight = 12;
	strcpy_s(m_lf.lfFaceName, "Arial");
}

CDialogGraphWind::~CDialogGraphWind()
{
	m_font.DeleteObject();
}

void CDialogGraphWind::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RADIUS, m_radius);
	DDX_Text(pDX, IDC_EDIT_LINEWEIGHT, m_lineWeight);
}


BEGIN_MESSAGE_MAP(CDialogGraphWind, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialogGraphWind::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_FONT, &CDialogGraphWind::OnClickedButtonFont)
END_MESSAGE_MAP()

BOOL CDialogGraphWind::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT(pDocum);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

// CDialogGraphWind message handlers

void CDialogGraphWind::ModifyRadius()
{
	SetRadius(m_radius);
	pExcept->PutMessage(1008);
}

void CDialogGraphWind::ModifyFont()
{
	SetFont(m_lf);
	SetFontColor(m_fontColor);

	CWnd* pControl = GetDlgItem(IDC_BUTTON_FONT);
	if (pControl)
	{
		CFont newFont;
		newFont.CreateFontIndirect(&m_lf);
		pControl->SetFont(&newFont);

		pControl->Invalidate();

		m_font.Attach(newFont.Detach());
	}
}

void CDialogGraphWind::ModifyLineWeight()
{
	SetLineWeight(m_lineWeight);
	pExcept->PutMessage(1010);
}

void CDialogGraphWind::OnBnClickedOk()
{
	CDialogEx::OnOK();
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);
	ModifyRadius();
	ModifyFont();
	ModifyLineWeight();
	UpdateData(FALSE);

	ASSERT_VALID(pDocum);
	pDocum->SetModifiedFlag();
	pDocum->UpdateAllViews(NULL);
}

void CDialogGraphWind::OnClickedButtonFont()
{
	// TODO: Add your control notification handler code here
	CFontDialog dlg(&m_lf);
	dlg.m_cf.rgbColors = m_fontColor;

	if (dlg.DoModal() == IDOK)
	{
		m_fontColor = dlg.GetColor();

		pExcept->PutMessage(1009);
	}
}
