// DlgStat.cpp : implementation file
//

#include "stdafx.h"
#include "mysniffer.h"
#include "DlgStat.h"
#include "MyOwnView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgStat dialog
extern CEvent m_stoptimeup;
extern my_tempstruct m_mystruct;

CDlgStat::CDlgStat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStat)
	m_time = _T("");
	m_pnumcount = _T("");
	//}}AFX_DATA_INIT
}


void CDlgStat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStat)
	DDX_Text(pDX, IDC_EDIT1, m_time);
	DDX_Text(pDX, IDC_EDIT2, m_pnumcount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStat, CDialog)
	//{{AFX_MSG_MAP(CDlgStat)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgStat message handlers

BOOL CDlgStat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(1,50,NULL);
	SetTimer(2,m_mystruct.m_stoptime*1000,NULL);
	//m_mystruct.m_count=0;
	begintime=CTime::GetCurrentTime();	
	// TODO: Add extra initialization here

	CProgressCtrl *prog=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	prog->SetRange(0,m_mystruct.m_packetlimit);

	m_stoptimeup.ResetEvent();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStat::OnTimer(UINT nIDEvent) 
{
	CProgressCtrl *prog=(CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	// TODO: Add your message handler code here and/or call default
	switch(nIDEvent)
	{
		case 1:if((m_mystruct.m_count+1)>=m_mystruct.m_packetlimit)
					m_pnumcount="包捕捉完毕！";
				else
				{ 
					m_pnumcount.Format("%d",m_mystruct.m_count+1);  
					nowtime= CTime::GetCurrentTime();
					ts=nowtime-begintime;
					prog->SetPos(m_mystruct.m_count);
					m_time=ts.Format( "分钟: %M  秒: %S" );
				} 
				UpdateData(false);
				break;
		case 2:
				m_stoptimeup.SetEvent();
				KillTimer(1);
				m_time="时间到！";
				UpdateData(false);
				break;
	} 	
	CDialog::OnTimer(nIDEvent);
}

void CDlgStat::OnOK() 
{
	// TODO: Add extra validation here
	m_stoptimeup.SetEvent();
	KillTimer(1);
	KillTimer(2);	
	CDialog::OnOK();
}


