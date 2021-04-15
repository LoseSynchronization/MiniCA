// UsbKeySheet.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbKeySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbKeySheet

IMPLEMENT_DYNAMIC(CUsbKeySheet, CPropertySheet)

CUsbKeySheet::CUsbKeySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

CUsbKeySheet::CUsbKeySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

CUsbKeySheet::~CUsbKeySheet()
{
	m_imgList.Detach( );
}


BEGIN_MESSAGE_MAP(CUsbKeySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CUsbKeySheet)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbKeySheet message handlers

BOOL CUsbKeySheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	// TODO: Add your specialized code here
	m_imgList.Create(16,16,TRUE|ILC_COLOR8,4,4);
	HICON hIcon = NULL;

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_DISK), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_PWD), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_CERT), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_SO), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_EXTERN), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_CA), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_CLIENT), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_SERVER), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_EVP), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_RA), IMAGE_ICON, 16, 16, 0);
	m_imgList.Add(hIcon);

//	CFont font;
//	font.CreateFont(-8,0,0,0,FW_BOLD,0,0,0,1,0,0,0,0,_T("MS Sans Serif"));
	CTabCtrl * pTab=GetTabControl();
	ASSERT(pTab);
	if(pTab)
	{
//		pTab->SetFont(&font);
		pTab->SetImageList(&m_imgList);
	}

	////////////////////////系统托盘//////////////////////////////////////////////////////
	m_nid.cbSize = sizeof( NOTIFYICONDATA );
	m_nid.hWnd = m_hWnd; 
	m_nid.uID = ID_SYSTEMTRAY; 
	m_nid.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	m_nid.uCallbackMessage = WM_SYSTEMTRAY;//自定义消息
	m_nid.hIcon = AfxGetApp()->LoadIcon( IDI_ICON_KEY );
	strcpy( m_nid.szTip, "MiniCA");
	::Shell_NotifyIcon( NIM_ADD,&m_nid );
	////////////////////////////////////////////////////////////////////////////////////
	return bResult;
}

int CUsbKeySheet::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	EnableStackedTabs(TRUE);//多行显示
	if (CPropertySheet::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO: Add your specialized creation code here
	SetWindowLong(this->m_hWnd,GWL_STYLE,
        GetWindowLong(this->m_hWnd,GWL_STYLE) | WS_MINIMIZEBOX);
	return 0;
}

void CUsbKeySheet::OnDestroy() 
{
	CPropertySheet::OnDestroy();
	
	// TODO: Add your message handler code here
	::Shell_NotifyIcon( NIM_DELETE,&m_nid );
	
}

LRESULT CUsbKeySheet::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch(message)
	{
		
	case WM_SYSTEMTRAY:  //自定义消息     
		if(lParam==WM_LBUTTONDOWN)
		{  
			//	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOW);
				AfxGetApp()->m_pMainWnd->ShowWindow(SW_RESTORE);
				AfxGetApp()->m_pMainWnd->SetForegroundWindow();
		}
		else if(lParam==WM_RBUTTONDOWN)
		{ 
/*			POINT point;
			HMENU hMenu, hSubMenu;
			GetCursorPos(&point);
			hMenu = LoadMenu(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MENU_TRAY));
			hSubMenu = GetSubMenu(hMenu, 0);
			SetForegroundWindow(); //点击可以关闭
			TrackPopupMenu(hSubMenu,
				TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_LEFTALIGN,
				point.x, point.y, 0, AfxGetApp()->m_pMainWnd->m_hWnd, NULL);
			DestroyMenu(hMenu);
			
*/		}
		break;
		
	case WM_SYSCOMMAND: //系统消息    
		
		if(wParam==SC_MINIMIZE)
		{ 
			AfxGetApp()->m_pMainWnd->ShowWindow(SW_HIDE);//窗口隐藏
			return 0;
		}
		break;
	}		
	return CPropertySheet::WindowProc(message, wParam, lParam);
}
