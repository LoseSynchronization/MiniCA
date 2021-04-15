// DlgBar.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "DlgBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBar dialog


CDlgBar::CDlgBar(CWnd* pParent /*=NULL*/)
	: CDialogBar()
{
	//{{AFX_DATA_INIT(CDlgBar)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBar)
	DDX_Control(pDX, IDC_LIST_INFO, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBar, CDialogBar)
	//{{AFX_MSG_MAP(CDlgBar)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBar message handlers

BOOL CDlgBar::OnInitDialogBar()
{
	UpdateData(FALSE);/////////////////////DDX
	return TRUE;
}
