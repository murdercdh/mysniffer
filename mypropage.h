#if !defined(AFX_MYPROPAGE_H__EEE1870E_C52C_4196_B0E6_E474394A13B3__INCLUDED_)
#define AFX_MYPROPAGE_H__EEE1870E_C52C_4196_B0E6_E474394A13B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProPage.h : header file
//
#include <afxcview.h>
#include "MyOwnView.h"

#define WM_USERAPPLY WM_USER+10

extern CFrameWnd * g_pFrame;
extern my_tempstruct m_mystruct;
/////////////////////////////////////////////////////////////////////////////
// CMyProPage dialog

class CMyProPage1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMyProPage1)

// Construction
public:
	CMyProPage1();
	~CMyProPage1();

// Dialog Data
	//{{AFX_DATA(CMyProPage1)
	enum { IDD = IDD_PROPPAGE_EDIT };
	BOOL	m_address;
	BOOL	m_ascii;
	int		m_dataformat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyProPage1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnApply();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyProPage1)
	afx_msg void OnDataformat1();
	afx_msg void OnCheckAscii();
	afx_msg void OnCheckAddress();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
// CMyProPage2 dialog

class CMyProPage2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CMyProPage2)

// Construction
public:
	CMyProPage2();
	~CMyProPage2();

// Dialog Data
	//{{AFX_DATA(CMyProPage2)
	enum { IDD = IDD_PROPPAGE_INTERFACE };
	CSpinButtonCtrl	m_spacketlimit;
	CSpinButtonCtrl	m_sstoptime;
	CSpinButtonCtrl	m_spl;
	BOOL	m_interface_mode;
	int		m_thread_num;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CMyProPage2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CMyProPage2)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// CMyProSheet

class CMyProSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CMyProSheet)

// Construction
public:
	CMyProSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CMyProSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
	CMyProPage1 m_page1;
	CMyProPage2 m_page2;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyProSheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMyProSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyProSheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROPAGE_H__EEE1870E_C52C_4196_B0E6_E474394A13B3__INCLUDED_)
