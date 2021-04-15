// Raclient.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Raclient.h"

#include "MainFrm.h"
#include "raChildFrame.h"

#include "logdlg.h"
#include "time.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CRaclientApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CRaclientApp

const UINT ID_RA_MSG =::RegisterWindowMessage(ra_MSG);

BEGIN_MESSAGE_MAP(CRaclientApp, CWinApp)
	//{{AFX_MSG_MAP(CRaclientApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_SYS_DISCONNECT, OnSysDisconnect)
	ON_UPDATE_COMMAND_UI(ID_SYS_DISCONNECT, OnUpdateSysDisconnect)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaclientApp construction

CRaclientApp::CRaclientApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRaclientApp object
//HANDLE gEven;
CRaclientApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CRaclientApp initialization

BOOL CRaclientApp::InitInstance()
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

	m_hOneInstance = ::CreateMutex( NULL,FALSE,UNIQE_NAME);
	if ( GetLastError() == ERROR_ALREADY_EXISTS )
	{

		DWORD dwRecipients = BSM_APPLICATIONS;
		::BroadcastSystemMessage( BSF_NOHANG,&dwRecipients,
			ID_RA_MSG, // registered window message
			0,0 ); // user defined parameters
		return FALSE;
	}


#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMDIFrameWnd* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need. 

	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_RACLIETYPE));
	m_hMenu=::LoadMenu(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_MAINFRAME));



	// The main window has been initialized, so show and update it.
//	pFrame->ShowWindow(m_nCmdShow);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->SetWindowText("RaClient-Î´µÇÂ¼");

	pFrame->UpdateWindow();
	m_candisconnect=false;
	m_bmp1.LoadBitmap(IDB_BITMAP1);
	m_bmp2.LoadBitmap(IDB_BITMAP2);
	m_bmp3.LoadBitmap(IDB_BITMAP3);
	m_bmp4.LoadBitmap(IDB_BITMAP4);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CRaclientApp message handlers

int CRaclientApp::ExitInstance() 
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		::DestroyMenu(m_hMDIMenu);
	if(m_hMenu != NULL)
		::DestroyMenu(m_hMenu);
	CloseHandle(m_hOneInstance);
	return CWinApp::ExitInstance();
}

void CRaclientApp::OnFileNew() //µÇÂ¼
{
	Connect();
}

void CRaclientApp::OnSysDisconnect() //×¢Ïú
{
	// TODO: Add your command handler code here
	Discon();
}



/////////////////////////////////////////////////////////////////////////////
// CRaclientApp message handlers

void CRaclientApp::OnUpdateSysDisconnect(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(m_candisconnect);
	
}

void CRaclientApp::Discon()//×¢Ïú
{
	if(m_SslSocket.m_hSocket==-1)//Á¬½ÓÒÑ¾­¶Ï¿ª
	{
		AfxMessageBox("×¢ÏúÊ§°Ü");
	}
	else
		((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlShouDown();

	if(((CMainFrame *)AfxGetMainWnd())->m_pInput!=NULL)
		((CMainFrame *)AfxGetMainWnd())->m_pInput->SendMessage(WM_CLOSE);

	if(((CMainFrame *)AfxGetMainWnd())->m_pAuditing!=NULL)
		((CMainFrame *)AfxGetMainWnd())->m_pAuditing->SendMessage(WM_CLOSE);


	if(((CMainFrame *)AfxGetMainWnd())->m_pMade!=NULL)
		((CMainFrame *)AfxGetMainWnd())->m_pMade->SendMessage(WM_CLOSE);

	if(((CMainFrame *)AfxGetMainWnd())->m_pRevoke!=NULL)
		((CMainFrame *)AfxGetMainWnd())->m_pRevoke->SendMessage(WM_CLOSE);

	SetMenu (AfxGetMainWnd()->m_hWnd,m_hMenu);
	m_candisconnect=false;
	m_pMainWnd->SetWindowText("RaClient-Î´µÇÂ¼");
	((CMainFrame*)m_pMainWnd)->SetToolBarHide();
	((CMainFrame *)AfxGetMainWnd())->SetPos(0);
	((CMainFrame *)AfxGetMainWnd())->SetStatusIcon(IDS_STRING_STATE,IDI_ICON2);
	((CMainFrame *)AfxGetMainWnd())->ShowFind(0);
}

void CRaclientApp::Connect()//µÇÂ½
{
	CLogDlg dlg;
	if(dlg.DoModal()!=IDOK)
		return;
	SetMenu(AfxGetMainWnd()->m_hWnd,m_hMDIMenu);
	m_candisconnect=true;
	m_pMainWnd->SetWindowText("RaClient-ÒÑµÇÂ¼");
	((CMainFrame*)m_pMainWnd)->SetToolBarShow();
	int cx=GetSystemMetrics(SM_CXMENUCHECK);
	int cy=GetSystemMetrics(SM_CYMENUCHECK);
	CMenu *pMenu=AfxGetMainWnd()->GetMenu();

	CMenu *pSubMenu=pMenu->GetSubMenu(3);
	pSubMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmp1,&m_bmp1);

	pSubMenu=pMenu->GetSubMenu(4);
	pSubMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmp2,&m_bmp2);

	pSubMenu=pMenu->GetSubMenu(5);
	pSubMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmp3,&m_bmp3);

	pSubMenu=pMenu->GetSubMenu(6);
	pSubMenu->SetMenuItemBitmaps(0,MF_BYPOSITION,&m_bmp4,&m_bmp4);

}
