// UsbKey.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "UsbKey.h"

#include "usbinfopage.h"
#include "usbprocpage.h"
#include "usbpwdpage.h"
#include "UsbSoPage.h"
#include "UsbKeySheet.h"
#include "UsbCertPage.h"
#include "UsbCaPage.h"
#include "UsbSslClient.h"
#include "UsbSslServer.h"
#include "UsbEvpPage.h"
#include "UsbRaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbKeyApp

BEGIN_MESSAGE_MAP(CUsbKeyApp, CWinApp)
	//{{AFX_MSG_MAP(CUsbKeyApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbKeyApp construction

CUsbKeyApp::CUsbKeyApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CUsbKeyApp object

CUsbKeyApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CUsbKeyApp initialization

BOOL CUsbKeyApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	if (!AfxSocketInit())
	{
		AfxMessageBox("IDP_SOCKETS_INIT_FAILED");
		return FALSE;
	}	
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if(USBKey_Connect(&m_handle)==FALSE)
	{
//		AfxMessageBox("检测不到USB钥匙");
//		return false;
	}
	m_VerifySo=false;
	m_VerifyUser=false;
//	m_PubKey=false;
//	m_PriKey=false;
//	m_ExternKey=false; 
	m_ChangeKey=false;;
	CUsbKeySheet dlg("MiniCA System");
	dlg.m_psh.dwFlags |= PSH_NOAPPLYNOW  |PSH_USEHICON;
	dlg.m_psh.dwFlags&= ~PSH_HASHELP;
	dlg.m_psh.nStartPage = 0;//本程序此处不能改动
	dlg.m_psh.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_KEY); 

	CUsbInfoPage pageInfo;
	pageInfo.m_psp.dwFlags |= PSH_USEHICON;
	pageInfo.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_DISK); 
	//MAKEINTRESOURCE

	CUsbPwdPage pagePwd;
	pagePwd.m_psp.dwFlags |= PSH_USEHICON;
	pagePwd.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_PWD); 

	CUsbProcPage pageProc;
	pageProc.m_psp.dwFlags |= PSH_USEHICON;
	pageProc.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_CERT); 

	CUsbSoPage pageOper;
	pageOper.m_psp.dwFlags |= PSH_USEHICON;
	pageOper.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_SO); 

	CUsbCertPage pageCert;
	pageCert.m_psp.dwFlags |= PSH_USEHICON;
	pageCert.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_EXTERN); 

	CUsbCaPage pageCa;
	pageCa.m_psp.dwFlags |= PSH_USEHICON;
	pageCa.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_CA); 

	CUsbSslClient pageClient;
	pageClient.m_psp.dwFlags |= PSH_USEHICON;
	pageClient.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_CLIENT); 

	CUsbSslServer pageServer;
	pageServer.m_psp.dwFlags |= PSH_USEHICON;
	pageServer.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_SERVER); 

	CUsbEvpPage pageEvp;
	pageEvp.m_psp.dwFlags |= PSH_USEHICON;
	pageEvp.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_EVP); 

	CUsbRaServer pageRa;
	pageRa.m_psp.dwFlags |= PSH_USEHICON;
	pageRa.m_psp.hIcon=AfxGetApp()->LoadIcon(IDI_ICON_RA); 

	dlg.AddPage(&pageInfo);
	dlg.AddPage(&pagePwd);
	dlg.AddPage(&pageProc);
	dlg.AddPage(&pageOper);
	dlg.AddPage(&pageCert);
	dlg.AddPage(&pageCa);
	dlg.AddPage(&pageClient);
	dlg.AddPage(&pageServer);
	dlg.AddPage(&pageEvp);
	dlg.AddPage(&pageRa);

	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

