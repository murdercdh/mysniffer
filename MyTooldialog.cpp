// MyTooldialog.cpp : implementation file
//

#include "stdafx.h"
#include "mysniffer.h"
#include "MyTooldialog.h"
#include "pcap.h"

//#pragma comment(lib, "C:/Hook/release/Hook.lib") 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMytooldialog dialog


CMytooldialog::CMytooldialog()
{
	//{{AFX_DATA_INIT(CMytooldialog)
	//}}AFX_DATA_INIT
}


void CMytooldialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMytooldialog)
	DDX_Control(pDX, IDC_COMBO1, m_cinterface);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMytooldialog, CDialogBar)
	//{{AFX_MSG_MAP(CMytooldialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMytooldialog message handlers
LONG CMytooldialog::OnInitDialog(UINT wParam, LONG lParam)
{
			BOOL bRet = HandleInitDialog(wParam, lParam);

            if (!UpdateData(FALSE))
            {
               TRACE0("Warning: UpdateData failed during dialog init.\n");
            }
	
	// TODO: Add extra initialization here
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
				m_cinterface.AddString(d->description);
			}	
			else
				AfxMessageBox("No description available");
			m_devnum++;
		} 
		pcap_freealldevs(alldevs);
	
	return bRet; 

}

/*void MyTooldialog::OnSelchangeCombo1() 
{
        m_devindex=m_cinterface.GetCurSel()+1;
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
       
		pcap_lookupnet(d->name, &net_ip, &net_mask, errbuf);
		net_ip_addr.S_un.S_addr=net_ip;
		net_mask_addr.S_un.S_addr=net_mask;
		m_sMask=inet_ntoa(net_mask_addr);
		m_sIPAddress=inet_ntoa(net_ip_addr);
		pcap_freealldevs(alldevs);
		MyTooldialog *pmywnd=(MyTooldialog*)GetDlgItem(CG_IDD_MYDIALOGBAR);
		pmywnd->GetDlgItem(IDC_STATIC_NAME)->SetWindowText(m_sMask);
		pmywnd->GetDlgItem(IDC_STATIC_IP)->SetWindowText(m_sIPAddress);
		UpdateData(false);
}

*/	
