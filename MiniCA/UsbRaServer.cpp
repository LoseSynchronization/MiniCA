// UsbRaServer.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbRaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbRaServer property page

IMPLEMENT_DYNCREATE(CUsbRaServer, CPropertyPage)

CUsbRaServer::CUsbRaServer() : CPropertyPage(CUsbRaServer::IDD)
{
	//{{AFX_DATA_INIT(CUsbRaServer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pListeSock=new CSslServerSocket(1);
	server=false;//启动，停止

}

CUsbRaServer::~CUsbRaServer()
{
	delete m_pListeSock;
}

void CUsbRaServer::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbRaServer)
	DDX_Control(pDX, IDC_IPADDRESS_IP, m_server_IP);
	DDX_Control(pDX, IDC_LIST_SERVER2, m_ListC);
	DDX_Control(pDX, IDC_LIST_SERVER, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbRaServer, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbRaServer)
	ON_BN_CLICKED(IDC_LISTEN, OnListen)
	ON_BN_CLICKED(IDC_B_GETC, OnBGetc)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbRaServer message handlers
void CUsbRaServer::DisplayError(_com_error &e)
{
	CString msgText;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	
	msgText.Format("连接数据库错误\n错误代码 = %08lx\n", e.Error());
	msgText += " Msg: ";
	msgText += e.ErrorMessage();
	msgText += "\n 来源: ";
	msgText += bstrSource;
	msgText += "\n 内容: ";
	msgText += bstrDescription;
	m_List.AddMsg(msgText,M_ERROR);

}
int CUsbRaServer::GetLocalHostName(CString &sHostName)	//获得本地计算机名称
{
	char szHostName[256];
	int nRetCode;
	nRetCode=gethostname(szHostName,sizeof(szHostName));
	if(nRetCode!=0)
	{
		//产生错误
		sHostName=_T("没有取得");
		SockMsgBox(GetLastError());
		return -1;
	}
	sHostName=szHostName;
	return 0;
}

int CUsbRaServer::GetIpAddress(const CString &sHostName, CString &sIpAddress)//获得本地IP
{
	struct hostent FAR * lpHostEnt=gethostbyname(sHostName);
	if(lpHostEnt==NULL)
	{
		//产生错误
		sIpAddress=_T("");
		SockMsgBox(GetLastError());
		return -1;
	}
	//获取IP
	LPSTR lpAddr=lpHostEnt->h_addr_list[0];
	if(lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr,lpAddr,4);
		//转换为标准格式
		sIpAddress=inet_ntoa(inAddr);
		if(sIpAddress.IsEmpty())
			sIpAddress=_T("没有取得");
	}
	return 0;
}
BOOL CUsbRaServer::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	if (!AfxOleInit())///初始化COM库,MFC 程序不用收回COM库
	{
		m_List.AddMsg("初始化ADO失败",M_ERROR);
		return FALSE;
	}
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	////////////连接数据库///////////////////////////////////////////////////////////
	CString m_strPath;
	GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	m_strPath.ReleaseBuffer ();
	int nPos;
	nPos=m_strPath.ReverseFind ('\\');
	m_strPath=m_strPath.Left (nPos);
	CString lpszFile = m_strPath + "\\ra.mdb";
	CString connect;
	connect.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Persist Security Info=False;Jet OLEDB:Database Password=hpxs",lpszFile);
	HRESULT hr;
	try
	{	// Create new Connection Object
		hr = m_pConnection.CreateInstance(__uuidof( Connection ));
		if (SUCCEEDED(hr))
		{	
			try
			{	// Open Connection to database
				hr = m_pConnection->Open((_bstr_t)connect,"","",adModeUnknown);///连接数据库
				if (SUCCEEDED(hr))
				{	// Successful connection
				//	m_IsConnected = TRUE;	// Set connection state
				//	SetToolBarShow();
				}
			}
			catch ( _com_error &e )//不要用指针，用引用,Runtime error
			{
				DisplayError(e);
				return FALSE;
			}
		}
		else throw ( "Failed to create instance of Connection Object");
	}
	catch ( _com_error &e )
	{
		DisplayError(e);
		return FALSE;
	}
	catch( char * str )
	{
		m_List.AddMsg(str,M_ERROR);
		return FALSE;
	}
	catch(...)
	{
		m_List.AddMsg( "Unhandled Exception wile connecting to database",M_ERROR);
		return FALSE;
	}
	GetDlgItem(IDC_LISTEN)->EnableWindow(true);
	///////////////////////取得IP///////////////////////////////
	CString strLocalName;
	GetLocalHostName(strLocalName);
	CString strLocalIP;
	GetIpAddress(strLocalName,strLocalIP);
	m_server_IP.SetWindowText(strLocalIP);
	m_server_IP.EnableWindow(false);

	SetDlgItemText(IDC_EDIT_PORT,"4430");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbRaServer::OnListen() 
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	CString port;
	GetDlgItemText(IDC_EDIT_PORT,port);

	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_SERVER_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*私钥*/
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
		
		if(m_pListeSock->CreateLisenSock(atoi(port),FD_ACCEPT)==FALSE)
			return;
		if(m_pListeSock->InitCtx(SSLv23_server_method(),lpCert,
			lenCert,lpKey,lenKey,lpszFile.GetBuffer(0),NULL,1,&m_List,&m_ObSock,m_pConnection,out)==NULL)
		{
			m_List.AddMsg(out,M_ERROR);
			server=!server;
			m_pListeSock->ShutDown();
			m_pListeSock->Close();
			return;
		}
		
		GetDlgItem(IDC_LISTEN)->SetWindowText("停止服务");//绿灯
		GetDlgItem(IDC_STATIC_OFF)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_ON)->ShowWindow(SW_SHOW);
		
		m_List.AddMsg("等待客户接入.......",M_WARING);
	}
	
	else
	{
		GetDlgItem(IDC_LISTEN)->SetWindowText("启动服务");//红灯
		GetDlgItem(IDC_STATIC_ON)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_OFF)->ShowWindow(SW_SHOW);
		m_pListeSock->SSlShouDown();//停止侦听
		CloseAllClient();
		GetDlgItem(IDC_EDIT_PORT)->EnableWindow(true);
		m_List.ResetContent();
	}	
}

void CUsbRaServer::OnBGetc() 
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

void CUsbRaServer::CloseAllClient()
{
	if(m_ObSock.IsEmpty()) return;
	CSslServerSocket * p=NULL;
	for(POSITION pos = m_ObSock.GetHeadPosition(); pos != NULL; )
	{
		p=(CSslServerSocket *)m_ObSock.GetNext(pos);
		p->SSlShouDown();
		delete p;//删除套接字
		p=NULL;
	}
	m_ObSock.RemoveAll(); 
}

void CUsbRaServer::OnDestroy() 
{
	CPropertyPage::OnDestroy();
	// TODO: Add your message handler code here
	if(m_pConnection->State)
    {
		m_pConnection->Close();
		m_pConnection= NULL; 
	}
	m_pListeSock->SSlShouDown();
	CloseAllClient();
}
