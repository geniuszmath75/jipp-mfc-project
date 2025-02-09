#pragma once
#include "afxdialogex.h"
#include "ProjectMFCDoc.h"

// CDialogGraphWind dialog
class CDialogGraphWind : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogGraphWind)

public:
	CDialogGraphWind(CProjectMFCDoc* pDoc, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDialogGraphWind();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GRAPHWIND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void ModifyRadius();
	void ModifyFont();
	void ModifyLineWeight();

	DECLARE_MESSAGE_MAP()
public:
	CProjectMFCDoc* pDocum;
	LOGFONT m_lf;
	COLORREF m_fontColor;
	CExcept1App* pExcept;

	int m_lineWeight;
	int m_radius;
	CFont m_font;
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedButtonFont();
	
	int GetLineWeight() { return m_lineWeight; }
	void SetLineWeight(int lineWeight) { m_lineWeight = lineWeight; }
	int GetRadius() { return m_radius; }
	void SetRadius(int radius) { m_radius = radius; }
	LOGFONT GetFont() { return m_lf; }
	void SetFont(LOGFONT lf) { m_lf = lf; }
	COLORREF GetFontColor() { return m_fontColor; }
	void SetFontColor(COLORREF fColor) { m_fontColor = fColor; }
};
