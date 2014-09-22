
#if !defined(AFX_MYLISTVIEW_H__E80AFCF6_1AAA_46FD_A4D4_60C1F9D637B5__INCLUDED_)
#define AFX_MYLISTVIEW_H__E80AFCF6_1AAA_46FD_A4D4_60C1F9D637B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyOWnView.h : header file
//
#include "afxcview.h"
#include "pcap.h"
#include "hexedit.h"
#include "afxmt.h"
/////////////////////////////////////////////////////////////////////////////
// CMyListView view


struct my_tempstruct
{
	pcap_t *pcap_handle;                  // winpcap句柄 
	struct pcap_pkthdr * protocol_header; // 数据包头部信息
	const u_char* pkt_data;					//数据
	CString m_file_path;				 //存放路径
	int m_thread_num;				//线程数目
	BOOL m_ipm;						//是否采用混杂模式
	int m_devindex_num;				//网络设备序号
	int m_pl;						//数据包头长度限制
	int m_stoptime;					//停止时间
	int m_packetlimit;				//数据包限制数
	pcap_dumper_t *dumpfile;		//open_dump指针
	int m_count;					//数据包计数
	CString m_sourcemac;			//源mac地址
	CString m_destinanionmac;		//目的mac地址
	int  m_data_show;				//显示方式设置
	BOOL m_data_address;			//是否显示地址
	BOOL m_data_ascii;				//是否显示ascii
	my_tempstruct()
	{
		pcap_handle=NULL;
		protocol_header=NULL;
		pkt_data=NULL;
		m_data_address=TRUE;
		m_data_show=TRUE;
		m_data_ascii=TRUE;
	}
};

struct ether_header
{
	u_int8_t ether_dhost[6];
	u_int8_t ether_shost[6];
	u_int16_t ether_type;
};

struct arp_header
{
	u_int16_t arp_hardware_type;
	u_int16_t arp_protocol_type;
	u_int8_t arp_hardware_length;
	u_int8_t arp_protocol_length;
	u_int16_t arp_operation_code;
	u_int8_t arp_source_ethernet_address[6];
	u_int8_t arp_source_ip_address[4];
	u_int8_t arp_destination_ethernet_address[6];
	u_int8_t arp_destination_ip_address[4];
};

struct ip_header
{
	#if defined(WORDS_BIGENDIAN)
		u_int8_t ip_version:4,ip_header_length:4;
	#else
		u_int8_t ip_header_length:4,ip_version:4;
	#endif
	u_int8_t ip_tos;
	u_int16_t ip_length;
	u_int16_t ip_id;
	u_int16_t ip_off;
	u_int8_t ip_ttl;
	u_int8_t ip_protocol;
	u_int16_t ip_checksum;
	struct in_addr ip_souce_address;
	struct in_addr ip_destination_address;
};

struct udp_header
{
	u_int16_t udp_source_port;
	u_int16_t udp_destinanion_port;
	u_int16_t udp_length;
	u_int16_t udp_checksum;
};

struct tcp_header
{
	u_int16_t tcp_source_port;
	u_int16_t tcp_destinanion_port;
	u_int32_t tcp_sequence_num;
	u_int32_t tcp_acknowledgement;
	#ifdef WORDS_BIGENDIAN
		u_int8_t tcp_offset:4,tcp_offset:4;
	#else
		u_int8_t tcp_reserved:4,tcp_offset:4;
	#endif
	u_int8_t tcp_flags;
	u_int16_t tcp_windows;
	u_int16_t tcp_checksum;
	u_int16_t tcp_urent_pointer;
};

struct icmp_header
{
	u_int8_t icmp_type;
	u_int8_t icmp_code;
	u_int16_t icmp_checksum;
	u_int16_t icmp_id;
	u_int16_t icmp_sequence;
};

struct mydata
{
	int len;
    unsigned char* pkt_data;
};

class CMyListView : public CListView
{
protected:

	CMyListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyListView)
    
// Attributes
public:
    struct in_addr ip_saddress;
	struct in_addr ip_daddress;
	struct mydata *m_mydata;
	CString Packetanalyse(const u_char* temp_data);//包分析函数
	CString AnalyseUDP(const unsigned char * temp_data_udp);
	CString AnalyseIP (const unsigned char * temp_data_ip);
	CString AnalyseICMP(const unsigned char *temp_data_ip);
	CString AnalyseTCP(const unsigned char *temp_data_ip);
	CString AnalyseARP(const unsigned char *temp_data_ip);
// Operations
	CString m_info;

public:
	void ShowByteData(int m_numbyte);	
	void Cappacket();
	void Capoffline(CString m_open_filepath);
    void OnInitialUpdate();
	BOOL PreCreateWindow(CREATESTRUCT& cs);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyListView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyListView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()
};

class CMyDateView : public CView
{
protected:
	CMyDateView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyDateView)

// Attributes
public:
    CHexEdit m_myedit;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyDateView)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyDateView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyDateView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYLISTVIEW_H__E80AFCF6_1AAA_46FD_A4D4_60C1F9D637B5__INCLUDED_)
