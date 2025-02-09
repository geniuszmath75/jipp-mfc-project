
// ProjectMFCView.h : interface of the CProjectMFCView class
//

#pragma once


class CProjectMFCView : public CView
{
protected: // create from serialization only
	CProjectMFCView() noexcept;
	DECLARE_DYNCREATE(CProjectMFCView)

// Attributes
public:
	CProjectMFCDoc* GetDocument() const;

// Operations
public:
	double m_ScaleX;
	double m_ScaleY;
	int PointRad;
	int LineWeight;
	LOGFONT lf;
	CFont font;
	COLORREF fontColor;

	struct DCOORD
	{
		double x;
		double y;
		DCOORD(double xx, double yy) : x(xx), y(yy) {}
	};

	CPoint CProjectMFCView::GetScreenCoord(DCOORD Coord, DCOORD min, DCOORD max, SIZE size1, SIZE marg, int hsbpos, int vsbpos);
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CProjectMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOperateInputdata();
	virtual void OnInitialUpdate();
	afx_msg void OnOperateGraphwind();
	afx_msg void OnOperateGetlastitem();
	afx_msg void OnOperateFindByName();
};

#ifndef _DEBUG  // debug version in ProjectMFCView.cpp
inline CProjectMFCDoc* CProjectMFCView::GetDocument() const
   { return reinterpret_cast<CProjectMFCDoc*>(m_pDocument); }
#endif

