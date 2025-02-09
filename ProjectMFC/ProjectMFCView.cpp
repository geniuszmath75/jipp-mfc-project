
// ProjectMFCView.cpp : implementation of the CProjectMFCView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ProjectMFC.h"
#endif

#include "ProjectMFCDoc.h"
#include "ProjectMFCView.h"

#include "CDialogInputData.h"
#include "CDialogGraphWind.h"
#include "CDialogGetLastItem.h"
#include "CDialogFindByName.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProjectMFCView

IMPLEMENT_DYNCREATE(CProjectMFCView, CView)

BEGIN_MESSAGE_MAP(CProjectMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CProjectMFCView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_OPERATE_INPUTDATA, &CProjectMFCView::OnOperateInputdata)
	ON_COMMAND(ID_OPERATE_GRAPHWIND, &CProjectMFCView::OnOperateGraphwind)
	ON_COMMAND(ID_OPERATE_GETLASTITEM, &CProjectMFCView::OnOperateGetlastitem)
	ON_COMMAND(ID_OPERATE_FINDBYNAME, &CProjectMFCView::OnOperateFindByName)
END_MESSAGE_MAP()

// CProjectMFCView construction/destruction

CProjectMFCView::CProjectMFCView() noexcept
{
	// TODO: add construction code here
	m_ScaleX = m_ScaleY = 1.0;
	PointRad = 8;
	LineWeight = 2;
	fontColor = RGB(0, 0, 0);

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 12;
	lf.lfCharSet = EASTEUROPE_CHARSET;
	strcpy_s(lf.lfFaceName, "Arial");
}

CProjectMFCView::~CProjectMFCView()
{
}

void CProjectMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CWnd* ptrWnd = this->GetActiveWindow();
	CProjectMFCDoc* pDoc = GetDocument();
	if (pDoc && pDoc->pDat)
	{
		MY_DATA* pdat = pDoc->pDat;
		pDoc->pExcept->SetWnd(ptrWnd, pdat);
		pDoc->pExcept->ClearOutWnd();
	}
}

BOOL CProjectMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProjectMFCView drawing

void CProjectMFCView::OnDraw(CDC* pDC)
{
	CProjectMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc || !pDoc->pDat || !pDoc->pDat->size())
		return;

	/*LOGFONT lf = pDoc->GetLogFont();
	COLORREF fontColor = pDoc->GetFontColor();*/

	// TODO: add draw code for native data here
	pDC->SetMapMode(MM_TEXT);
	pDC->SetGraphicsMode(GM_ADVANCED);

	CString str;
	TEXTMETRIC tm;

	CPen newpen;
	CPen* oldpen;
	CBrush newbrush;
	CBrush* oldbrush;

	CPoint scr;
	SIZE size1;
	SIZE marg = { 80, 80 };

	VERIFY(font.CreateFontIndirect(&lf));
	CFont* def_font = pDC->SelectObject(&font);
	COLORREF def_color = pDC->SetTextColor(fontColor);

	pDC->GetOutputTextMetrics(&tm);

	CRect rect;
	this->GetClientRect(&rect);

	double max_x, min_x, max_y, min_y;
	pDoc->pDat->GetMaxMinCoords(max_x, min_x, max_y, min_y);

	size1.cx = (long)(m_ScaleX * (rect.right - rect.left));
	size1.cy = (long)(m_ScaleY * (rect.bottom - rect.top));

	newbrush.CreateSolidBrush(RGB(255, 255, 255));
	oldbrush = pDC->SelectObject(&newbrush);
	pDC->Rectangle(0, 0, (rect.right - rect.left), (rect.bottom - rect.top));
	pDC->SelectObject(oldbrush);
	newbrush.DeleteObject();

	DCOORD Coord(0, 0), mmin(min_x, min_y), mmax(max_x, max_y);

	const int npoints = pDoc->pDat->size();

	newpen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	oldpen = pDC->SelectObject(&newpen);

	for (int ipoint = 0; ipoint < npoints; ++ipoint)
	{
		Coord.x = (*pDoc->pDat)[ipoint].x;
		Coord.y = (*pDoc->pDat)[ipoint].y;
		scr = GetScreenCoord(Coord, mmin, mmax, size1, marg, 1, 1);
		MY_POINT tmp = (*pDoc->pDat)[ipoint];
		newbrush.CreateSolidBrush(tmp.color);
		oldbrush = pDC->SelectObject(&newbrush);
		pDC->Ellipse(scr.x + PointRad, scr.y + PointRad, scr.x - PointRad, scr.y - PointRad);
		pDC->SelectObject(oldbrush);
		newbrush.DeleteObject();

		pDC->SelectObject(oldpen);
		newpen.DeleteObject();
		newpen.CreatePen(PS_SOLID, LineWeight, RGB(255, 0, 0));
		oldpen = pDC->SelectObject(&newpen);

		if (ipoint == 0)
			pDC->MoveTo(scr);
		else
			pDC->LineTo(scr);

		pDC->SelectObject(oldpen);
		newpen.DeleteObject();

		str.Format("%s", tmp.name);
		pDC->TextOut(scr.x + PointRad + 2, scr.y, str);
	}

	pDC->SelectObject(oldpen);
	newpen.DeleteObject();

	pDC->SelectObject(def_font);
	pDC->SetTextColor(def_color);
	font.DeleteObject();
}


// CProjectMFCView printing


void CProjectMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CProjectMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProjectMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProjectMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

CPoint CProjectMFCView::GetScreenCoord(DCOORD Coord, DCOORD min, DCOORD max, SIZE size1, SIZE marg, int hsbpos, int vsbpos)
{
	CPoint scr;
	const double eps = 1e-40;
	if (fabs(min.y - max.y) < eps)
	{
		scr.y = size1.cy / 2;
	}
	else
		scr.y = (long)(marg.cy + (Coord.y - max.y) / (min.y - max.y) * (size1.cy - 2 * marg.cy));

	if (fabs(min.x - max.x) < eps)
	{
		scr.x = size1.cx / 2;
	}
	else
		scr.x = (long)(marg.cx + (Coord.x - min.x) / (max.x - min.x) * (size1.cx - 2 * marg.cx));

	scr.x -= hsbpos * size1.cx / 100;
	scr.y -= vsbpos * size1.cy / 100;

	return scr;
}

void CProjectMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CProjectMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CProjectMFCView diagnostics

#ifdef _DEBUG
void CProjectMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CProjectMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProjectMFCDoc* CProjectMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProjectMFCDoc)));
	return (CProjectMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CProjectMFCView message handlers


void CProjectMFCView::OnOperateInputdata()
{
	// TODO: Add your command handler code here
	CProjectMFCDoc* pDoc = GetDocument();
	CDialogInputData dlg(pDoc);
	dlg.DoModal();

}

void CProjectMFCView::OnOperateGraphwind()
{
	// TODO: Add your command handler code here
	CProjectMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CDialogGraphWind dlg(pDoc, this);
	dlg.m_lineWeight = LineWeight;
	dlg.m_lf = lf;
	dlg.m_radius = PointRad;
	dlg.m_fontColor = fontColor;
	if (dlg.DoModal() == IDOK)
	{
		PointRad = dlg.GetRadius();
		LineWeight = dlg.GetLineWeight();
		lf = dlg.GetFont();
		fontColor = dlg.GetFontColor();
		Invalidate();
	}
}


void CProjectMFCView::OnOperateGetlastitem()
{
	// TODO: Add your command handler code here
	CProjectMFCDoc* pDoc = GetDocument();
	CDialogGetLastItem dlg(pDoc);
	dlg.DoModal();
}



void CProjectMFCView::OnOperateFindByName()
{
	// TODO: Add your command handler code here
	CProjectMFCDoc* pDoc = GetDocument();
	CDialogFindByName dlg(pDoc);
	dlg.DoModal();
}
