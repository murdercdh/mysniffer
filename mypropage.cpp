// MyProPage.cpp : implementation file
//

#include "stdafx.h"
#include "mysniffer.h"
#include "MyProPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyProPage1 property page

IMPLEMENT_DYNCREATE(CMyProPage1, CPropertyPage)

CMyProPage1::CMyProPage1() : CPropertyPage(CMyProPage1::IDD)
{
	//{{AFX_DATA_INIT(CMyProPage1)
	m_address = FALSE;
	m_ascii = FALSE;
	m_dataformat = 1;
	//}}AFX_DATA_INIT
}

CMyProPage1::~CMyProPage1()
{
}

void CMyProPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyProPage1)
	DDX_Check(pDX, IDC_CHECK_ADDRESS, m_address);
	DDX_Check(pDX, IDC_CHECK_ASCII, m_ascii);
	DDX_Radio(pDX, IDC_DATAFORMAT1, m_dataformat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyProPage1, CPropertyPage)
	//{{AFX_MSG_MAP(CMyProPage1)
	ON_BN_CLICKED(IDC_DATAFORMAT1, OnDataformat1)
	ON_BN_CLICKED(IDC_CHECK_ASCII, OnCheckAscii)
	ON_BN_CLICKED(IDC_CHECK_ADDRESS, OnCheckAddress)
	ON_BN_CLICKED(IDC_DATAFORMAT2, OnDataformat1)
	ON_BN_CLICKED(IDC_DATAFORMAT3, OnDataformat1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyProPage1::OnApply()
{
	UpdateData(TRUE);
	m_mystruct.m_data_address=m_address;
	m_mystruct.m_data_ascii=m_ascii;
	m_mystruct.m_data_show=m_dataformat;
	g_pFrame->SendMessage(WM_USERAPPLY);
	return TRUE;
}

BOOL CMyProPage1::OnCommand(WPARAM wParam, LPARAM lParam)
{
	SetModified(TRUE);
	return CPropertyPage::OnCommand(wParam,lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMyProPage1 message handlers
/////////////////////////////////////////////////////////////////////////////
// CMyProPage2 property page

IMPLEMENT_DYNCREATE(CMyProPage2, CPropertyPage)

CMyProPage2::CMyProPage2() : CPropertyPage(CMyProPage2::IDD)
{
	//{{AFX_DATA_INIT(CMyProPage2)
	m_interface_mode = TRUE;
	m_thread_num = 1;
	//}}AFX_DATA_INIT
}

CMyProPage2::~CMyProPage2()
{
}

void CMyProPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyProPage2)
	DDX_Control(pDX, IDC_SPIN_PACKETLIMIT, m_spacketlimit);
	DDX_Control(pDX, IDC_SPIN_STOPTIME, m_sstoptime);
	DDX_Control(pDX, IDC_SPIN_PL, m_spl);
	DDX_Check(pDX, IDC_CHECK_INTERFACE, m_interface_mode);
	DDX_Text(pDX, IDC_EDIT_THREADNUM, m_thread_num);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMyProPage2, CPropertyPage)
	//{{AFX_MSG_MAP(CMyProPage2)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CMyProPage2::OnCommand(WPARAM wParam, LPARAM lParam)
{
	SetModified(TRUE);
	return CPropertyPage::OnCommand(wParam,lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CMyProPage2 message handlers
/////////////////////////////////////////////////////////////////////////////
// CMyProSheet

IMPLEMENT_DYNAMIC(CMyProSheet, CPropertySheet)
CFrameWnd * g_pFrame=NULL;
CMyProSheet::CMyProSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CMyProSheet::CMyProSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
	AddPage(&m_page2);
}

CMyProSheet::~CMyProSheet()
{
}


BEGIN_MESSAGE_MAP(CMyProSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CMyProSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyProSheet message handlers

BOOL CMyProPage2::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

	m_spacketlimit.SetBuddy(GetDlgItem(IDC_EDIT_PACKETLIMIT));
	m_spacketlimit.SetRange(1,10000);
	m_spacketlimit.SetPos(50);

	m_sstoptime.SetBuddy(GetDlgItem(IDC_EDIT_STOPTIME));
	m_sstoptime.SetRange(1,10000);
	m_sstoptime.SetPos(20);

	m_spl.SetBuddy(GetDlgItem(IDC_EDIT_PL));
	m_spl.SetRange(1,10000);
	m_spl.SetPos(900);

	m_thread_num=1;
	m_interface_mode=true;
	//以上是对话框上复选框的初始化
	UpdateData(TRUE);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CMyProPage1::OnDataformat1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
		switch (m_dataformat)
		{
		case 0:	// byte
			//m_ctlHexEdit.SetDigitsInData(2);
			//m_address = m_ctlHexEdit.GetShowAscii();
			m_mystruct.m_data_show=2;
			UpdateData ( FALSE );
			break;
		case 2:	// dword
			//m_ctlHexEdit.SetDigitsInData(8);
			m_mystruct.m_data_show=8;
			m_address = false;
			UpdateData ( FALSE );
			break;
		case 1:	// word
			//m_ctlHexEdit.SetDigitsInData(4);
			m_mystruct.m_data_show=4;
			m_address = false;
			UpdateData ( FALSE );
			break;
		}
		m_mystruct.m_data_address=m_address;
}

void CMyProPage1::OnCheckAscii() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_mystruct.m_data_ascii=m_ascii;
	UpdateData(FALSE);
}

void CMyProPage1::OnCheckAddress() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_mystruct.m_data_address=m_address;
	UpdateData(FALSE);
	
}
