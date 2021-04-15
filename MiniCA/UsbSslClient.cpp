// UsbSslClient.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbSslClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbSslClient property page

IMPLEMENT_DYNCREATE(CUsbSslClient, CPropertyPage)

CUsbSslClient::CUsbSslClient() : CPropertyPage(CUsbSslClient::IDD)
{
	//{{AFX_DATA_INIT(CUsbSslClient)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_ConnectTime=0;
}

CUsbSslClient::~CUsbSslClient()
{
}

void CUsbSslClient::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbSslClient)
	DDX_Control(pDX, IDC_LIST_CLIENT, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbSslClient, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbSslClient)
	ON_BN_CLICKED(IDC_B_CONNECT, OnBConnect)
	ON_BN_CLICKED(IDC_B_DISCON, OnBDiscon)
	ON_BN_CLICKED(IDC_B_SEND, OnBSend)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbSslClient message handlers
BOOL CUsbSslClient::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_COM_IP,"localhost");//www.itrus.com.cn,login.sybase.com;lists.ust.hk;www.onlinenic.com
	SetDlgItemText(IDC_EDIT_PORT,"443");
	SetDlgItemText(IDC_EDIT_SEND,"GET / HTTP/1.0\n\n");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbSslClient::OnBConnect() 
{
	// TODO: Add your control notification handler code here
	CString host,port;
	GetDlgItemText(IDC_COM_IP,host);
	GetDlgItemText(IDC_EDIT_PORT,port);

	char out[100]={0};

	/*得到公钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_CLIENT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*私钥*/
	hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_CLIENT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);
	if(m_clientSock.m_Ssl!=NULL)//断开上次连接
	{
		CString str;
		str.Format("%d已经断开与服务器的连接",m_clientSock.m_hSocket);
		m_clientSock.SSlShouDown();
		m_List.AddMsg(str,M_WARING);
	}
	GetDlgItem(IDC_B_SEND)->EnableWindow(0);

	CString m_strPath;
	GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	m_strPath.ReleaseBuffer ();
	int nPos;
	nPos=m_strPath.ReverseFind ('\\');
	m_strPath=m_strPath.Left (nPos);
	CString lpszFile = m_strPath + "\\RootCert.pem";

	BOOL b=m_clientSock.SockConnect(SSLv23_client_method(),lpCert,lenCert,lpKey,
		lenKey,lpszFile.GetBuffer(0),NULL,&m_List,host,atoi(port),out);
	if(b==FALSE)
	{
		m_List.AddMsg(out,M_ERROR);
		return;
	}
	SetTimer(1,500,NULL);//建立计时器，每.5秒尝试连接一次，直到连上或超出

}

void CUsbSslClient::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_ConnectTime++;
	if(m_ConnectTime>9)
	{
		m_List.AddMsg("SSL连接超时",M_ERROR);
		m_clientSock.SSlShouDown();
		KillTimer(1);
		m_ConnectTime=0;
		return;
	}
	char out[100]={0};
	stuSERVERINFO stu;
	int i=m_clientSock.SSlConnect(&stu,out);
	if(i==-1)
	{
		m_List.AddMsg(out,M_ERROR);
		m_clientSock.SSlShouDown();
		KillTimer(1);
		m_ConnectTime=0;

	}
	else if(i==1)
	{
		m_List.AddMsg(stu.Cert);
		m_List.AddMsg(stu.CiphersVer);
		m_List.AddMsg(stu.CiphersName);
		m_List.AddMsg(stu.peerCert.iss);
		m_List.AddMsg(stu.peerCert.sub);
		m_List.AddMsg(stu.peerChain.iss);
		m_List.AddMsg(stu.peerChain.sub);
		m_List.AddMsg(stu.selfChain);
		m_List.AddMsg(stu.Session);
		CString str;
		str.Format("握手结束，%d接入服务器成功",m_clientSock.m_hSocket);
		m_List.AddMsg(str,M_WARING);
		KillTimer(1);
		m_ConnectTime=0;
		GetDlgItem(IDC_B_SEND)->EnableWindow(1);

	}

	CPropertyPage::OnTimer(nIDEvent);
}

void CUsbSslClient::OnBDiscon() 
{
	// TODO: Add your control notification handler code here
	if(m_clientSock.m_hSocket==-1)
		return;
	KillTimer(1);
	CString str;
	str.Format("%d已经断开与服务器的连接",m_clientSock.m_hSocket);
	m_clientSock.SSlShouDown();
	m_List.AddMsg(str,M_WARING);

}

void CUsbSslClient::OnBSend() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_EDIT_SEND,str);
	m_clientSock.SSlSend(str.GetBuffer(100),str.GetLength());

}


void CUsbSslClient::OnDestroy() 
{
	CPropertyPage::OnDestroy();

	// TODO: Add your message handler code here
	m_clientSock.SSlShouDown();
	
}
