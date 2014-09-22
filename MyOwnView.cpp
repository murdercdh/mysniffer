// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "mysniffer.h"
#include "MyOwnView.h"
#include "MainFrm.h"
#include "DlgStat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT Cappacketlivethread(LPVOID pParam);
CEvent m_eventEnd;
CEvent m_stoptimeup;
extern my_tempstruct m_mystruct;

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_NOTIFY_REFLECT(NM_CLICK,OnClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

BOOL CMyListView::PreCreateWindow(CREATESTRUCT& cs)
{
// TODO: Add your specialized code here and/or call the base class
	cs.style |= LVS_REPORT;
	return CListView::PreCreateWindow(cs);
}

void CMyListView::OnInitialUpdate()
{
	CListCtrl& theCtrl = GetListCtrl();
    DWORD dwStyle;
    dwStyle = theCtrl.GetExtendedStyle();//GetStyle();
    dwStyle |=LVS_EX_FULLROWSELECT;
    theCtrl.SetExtendedStyle(dwStyle);
    // Insert a column. This override is the most convenient.
    theCtrl.InsertColumn(0, _T("序号"), LVCFMT_LEFT);   //初始化列名
    theCtrl.InsertColumn(1, _T("捕获时间"), LVCFMT_LEFT,160);
    theCtrl.InsertColumn(2, _T("包长度"), LVCFMT_LEFT);
    theCtrl.InsertColumn(3, _T("源IP"), LVCFMT_LEFT,110);
    theCtrl.InsertColumn(4, _T("目的IP"), LVCFMT_LEFT,110);
    theCtrl.InsertColumn(5, _T("源物理地址"), LVCFMT_LEFT,120);
    theCtrl.InsertColumn(6, _T("目的物理地址"),LVCFMT_LEFT,120);
    theCtrl.InsertColumn(7, _T("使用协议"), LVCFMT_LEFT,90);
    theCtrl.InsertColumn(8, _T("相关信息"), LVCFMT_LEFT,150);
    theCtrl.SetColumnWidth(0, LVSCW_AUTOSIZE_USEHEADER);
    theCtrl.SetColumnWidth(2, LVSCW_AUTOSIZE_USEHEADER);
	
	m_mystruct.m_data_address=TRUE;
	m_mystruct.m_data_ascii=TRUE;
	m_mystruct.m_data_show=TRUE;
	m_mystruct.m_count=0;
	m_mystruct.m_ipm=TRUE;


}
/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

void CMyListView::Cappacket()
{
	
	int m_count=1;               //申明自己用的变量
	CString m_count1;
	CString m_packetlen;
	CString m_protocol;
    //以下是网络变量
	pcap_if_t *alldevs;//指向设备的链表
	pcap_if_t *d;//临时变量，指向设备的链表
	char error_content[PCAP_ERRBUF_SIZE];
    /* 存储错误信息 */
    pcap_t *pcap_handle;
    /* winpcap句柄 */
//    const unsigned char *packet_content;
    /* 数据包内容 */
//    unsigned char *mac_string;
    /* 以太网地址 */
//    unsigned short int ethernet_type;
    /* 以太网类型 */
    bpf_u_int32 net_mask;
    /* 掩码地址 */
    bpf_u_int32 net_ip;
    /* 网络地址 */
//    char *net_interface;
    /* 网络接口 */
//    struct pcap_pkthdr * protocol_header;
    /* 数据包头部信息 */
//    struct ether_header *ethernet_protocol;
    /* 以太网协议变量 */
    struct bpf_program bpf_filter;
    /* BPF过滤规则 */
    char* bpf_filter_string= "";
    /* 过滤规则字符串 */
    
//	bpf_filter_string=(LPSTR)(LPCTSTR)m_filter;
//    struct ip_header* ip_protocol;//ip头
//    struct tcp_header* tcp_protocol;//tcp头
//    struct udp_header* udp_protocol;//UDP头
//    struct icmp_header* icmp_protocol;//icmp头
//	struct arp_header* arp_protocol;//arp头
//	struct ether_header* ether_protocol;//以太网头
//    u_int data_len;
//    u_int tcp_len;
//	const u_char* pkt_data;//数据
//    const u_char* pkt_data_temp;//数据备份
	pcap_dumper_t *dumpfile;//open_dump指针
	if(pcap_findalldevs(&alldevs,error_content)==-1)
	{
		AfxMessageBox("Error in pcap_findalldevs");
		AfxMessageBox(error_content);
	} 
	else
	{
		d=alldevs;
		while(m_count<m_mystruct.m_devindex_num)//获得网络接口
		{
			d=d->next;
			m_count++;
		} 
	} 
      
    pcap_lookupnet(d->name, &net_ip, &net_mask, error_content);// 获得网络地址和网络掩码 
	if(d->addresses != NULL)
		net_mask=((struct sockaddr_in *)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		net_mask=0xffffff;

    pcap_handle = pcap_open_live(d->name,65536,m_mystruct.m_ipm,1000, error_content);//打开网路接口 
	pcap_freealldevs(alldevs);
    if(pcap_compile(pcap_handle,&bpf_filter,bpf_filter_string,1,net_mask)<0)// 编译过滤规则
	{ 
		AfxMessageBox("过滤规则出错！");
	} 
	if(pcap_setfilter(pcap_handle, &bpf_filter)<0)// 设置过滤规则 
	{ 
		AfxMessageBox("过滤规则出错！将使用默认方式捕获数据包");
	} 
	if (pcap_datalink(pcap_handle) != DLT_EN10MB)
        AfxMessageBox("不在局域网内");
	dumpfile=pcap_dump_open(pcap_handle,m_mystruct.m_file_path);
	if(dumpfile==NULL)
	{ 
		AfxMessageBox("不能打开文件！将使用默认文件default.DAT进行保存");
		CFile m_file;
		if (m_file.Open("default.DAT",CFile::modeRead,NULL))
		{ 
			m_file.Close();
			m_file.Remove("default.DAT");
		} 
	    m_mystruct.m_file_path="default.DAT";
		dumpfile=pcap_dump_open(pcap_handle,m_mystruct.m_file_path);
	}  
	
		m_mystruct.pcap_handle=pcap_handle;
//		m_mystruct.protocol_header=protocol_header;
//		m_mystruct.pkt_data=pkt_data;
		m_mystruct.dumpfile=dumpfile;
		CDlgStat m_dlgstat;
		AfxBeginThread(Cappacketlivethread,GetSafeHwnd());
		m_dlgstat.DoModal();
		WaitForSingleObject(m_eventEnd.m_hObject,INFINITE);
		Capoffline(m_mystruct.m_file_path);
		UpdateData(true);
		pcap_close(pcap_handle);
}

CString CMyListView::Packetanalyse(const u_char* temp_data)//包分析函数
{
	CString m_protocol_temp;
	CString temp;
	//CString m_sourcemac;
	//CString m_destinanionmac;
	u_char* mac_string;
	struct ether_header* ether_protocol;//以太网头
	ether_protocol=(ether_header*)temp_data;
	u_short ether_type;
	ether_type=ntohs(ether_protocol->ether_type);
    mac_string=ether_protocol->ether_shost;
    m_mystruct.m_sourcemac.Format("%02x:%02x:%02x:%02x:%02x:%02x",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
	mac_string=ether_protocol->ether_dhost;
    m_mystruct.m_destinanionmac.Format("%02x:%02x:%02x:%02x:%02x:%02x",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
	switch(ether_type)
	{
		case 0x0800:m_protocol_temp=AnalyseIP(temp_data);
					break;
		case 0x0806:m_protocol_temp=AnalyseARP(temp_data);
					break;
		case 0x0835:m_protocol_temp="RARP";
					break;
		default:m_protocol_temp="unknown";
				m_info="unknown";
	}      
    return m_protocol_temp;
} 

CString CMyListView::AnalyseIP(const unsigned char *temp_data_ip)
{
	CString m_protocol_temp;
	struct ip_header* ip_protocol;//ip头
	ip_protocol=(ip_header*)(temp_data_ip+14);//去掉以太网头
     switch(ip_protocol->ip_protocol)
	 { 
      case 6: m_protocol_temp=AnalyseTCP(temp_data_ip);
      break;
      case 17:m_protocol_temp=AnalyseUDP(temp_data_ip);
      break;
      case 1: m_protocol_temp=AnalyseICMP(temp_data_ip);
      break;
	  default:m_protocol_temp="IP::unknown";
      m_info="unknown";
  }
     memcpy((void*)&ip_saddress,(void*)&ip_protocol->ip_souce_address,sizeof(struct in_addr));
     memcpy((void*)&ip_daddress,(void*)&ip_protocol->ip_destination_address,sizeof(struct in_addr));
   return m_protocol_temp;
}


CString CMyListView::AnalyseARP(const unsigned char *temp_data_arp)
{
	CString m_protocol_temp="ARP";
	struct arp_header *arp_protocol;
	arp_protocol=(arp_header*)(temp_data_arp+14);
	u_char* mac_string;

	memcpy((void*)&ip_saddress,(void*)&arp_protocol->arp_source_ip_address,sizeof(struct in_addr));
	memcpy((void*)&ip_daddress,(void*)&arp_protocol->arp_destination_ip_address,sizeof(struct in_addr));
	
	if(ntohs(arp_protocol->arp_operation_code)==1)
	{
		m_info="arp请求";		
		mac_string=arp_protocol->arp_source_ethernet_address;
		m_mystruct.m_sourcemac.Format("%02x:%02x:%02x:%02x:%02x:%02x",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
	}
	else if(ntohs(arp_protocol->arp_operation_code)==2)
	{
		m_info="arp回复";
		mac_string=arp_protocol->arp_source_ethernet_address;
		m_mystruct.m_destinanionmac.Format("%02x:%02x:%02x:%02x:%02x:%02x",*mac_string,*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));
	}	
	return m_protocol_temp;
}

CString CMyListView::AnalyseUDP(const unsigned char *temp_data_udp)
{

	CString m_protocol_temp="UDP";
	CString m_info_temp;
	struct udp_header* udp_protocol;//UDP头
	udp_protocol=(udp_header*)(temp_data_udp+14+20);//去掉以太网头和ip头
	u_short udp_destinanion_port;
	u_short udp_sport;
	udp_destinanion_port=ntohs(udp_protocol->udp_destinanion_port);
	udp_sport=ntohs(udp_protocol->udp_source_port);
	m_info_temp.Format("%d--->%d",udp_sport,udp_destinanion_port);
	switch(static_cast<int>(udp_destinanion_port))
	{ 
		case 138:m_info="UDP::NetBIOS数据报服务";
				break;
		case 137:m_info="UDP::NetBIOS名字服务";
                break;
		case 139:m_info="UDP::NetBIOS会话服务";
				break;
		case 53:m_info="UDP::DNS服务";
				break;
		default:m_info=m_info_temp;
	} 
    return m_protocol_temp;
}


CString CMyListView::AnalyseTCP(const unsigned char *temp_data_tcp)
{
	CString m_protocol_temp="tcp";
//    u_char* m_info_temp;
    struct tcp_header* tcp_protocol;//UDP头
    tcp_protocol=(tcp_header *)(temp_data_tcp+14+20);//去掉以太网头和ip头

	u_short tcp_destinanion_port;
	u_short tcp_source_port;

	tcp_destinanion_port=ntohs(tcp_protocol->tcp_destinanion_port);
	tcp_source_port=ntohs(tcp_protocol->tcp_source_port);

//	unsigned   char   FlagMask   =   1;   
//	for(int i=0;   i<6;   i++   )   
//	{   
//		if((tcp_protocol->tcp_flags)   &   FlagMask)  printf("%c",m_info_temp[i]);   
//		else   printf("-",m_info_temp[i]);   
//		FlagMask=FlagMask<<1;   
//	}

	switch(static_cast<int>(tcp_destinanion_port))
	{ 
		case 23:m_info="TCP::telnet";
				break;
		case 21:m_info="TCP::ftp";
			    break;
		case 25:m_info="TCP::smtp";
                break;
		case 43:m_info="TCP::whois";
				break;
		case 15:m_info="TCP::netstat";
				break;
		case 139:m_info="TCP::netbios";
				break;
		case 103:m_info="TCP::x.400邮件服务";
				break;
		case 53:m_info="TCP::遇名服务器";
				break;
		default:m_info="unknown";
	} 
	   
	//m_info.Format("%s",m_info_temp);
    return m_protocol_temp;
}

CString CMyListView::AnalyseICMP(const unsigned char *temp_data_icmp)
{
	
	CString m_protocol_temp="ICMP";
	CString m_info_temp;
	struct icmp_header* icmp_protocol;
	icmp_protocol=(icmp_header*)(temp_data_icmp+14+20);//去掉以太网头和ip头
	
	switch(static_cast<int>(icmp_protocol->icmp_type))
	{
		case 0:m_info="ICMP::回应应答";
			break;
		case 3:m_info="ICMP::目的不可达";
			break;
		case 4:m_info="ICMP::源消亡";
			break;
		case 5:m_info="ICMP::重定向";
			break;
		case 9:m_info="ICMP::路由器公告";
			break;
		case 11:m_info="ICMP::超时";
			break;
		case 12:m_info="ICMP::参数问题";
			break;
		case 10:m_info="ICMP::路由器请求";
			break;
		default:m_info="unknown";
	} 
    return m_protocol_temp;
}

void CMyListView::OnClick(NMHDR* pNMHDR, LRESULT* pResult)
{
	 // TODO: Add your control notification handler code here
	int nItem = -1;
    LPNMITEMACTIVATE lpNMItemActivate = (LPNMITEMACTIVATE)pNMHDR;
    if(lpNMItemActivate != NULL)
	{
		nItem = lpNMItemActivate->iItem;
	}
    ShowByteData(nItem);
	*pResult = 0;

}

void CMyListView::ShowByteData(int m_numbyte)
{
	COleSafeArray g_arr;
	if(m_numbyte>=0)
	{
		/*
		SAFEARRAYBOUND rgsabound;
		rgsabound.cElements = m_mydata[m_numbyte].len;
		rgsabound.lLbound = 0;
		g_arr.Create(VT_UI1, 1, &rgsabound);
		
		void* buf;
		g_arr.AccessData(&buf);
		
		char *p = (char*)buf;
		memcpy(p, m_mydata[m_numbyte].pkt_data, m_mydata[m_numbyte].len);
		
		g_arr.UnaccessData();
		*/
		CMainFrame * pFrame=(CMainFrame *)AfxGetMainWnd();
		CMyDateView *p_dateView=(CMyDateView *)pFrame->m_wndSplitter.GetPane(1,0);	
		g_arr.CreateOneDim (VT_UI1,m_mydata[m_numbyte].len,m_mydata[m_numbyte].pkt_data);
		p_dateView->m_myedit.SetData(g_arr, 0);
	}  
}

void CMyListView::Capoffline(CString m_open_filepath)//文件读取操作函数
{
	char errbuf[PCAP_ERRBUF_SIZE];
    char source[1024];
//    struct pcap_pkthdr *header;//网络包头
    const u_char *pkt_data;//数据报数据
	CString m_packetlen;//数据包长度
	CString m_protocol;//数据包协议
	CString m_count1;//数据包计数
	u_int i=0;
	pcap_t *fp;
	int m_count=0;
	struct pcap_pkthdr* protocol_header;//协议头
    int res;
	if (pcap_createsrcstr(source,         // variable that will keep the source string
                            PCAP_SRC_FILE,  // we want to open a file
                            NULL,           // remote host
                            NULL,           // port on the remote host
                            m_open_filepath,        // name of the file we want to open
                            errbuf          // error buffer
                            ) != 0)
    {
        AfxMessageBox(errbuf);
    }
	
	if ((fp=pcap_open(source,         // name of the device
                        65536,          // portion of the packet to capture
                                        // 65536 guarantees that the whole packet will be captured on all the link layers
                         PCAP_OPENFLAG_PROMISCUOUS,     // promiscuous mode
                         1000,              // read timeout
                         NULL,              // authentication on the remote machine
                         errbuf         // error buffer
                         ) ) == NULL)
    {
        AfxMessageBox(errbuf);
    }

    m_mydata=(mydata*)malloc((m_mystruct.m_count-1)*sizeof(mydata));//数据包个数

	while((res = pcap_next_ex(fp,&protocol_header,&pkt_data))>=0)
    {
		if (protocol_header->len==0) continue;
		m_mydata[m_count].len=protocol_header->len;
        m_mydata[m_count].pkt_data=(unsigned char*)malloc(protocol_header->len);
		memcpy(m_mydata[m_count].pkt_data,pkt_data,protocol_header->len);
		m_packetlen.Format("%d",protocol_header->len);
        m_protocol=Packetanalyse(pkt_data);//协议分析
		m_count1.Format("%d",m_count+1);//对要添加的信息做格式化处理
		CListCtrl &m_list=GetListCtrl();//以下是对ListView添加信息
		m_list.InsertItem(m_count,m_count1);
		m_list.SetItemText(m_count,1,ctime((const time_t*)&protocol_header->ts.tv_sec));
		m_list.SetItemText(m_count,2,m_packetlen);
		m_list.SetItemText(m_count,3,inet_ntoa(ip_saddress));
		m_list.SetItemText(m_count,4,inet_ntoa(ip_daddress));
		m_list.SetItemText(m_count,5,m_mystruct.m_sourcemac);
		m_list.SetItemText(m_count,6,m_mystruct.m_destinanionmac);
		m_list.SetItemText(m_count,7,m_protocol);
		m_list.SetItemText(m_count,8,m_info);
		m_count++;
    } 
}

UINT Cappacketlivethread(LPVOID pParam)//抓包线程函数
{
	//CMainFrame *p_frame=(CMainFrame*)AfxGetMainWnd();
	//int m_exsn=p_frame->m_myprosheet.m_page2.m_thread_num;
	//int m_stoptime=p_frame->m_myprosheet.m_page2.m_stoptime;
	//int m_thread_index=0;
	for(int i=0;i<m_mystruct.m_packetlimit;i++)//线程数目
	{	
		if (::WaitForSingleObject(m_stoptimeup,0)==WAIT_OBJECT_0)
		{
			//m_thread_index=i;
			m_mystruct.m_count=i;
			break;
		} 
        pcap_next_ex(m_mystruct.pcap_handle,&m_mystruct.protocol_header,&m_mystruct.pkt_data);//句柄，协议头，数据包
		if ((m_mystruct.protocol_header->len)>m_mystruct.m_pl)//判断是否在规定长度以内
		{	
			i--;
			continue;
		}  
		pcap_dump((u_char*)m_mystruct.dumpfile,m_mystruct.protocol_header,m_mystruct.pkt_data);
		m_mystruct.m_count=i;
	} 
	m_eventEnd.SetEvent();
	return 0;
}
/////////////////////////////////////////////////////////////////////////////
// CMyDateView

IMPLEMENT_DYNCREATE(CMyDateView, CView)

CMyDateView::CMyDateView()
{
}

CMyDateView::~CMyDateView()
{
}


BEGIN_MESSAGE_MAP(CMyDateView, CView)
	//{{AFX_MSG_MAP(CMyDateView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDateView drawing

void CMyDateView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
	
}

int CMyDateView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_myedit.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, 0);
	m_myedit.SetBackColor(0x00FFffff);

	m_myedit.SetShowAscii(m_mystruct.m_data_ascii);
	m_mystruct.m_data_ascii = m_myedit.GetShowAscii();
	
	m_myedit.SetShowAddress(TRUE);

//	m_myedit.SetDigitsInData(m_mystruct.m_data_show);
//	m_myedit.SetDigitsInAddress(m_mystruct.m_data_address);

	return 0;
}

void CMyDateView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	m_myedit.MoveWindow(0, 0, cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDateView diagnostics

#ifdef _DEBUG
void CMyDateView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDateView message handlers

