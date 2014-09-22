#if !defined(AFX_DLGSTAT_H__1B82FDB0_4D2A_45F5_9134_C9D72D20FFB5__INCLUDED_)
#define AFX_DLGSTAT_H__1B82FDB0_4D2A_45F5_9134_C9D72D20FFB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStat dialog

class CDlgStat : public CDialog
{
// Construction
public:
	CTime begintime;
	CTime nowtime;
	CTimeSpan ts;
	CDlgStat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStat)
	enum { IDD = IDD_DIALOG1 };
	CString	m_time;
	CString	m_pnumcount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStat)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTAT_H__1B82FDB0_4D2A_45F5_9134_C9D72D20FFB5__INCLUDED_)
