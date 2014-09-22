#if !defined(AFX_MYTOOLDIALOG_H__48209AE1_F565_4F79_83F3_A87F13EEC953__INCLUDED_)
#define AFX_MYTOOLDIALOG_H__48209AE1_F565_4F79_83F3_A87F13EEC953__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTooldialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMytooldialog dialog

class CMytooldialog : public CDialogBar
{
// Construction
public:
	CMytooldialog();   // standard constructor
	int m_devindex;
	int m_devnum;
	char* m_sMask;
	char* m_sIPAddress;

// Dialog Data
	//{{AFX_DATA(CMytooldialog)
	enum { IDD = CG_IDD_MYDIALOGBAR };
	CComboBox	m_cinterface;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMytooldialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMytooldialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg LONG OnInitDialog( UINT, LONG );
	//afx_msg void OnSettingChange()
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLDIALOG_H__48209AE1_F565_4F79_83F3_A87F13EEC953__INCLUDED_)
