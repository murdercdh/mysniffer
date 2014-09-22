// mysnifferView.cpp : implementation of the CMysnifferView class
//

#include "stdafx.h"
#include "mysniffer.h"

#include "mysnifferDoc.h"
#include "mysnifferView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView

IMPLEMENT_DYNCREATE(CMysnifferView, CView)

BEGIN_MESSAGE_MAP(CMysnifferView, CView)
	//{{AFX_MSG_MAP(CMysnifferView)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
//	ON_MESSAGE(WM_USERAPPLY,OnUserApply)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView construction/destruction
//CView *my_pView=NULL;
CMysnifferView::CMysnifferView()
{


}

CMysnifferView::~CMysnifferView()
{
}

BOOL CMysnifferView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView drawing

void CMysnifferView::OnDraw(CDC* pDC)
{
	CMysnifferDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView printing

BOOL CMysnifferView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMysnifferView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMysnifferView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView diagnostics

#ifdef _DEBUG
void CMysnifferView::AssertValid() const
{
	CView::AssertValid();
}

void CMysnifferView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMysnifferDoc* CMysnifferView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMysnifferDoc)));
	return (CMysnifferDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMysnifferView message handlers
//LRESULT CMysnifferView::OnUserApply(WPARAM wParam,LPARAM lParam)
//{

//	return 0;

//}




