// mysnifferDoc.h : interface of the CMysnifferDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYSNIFFERDOC_H__B7B7FB97_5549_4880_88BB_276ECCA1E874__INCLUDED_)
#define AFX_MYSNIFFERDOC_H__B7B7FB97_5549_4880_88BB_276ECCA1E874__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMysnifferDoc : public CDocument
{
protected: // create from serialization only
	CMysnifferDoc();
	DECLARE_DYNCREATE(CMysnifferDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnifferDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMysnifferDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CMysnifferDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CMysnifferDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNIFFERDOC_H__B7B7FB97_5549_4880_88BB_276ECCA1E874__INCLUDED_)
