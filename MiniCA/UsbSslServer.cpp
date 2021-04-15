// UsbSslServer.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbSslServer.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbSslServer property page

IMPLEMENT_DYNCREATE(CUsbSslServer, CPropertyPage)

CUsbSslServer::CUsbSslServer() : CPropertyPage(CUsbSslServer::IDD)
{
	//{{AFX_DATA_INIT(CUsbSslServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	server=false;//������ֹͣ
	m_type=0;//��Ҫ��

}

CUsbSslServer::~CUsbSslServer()
{
}

void CUsbSslServer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbSslServer)
	DDX_Control(pDX, IDC_LIST_SERVER2, m_ListC);
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_server_IP);
	DDX_Control(pDX, IDC_LIST_SERVER, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbSslServer, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbSslServer)
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_B_GETC, OnBGetc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbSslServer message handlers

BOOL CUsbSslServer::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	///////////////////////ȡ��IP///////////////////////////////
	CString strLocalName;
	GetLocalHostName(strLocalName);
	CString strLocalIP;
	GetIpAddress(strLocalName,strLocalIP);
	m_server_IP.SetWindowText(strLocalIP);
	m_server_IP.EnableWindow(false);

	SetDlgItemText(IDC_EDIT_PORT,"443");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbSslServer::OnListen() //��ʼ������
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	CString port;
	GetDlgItemText(IDC_EDIT_PORT,port);

//	stuCLIENTINFO  stu;
	/*�õ���Կ*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_SERVER_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*˽Կ*/
	hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_SERVER_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);

	server=!server;
	if(server)
	{	
		CString m_strPath;
		GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
		m_strPath.ReleaseBuffer ();
		int nPos;
		nPos=m_strPath.ReverseFind ('\\');
		m_strPath=m_strPath.Left (nPos);
		CString lpszFile = m_strPath + "\\RootCert.pem";
		
		if(m_ListeSock.CreateLisenSock(atoi(port),FD_ACCEPT)==FALSE)
			return;
		if(m_ListeSock.InitCtx(SSLv23_server_method(),lpCert,
			lenCert,lpKey,lenKey,lpszFile.GetBuffer(0),NULL,m_type,&m_List,&m_ObSock,NULL,out)==NULL)
		{
			m_List.AddMsg(out,M_ERROR);
			server=!server;
			m_ListeSock.ShutDown();
			m_ListeSock.Close();
			return;
		}
		
		GetDlgItem(IDC_LISTEN)->SetWindowText("ֹͣ����");//�̵�
		GetDlgItem(IDC_STATIC_OFF)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ON)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CHECK)->EnableWindow(false);
		
		m_List.AddMsg("�ȴ��ͻ�����.......",M_WARING);
	}
	
	else
	{
		GetDlgItem(IDC_LISTEN)->SetWindowText("��������");//���
		GetDlgItem(IDC_STATIC_ON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_OFF)->ShowWindow(SW_SHOW);
		m_ListeSock.SSlShouDown();//ֹͣ����
		CloseAllClient();
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
		m_List.ResetContent();
		GetDlgItem(IDC_CHECK)->EnableWindow(true);
	}	

}

int CUsbSslServer::GetLocalHostName(CString &sHostName)	//��ñ��ؼ��������
{
	char szHostName[256];
	int nRetCode;
	nRetCode=gethostname(szHostName,sizeof(szHostName));
	if(nRetCode!=0)
	{
		//��������
		sHostName=_T("û��ȡ��");
		SockMsgBox(GetLastError());
		return -1;
	}
	sHostName=szHostName;
	return 0;
}

int CUsbSslServer::GetIpAddress(const CString &sHostName, CString &sIpAddress)//��ñ���IP
{
	struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//��������
		sIpAddress=_T("");
		SockMsgBox(GetLastError());
		return -1;
	}
	//��ȡIP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		//ת��Ϊ��׼��ʽ
		sIpAddress=inet_ntoa(inAddr);
		if(sIpAddress.IsEmpty())
			sIpAddress=_T("û��ȡ��");
	}
	return 0;
}

void CUsbSslServer::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	m_ListeSock.SSlShouDown();
	CloseAllClient();
	// TODO: Add your message handler code here
	
}

void CUsbSslServer::OnCheck() 
{
	// TODO: Add your control notification handler code here
	int check=((CButton *)GetDlgItem(IDC_CHECK))->GetCheck();
	if(check) m_type=2;
	else m_type=0;
}

void CUsbSslServer::OnBGetc() 
{
	// TODO: Add your control notification handler code here
	m_ListC.ResetContent();
	if(m_ObSock.IsEmpty()) return;
	CString ip,sport;
	UINT port;
	CSslServerSocket * p=NULL;
	for(POSITION pos = m_ObSock.GetHeadPosition(); pos != NULL; )
	{
		p=(CSslServerSocket *)m_ObSock.GetNext(pos);
		p->GetPeerName(ip,port);
		sport.Format("%s:%d",ip,port);
		m_ListC.AddMsg(sport);
	}
}

void CUsbSslServer::CloseAllClient()//�ر����пͻ�����
{
	if(m_ObSock.IsEmpty()) return;
	CSslServerSocket * p=NULL;
	for(POSITION pos = m_ObSock.GetHeadPosition(); pos != NULL; )
	{
		p=(CSslServerSocket *)m_ObSock.GetNext(pos);
		p->SSlShouDown();
		delete p;//ɾ���׽���
		p=NULL;
	}
	m_ObSock.RemoveAll(); 
}
