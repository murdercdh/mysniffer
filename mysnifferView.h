// mysnifferView.h : interface of the CMysnifferView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSNIFFERVIEW_H__5CD58F3E_C580_4CD0_81FA_3565881B87D6__INCLUDED_)
#define AFX_MYSNIFFERVIEW_H__5CD58F3E_C580_4CD0_81FA_3565881B87D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMysnifferView : public CView
{
protected: // create from serialization only
	CMysnifferView();
	DECLARE_DYNCREATE(CMysnifferView)

// Attributes

public:
	CMysnifferDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnifferView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysnifferView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMysnifferView)
	//}}AFX_MSG
	//afx_msg LRESULT OnUserApply(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in mysnifferView.cpp
inline CMysnifferDoc* CMysnifferView::GetDocument()
   { return (CMysnifferDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNIFFERVIEW_H__5CD58F3E_C580_4CD0_81FA_3565881B87D6__INCLUDED_)
