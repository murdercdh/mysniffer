// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__93176B98_6D61_43C5_BA54_C1AA751D6E54__INCLUDED_)
#define AFX_MAINFRM_H__93176B98_6D61_43C5_BA54_C1AA751D6E54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mypropage.h"

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	char* m_sMask;
	char* m_sIPAddress;
  
public:
	CSplitterWnd m_wndSplitter;
	CMyProSheet m_myprosheet;
    int m_devnum;
	int m_devindex;
    //CString m_file_path;
	
	CDialogBar m_wndMyDialogBar;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSettingChange();
	afx_msg void OnLButtonDownScan();
	afx_msg void OnLButtonDownStop();
	afx_msg void OnSaveToFile();
	afx_msg void OnMysetSheet();
	//}}AFX_MSG
	afx_msg LRESULT OnUserApply(WPARAM wParam,LPARAM lParam);	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__93176B98_6D61_43C5_BA54_C1AA751D6E54__INCLUDED_)
