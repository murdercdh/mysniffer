// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "mysniffer.h"
#include "MyOwnView.h"
#include "pcap.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

my_tempstruct m_mystruct;
extern CEvent m_eventEnd;
//extern CEvent m_eventStart;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_COMMAND_EX(CG_ID_VIEW_MYDIALOGBAR, OnBarCheck)
	ON_UPDATE_COMMAND_UI(CG_ID_VIEW_MYDIALOGBAR, OnUpdateControlBarMenu)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(IDC_COMBO1,OnSettingChange)
	ON_COMMAND(IDC_BUTTON_SCAN,OnLButtonDownScan)
	ON_COMMAND(IDC_BUTTON_STOP,OnLButtonDownStop)
	ON_COMMAND(ID_SAVE_TO_FILE, OnSaveToFile)
	ON_COMMAND(ID_MYSET_SHEET, OnMysetSheet)
	ON_MESSAGE(WM_USERAPPLY,OnUserApply)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame():m_myprosheet("程序属性设置")
{
	m_myprosheet.m_page1.m_address=TRUE;
	m_myprosheet.m_page1.m_ascii=TRUE;
	g_pFrame=this;
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	// TODO: Add a menu item that will toggle the visibility of the
	// dialog bar named "My Dialog Bar":
	//   1. In ResourceView, open the menu resource that is used by
	//      the CMainFrame class
	//   2. Select the View submenu
	//   3. Double-click on the blank item at the bottom of the submenu
	//   4. Assign the new item an ID: CG_ID_VIEW_MYDIALOGBAR
	//   5. Assign the item a Caption: My Dialog Bar

	// TODO: Change the value of CG_ID_VIEW_MYDIALOGBAR to an appropriate value:
	//   1. Open the file resource.h
	// CG: The following block was inserted by the 'Dialog Bar' component

		// Initialize dialog bar m_wndMyDialogBar
	/*	if (!m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_MYDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}
*/
	    //m_cinterface.SubclassDlgItem(IDC_COMBO1,&m_wndMyDialogBar);
		
		if (!m_wndMyDialogBar.Create(this, CG_IDD_MYDIALOGBAR,
			CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_HIDE_INPLACE,
			CG_ID_VIEW_MYDIALOGBAR))
		{
			TRACE0("Failed to create dialog bar m_wndMyDialogBar\n");
			return -1;		// fail to create
		}

		m_wndMyDialogBar.EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM);
		EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_wndMyDialogBar);
		
		CComboBox *pCombo = (CComboBox*)m_wndMyDialogBar.GetDlgItem(IDC_COMBO1);
		pcap_if_t *alldevs;
		pcap_if_t *d;
		char errbuf[PCAP_ERRBUF_SIZE];
		if(pcap_findalldevs(&alldevs, errbuf)==-1)
		{
			AfxMessageBox("Error in pcap_findalldevs");
			AfxMessageBox(errbuf);
		} 
		for(d=alldevs; d; d=d->next)
		{ 
			if (d->description)
			{
				pCombo->AddString(d->description);
			} 
			else
				 AfxMessageBox("No description available");
				 m_devnum++;
		}
		pcap_freealldevs(alldevs);	
	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	m_wndSplitter.CreateStatic(this,2,1);
	m_wndSplitter.CreateView(0,0,RUNTIME_CLASS(CMyListView),CSize(100,200),pContext);
	m_wndSplitter.CreateView(1,0,RUNTIME_CLASS(CMyDateView),CSize(200,300),pContext);	
	return true;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	m_strTitle = "我的winpcap抓包程序"; 
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnSettingChange() 
{
	CComboBox *pCombo = (CComboBox*)m_wndMyDialogBar.GetDlgItem(IDC_COMBO1);
	m_devindex=pCombo->GetCurSel()+1;
	pcap_if_t *alldevs;
	pcap_if_t *d;
	bpf_u_int32 net_mask;
	bpf_u_int32 net_ip;
	struct in_addr net_ip_addr;
	struct in_addr net_mask_addr;
	int m_count=1;
	char errbuf[PCAP_ERRBUF_SIZE];
	if(pcap_findalldevs(&alldevs,errbuf)==-1)
	{
		AfxMessageBox("Error in pcap_findalldevs");
		AfxMessageBox(errbuf);
	} 
	else
	{ 
		d=alldevs;
		while(m_count<m_devindex)
		{ 
			d=d->next;
			m_count++;
		} 
	} 
	m_mystruct.m_devindex_num=m_devindex;
    pcap_lookupnet(d->name, &net_ip, &net_mask, errbuf); //  获得网络接口
	net_ip_addr.S_un.S_addr=net_ip;
    net_mask_addr.S_un.S_addr=net_mask;
	m_sMask=inet_ntoa(net_mask_addr);
	m_sIPAddress=inet_ntoa(net_ip_addr);
	pcap_freealldevs(alldevs);
	//m_wndMyDialogBar.GetDlgItem(IDC_STATIC_IP)->SetWindowText("你当前选中网卡的ip是：");
	m_wndMyDialogBar.GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_sIPAddress);
	m_wndMyDialogBar.GetDlgItem(IDC_STATIC_IP)->SetWindowText(m_sMask);
	UpdateData(false);
	
	// TODO: Add your message handler code here
	
}

void CMainFrame::OnLButtonDownScan()
{
	CMyListView *pview=(CMyListView*)m_wndSplitter.GetPane(0,0);
	pview->Cappacket();	
}

void CMainFrame::OnLButtonDownStop()
{
	m_eventEnd.SetEvent();
}


void CMainFrame::OnSaveToFile() 
{
	// TODO: Add your command handler code here
	CFileDialog m_file_dlg(TRUE, "DAT", ".DAT", OFN_HIDEREADONLY, _T(".DAT Files|*.DAT"), this);
	m_file_dlg.m_ofn.lpstrTitle="保存数据包文件";
	if(m_file_dlg.DoModal() == IDOK )
	{
        CString pathName=m_file_dlg.GetPathName();
		m_mystruct.m_file_path=pathName;
		UpdateData(TRUE);
	} 	
}

void CMainFrame::OnMysetSheet() 
{
	m_myprosheet.DoModal();		
}

LRESULT CMainFrame::OnUserApply(WPARAM wParam,LPARAM lParam)
{
	m_mystruct.m_count=0;
	m_mystruct.m_pl=m_myprosheet.m_page2.m_spl.GetPos();
	m_mystruct.m_packetlimit=m_myprosheet.m_page2.m_spacketlimit.GetPos();
	m_mystruct.m_stoptime=m_myprosheet.m_page2.m_sstoptime.GetPos();
	m_mystruct.m_thread_num=m_myprosheet.m_page2.m_thread_num;
	m_mystruct.m_ipm=m_myprosheet.m_page2.m_interface_mode;
	return true;	
}


