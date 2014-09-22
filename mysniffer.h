// mysniffer.h : main header file for the MYSNIFFER application
//

#if !defined(AFX_MYSNIFFER_H__4E624744_DB02_4495_9D61_8C1D52FE16FC__INCLUDED_)
#define AFX_MYSNIFFER_H__4E624744_DB02_4495_9D61_8C1D52FE16FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMysnifferApp:
// See mysniffer.cpp for the implementation of this class
//

class CMysnifferApp : public CWinApp
{
public:
	CMysnifferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMysnifferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation
	//{{AFX_MSG(CMysnifferApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSNIFFER_H__4E624744_DB02_4495_9D61_8C1D52FE16FC__INCLUDED_)
