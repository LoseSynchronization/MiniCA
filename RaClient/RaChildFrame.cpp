// RaChildFrame.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "RaChildFrame.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CRaChildFrame
//extern HANDLE gEven;

IMPLEMENT_DYNCREATE(CRaChildFrame, CMDIChildWnd)

CRaChildFrame::CRaChildFrame()
{
}


CRaChildFrame::~CRaChildFrame()
{
}


BEGIN_MESSAGE_MAP(CRaChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CRaChildFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRaChildFrame message handlers

int CRaChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	//创建对话条
	if(!m_wndBar.Create(this,IDD_DIALOGBAR,WS_CHILD|WS_VISIBLE|
		CBRS_BOTTOM|CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | 
		CBRS_SIZE_DYNAMIC,IDD_DIALOGBAR)||!m_wndBar.OnInitDialogBar())
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;      // fail to create
	}
	//操纵对话条上的CTabCtrl控件
	CTabCtrl * ptab=(CTabCtrl *)m_wndBar.GetDlgItem(IDC_TAB_INFO);
	ptab->InsertItem(0,"操作信息");
	ptab->SetImageList(&((CMainFrame *)AfxGetMainWnd())->m_imageList);
    
    TC_ITEM item;
    item.mask = TCIF_IMAGE;
	item.iImage = 6;
    ptab->SetItem (0, &item );

	m_wndBar.m_List.SetWindowPos(NULL,0,0,GetSystemMetrics(SM_CXSCREEN)-11,75,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE|SWP_SHOWWINDOW);
	return 0;
}

void CRaChildFrame::AddMsg(CString str,DWORD info)
{
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	CString time;
	time.Format(_T(" %d年%d月%d日 %d时:%d分：%d秒   "), tm.wYear,tm.wMonth,tm.wDay,tm.wHour, tm.wMinute,tm.wSecond);
	m_wndBar.m_List.AddMsg(time+str,info);
}
