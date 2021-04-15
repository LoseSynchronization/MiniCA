// LogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "LogDlg.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog



CLogDlg::CLogDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLogDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogDlg)
	m_password = _T("");
	//}}AFX_DATA_INIT
	m_ConnectTime=0;
}


void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogDlg)
	DDX_Control(pDX, IDOK, m_Ok);
	DDX_Control(pDX, IDCANCEL, m_Cancel);
	DDX_Control(pDX, IDC_LIST_LOGO, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_password);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialog)
	//{{AFX_MSG_MAP(CLogDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogDlg message handlers
BOOL CLogDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	//////////////////////设置对话框大小////////////////////
	GetWindowRect(m_dlgRect_big);  //最大对话框
	CRect rect_X,rect_Y; 							     
	GetDlgItem(IDC_CXY_Y)->GetWindowRect(rect_Y); //Y标尺
	SetDlgItemText(IDC_EDIT_IP,"localhost");
	SetDlgItemText(IDC_EDIT_PORT,"4430");


	m_dlgRect_small.left=m_dlgRect_big.left;//设置最小对话框
	m_dlgRect_small.top=m_dlgRect_big.top;
	m_dlgRect_small.right=m_dlgRect_big.right;
	m_dlgRect_small.bottom=rect_Y.bottom;
	MoveWindow(&m_dlgRect_small);

	////////////////////////////////////////////////////////////
	// TODO: Add extra initialization here
	m_Ok.SetIcon(IDI_ICON_LOG);
	m_Cancel.SetIcon(IDI_ICON_LOGC);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLogDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString host("localhost"),port("4430");
	GetDlgItemText(IDC_EDIT_IP,host);
	GetDlgItemText(IDC_EDIT_PORT,port);
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

	CString m_strPath;
	GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	m_strPath.ReleaseBuffer ();
	int nPos;
	nPos=m_strPath.ReverseFind ('\\');
	m_strPath=m_strPath.Left (nPos);
	CString lpszFile = m_strPath + "\\RootCert.pem";
	
	char out[100]={0};
	BOOL b=((CRaclientApp *)AfxGetApp())->m_SslSocket.SockConnect(SSLv23_client_method(),lpCert,lenCert,lpKey,
		lenKey,lpszFile.GetBuffer(0),NULL,host,atoi(port),out);
	if(b==FALSE)
	{
		m_List.AddMsg(out,M_ERROR);//显示-大
		SetWindowPos(&wndTop,0,0,m_dlgRect_big.Width(),m_dlgRect_big.Height(),SWP_NOMOVE);
		return;
	}
	SetTimer(1,500,NULL);//建立计时器，每.5秒尝试连接一次，直到连上或超出
	
}


void CLogDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_ConnectTime++;
	if(m_ConnectTime>9)
	{
		m_List.AddMsg("SSL连接超时",M_ERROR);
		((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlShouDown();
		KillTimer(1);
		m_ConnectTime=0;
		SetWindowPos(&wndTop,0,0,m_dlgRect_big.Width(),m_dlgRect_big.Height(),SWP_NOMOVE);
		return;
	}
	char out[100]={0};
	int i=((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlConnect(out);
	if(i==-1)//连接失败
	{
		m_List.AddMsg(out,M_ERROR);
		SetWindowPos(&wndTop,0,0,m_dlgRect_big.Width(),m_dlgRect_big.Height(),SWP_NOMOVE);
		((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlShouDown();
		KillTimer(1);
		m_ConnectTime=0;

	}
	else if(i==1)//成功
	{
		KillTimer(1);
		m_ConnectTime=0;
	    ((CMainFrame *)AfxGetMainWnd())->SetStatusIcon(IDS_STRING_STATE,IDI_ICON1);
		CDialog::OnOK();
	}	
	CDialog::OnTimer(nIDEvent);
}

