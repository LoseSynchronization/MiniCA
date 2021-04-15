// ProgStatusBar.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "ProgStatusBar.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgStatusBar

CProgStatusBar::CProgStatusBar()
{
}

CProgStatusBar::~CProgStatusBar()
{
}


BEGIN_MESSAGE_MAP(CProgStatusBar, CStatusBar)
	//{{AFX_MSG_MAP(CProgStatusBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgStatusBar message handlers

int CProgStatusBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->style |= WS_CLIPCHILDREN;
	if (CStatusBar::OnCreate(lpCreateStruct) == -1||
		m_wndProgQuery.Create(WS_CHILD|WS_VISIBLE|PBS_SMOOTH, CRect(), this, 1)==-1)
		return -1;
	return 0;
}

void CProgStatusBar::OnSize(UINT nType, int cx, int cy) 
{
	CStatusBar::OnSize(nType, cx, cy); 
	UINT inx;
	CRect rect;
	inx=CommandToIndex(IDS_STRING_PROGRESS_QUERY);
	GetItemRect(inx,&rect);
	m_wndProgQuery.MoveWindow(rect);
}

void CProgStatusBar::ShowProg(BOOL flag)
{
	if(!m_wndProgQuery)
		return;
	if(flag)
	{
		m_wndProgQuery.ShowWindow(SW_SHOW);
	}
	else
	{
		m_wndProgQuery.ShowWindow(SW_HIDE);
	}
}

void CProgStatusBar::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CStatusBarCtrl& statusBar = GetStatusBarCtrl();
    CRect rectPane;
    CPoint ptTmp(point);
	int inx=CommandToIndex(IDS_STRING_STATE);
    statusBar.GetRect(inx, rectPane);
    if (rectPane.PtInRect(ptTmp) )
    {
		if(((CRaclientApp *)AfxGetApp())->m_candisconnect==false)//Î´Á¬½Ó
		{
			((CRaclientApp *)AfxGetApp())->Connect();
		}
		else
		{
			((CRaclientApp *)AfxGetApp())->Discon();
		}
    }
   	CStatusBar::OnLButtonDblClk(nFlags, point);
}

