// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Raclient.h"
#include "MainFrm.h"
#include "rachildframe.h"
#include "inputcertview.h"
#include "AuditingCertView.h"
#include "MadeCertView.h"
#include "RevokeCertView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame
const UINT ID_RA_MSG =::RegisterWindowMessage(ra_MSG);

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_INPUT_UNIT, OnInputUnit)
	ON_COMMAND(ID_AUDITING_CERT, OnAuditingCert)
	ON_COMMAND(ID_MADE_MADE, OnMadeMade)
	ON_COMMAND(ID_CERT_REVOKE, OnCertRevoke)
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(ID_RA_MSG,OnRaMsg)
	ON_NOTIFY_EX(TTN_NEEDTEXT,0,ShowTips) 

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	IDS_STRING6_FIND,		//查询
	IDS_STRING_PROGRESS,	//进度条
	IDS_STRING_STATE,		//icon
	IDS_STRING_SELECT,		//选择数量
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_pInput=m_pAuditing=m_pMade=m_pRevoke=NULL;
}

CMainFrame::~CMainFrame()
{
	m_imageList.Detach();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC|CCS_ADJUSTABLE) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	m_imageList.Create(16, 16, TRUE | ILC_COLOR8, 6, 0);
	HICON hIcon = NULL;

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON2), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON3), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON4), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON5), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON8), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON6), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON7), IMAGE_ICON, 16, 16, 0);
	m_imageList.Add(hIcon);



	m_wndToolBar.GetToolBarCtrl().SetImageList(&m_imageList);

	SetToolBarHide();

	if (!m_wndStatusBar.CreateEx(this,SBT_TOOLTIPS)||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	ShowFind(0);
	SetStatusIcon(IDS_STRING_STATE,IDI_ICON2);/////////////////----SetPaneInfo

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable


	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	int cxScreen = GetSystemMetrics(SM_CXSCREEN);
    int cyScreen = GetSystemMetrics(SM_CYSCREEN);
	cs.cx=cxScreen;
	cs.cy=cyScreen;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnInputUnit() 
{
	// TODO: Add your command handler code here
	if(m_pInput!=NULL)
	{
		m_pInput->MDIActivate();
		return;
	}

	m_pInput=new CRaChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CInputCertView);
	if(!m_pInput->LoadFrame(IDI_ICON3,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
	m_pInput->ShowWindow(SW_SHOWMAXIMIZED);
	m_pInput->InitialUpdateFrame(NULL,true);
}

void CMainFrame::OnAuditingCert() 
{
	// TODO: Add your command handler code here
	if(m_pAuditing!=NULL)
	{
		m_pAuditing->MDIActivate();
		return;
	}

	m_pAuditing=new CRaChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CAuditingCertView);
	if(!m_pAuditing->LoadFrame(IDI_ICON4,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
	m_pAuditing->ShowWindow(SW_SHOWMAXIMIZED);
	m_pAuditing->InitialUpdateFrame(NULL,true);
}


void CMainFrame::OnMadeMade() 
{
	// TODO: Add your command handler code here
	if(m_pMade!=NULL)
	{
		m_pMade->MDIActivate();
		return;
	}

	m_pMade=new CRaChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CMadeCertView);
	if(!m_pMade->LoadFrame(IDI_ICON5,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
	m_pMade->ShowWindow(SW_SHOWMAXIMIZED);
	m_pMade->InitialUpdateFrame(NULL,true);
}

void CMainFrame::OnCertRevoke() 
{
	// TODO: Add your command handler code here
	if(m_pRevoke!=NULL)
	{
		m_pRevoke->MDIActivate();
		return;
	}

	m_pRevoke=new CRaChildFrame();
	CCreateContext context;
	context.m_pNewViewClass=RUNTIME_CLASS(CRevokeCertView);
	if(!m_pRevoke->LoadFrame(IDI_ICON8,WS_MAXIMIZE|WS_OVERLAPPEDWINDOW,this,&context))
		return;
	m_pRevoke->ShowWindow(SW_SHOWMAXIMIZED);
	m_pRevoke->InitialUpdateFrame(NULL,true);
}

void CMainFrame::SetToolBarShow()
{
	m_wndToolBar.GetToolBarCtrl().SetState(ID_FILE_NEW,TBSTATE_HIDDEN);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_SYS_DISCONNECT,TBSTATE_ENABLED);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_INPUT_UNIT,TBSTATE_ENABLED);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_AUDITING_CERT,TBSTATE_ENABLED);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_MADE_MADE,TBSTATE_ENABLED);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_CERT_REVOKE,TBSTATE_ENABLED);
	RecalcLayout( );
//	m_wndToolBar.GetToolBarCtrl().AutoSize();

}

void CMainFrame::SetToolBarHide()
{
	m_wndToolBar.GetToolBarCtrl().SetState(ID_FILE_NEW,TBSTATE_ENABLED);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_SYS_DISCONNECT,TBSTATE_HIDDEN);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_INPUT_UNIT,TBSTATE_HIDDEN);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_AUDITING_CERT,TBSTATE_HIDDEN);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_MADE_MADE,TBSTATE_HIDDEN);
	m_wndToolBar.GetToolBarCtrl().SetState(ID_CERT_REVOKE,TBSTATE_HIDDEN);
	RecalcLayout( );
//	m_wndToolBar.GetToolBarCtrl().AutoSize();

}

LRESULT CMainFrame::OnRaMsg( WPARAM wParam,LPARAM lParam )
{
// process message
//	SetForegroundWindow();
	ShowWindow(SW_SHOWMAXIMIZED);
	return 0;
}

void CMainFrame::AddDialogBarInfo(int index, CString msg,int info)
{
	if(index==0)//录入对话条
	{
		if(m_pInput==NULL)
			return;
		else
			m_pInput->AddMsg(msg,info);
	}
	else if(index==1)//审核对话条
	{
		if(m_pAuditing==NULL)
			return;
		else
			m_pAuditing->AddMsg(msg,info);
	}
	else if(index==2)//制作对话条
	{
		if(m_pMade==NULL)
			return;
		else
			m_pMade->AddMsg(msg,info);
	}
	else if(index==3)//作废对话条
	{
		if(m_pRevoke==NULL)
			return;
		else
			m_pRevoke->AddMsg(msg,info);
	}
}

void CMainFrame::SetRange(int nLower, int nUpper)
{
	m_wndStatusBar.m_wndProgQuery.SetRange32(nLower,nUpper);
}

int CMainFrame::SetPos(int nPos)
{
	return m_wndStatusBar.m_wndProgQuery.SetPos(nPos);
}

void CMainFrame::SetStatusIcon(int nPane,UINT nICON)//状态栏显示图标
{
	HICON icon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(nICON),IMAGE_ICON,16,16,LR_DEFAULTCOLOR);
	int inx=m_wndStatusBar.CommandToIndex(nPane);
	m_wndStatusBar.GetStatusBarCtrl().SetIcon(inx,icon);//icon
    m_wndStatusBar.SetPaneInfo(inx,nPane,SBPS_NORMAL,16);

}

void CMainFrame::SetStatusText(int nPane,CString str)
{
	int inx=m_wndStatusBar.CommandToIndex(nPane);
	m_wndStatusBar.SetPaneStyle(inx,SBPS_NORMAL);
	m_wndStatusBar.SetPaneText(inx,str);
}

void CMainFrame::ShowFind(BOOL flag)
{
	if(!flag)//隐藏
	{
		m_wndStatusBar.SetPaneStyle(1,SBPS_NOBORDERS|SBPS_DISABLED);
		m_wndStatusBar.SetPaneStyle(2,SBPS_NOBORDERS|SBPS_DISABLED);
		m_wndStatusBar.SetPaneStyle(4,SBPS_DISABLED);
	}
	else
	{
		m_wndStatusBar.SetPaneStyle(1,SBPS_NOBORDERS);
	}
	m_wndStatusBar.ShowProg(flag);
}

BOOL CMainFrame::ShowTips(UINT id,NMHDR* pNMHDR,LRESULT* pResult)
{
	ASSERT(pNMHDR->code == TTN_NEEDTEXTA); 
	TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
	UINT nID = pNMHDR->idFrom;
	UINT inx=m_wndStatusBar.CommandToIndex(IDS_STRING_STATE);

	////如果idFrom是一个子窗口，则得到其ID。
	if ((pTTTA->uFlags & TTF_IDISHWND))
	{
		nID = ::GetDlgCtrlID((HWND)nID);
	}
	if(nID==inx)
	{
		strcpy(pTTTA->lpszText,"连接状态");
		return TRUE;
	}
	return FALSE;
}

