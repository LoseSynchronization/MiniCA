// AuditingCertView.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "AuditingCertView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAuditingCertView
IMPLEMENT_DYNCREATE(CAuditingCertView, CFormView)

CAuditingCertView::CAuditingCertView()
	: CFormView(CAuditingCertView::IDD)
{
	//{{AFX_DATA_INIT(CAuditingCertView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	((CRaclientApp *)AfxGetApp())->m_SslSocket.m_AuditList=&m_List;
}

CAuditingCertView::~CAuditingCertView()
{
}

void CAuditingCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAuditingCertView)
	DDX_Control(pDX, IDC_BUTTON5, m_Naudit);
	DDX_Control(pDX, IDC_BUTTON_PASS, m_Paudit);
	DDX_Control(pDX, IDC_BUTTON_AUDITING, m_Faudit);
	DDX_Control(pDX, IDC_LIST_AUDITING, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAuditingCertView, CFormView)
	//{{AFX_MSG_MAP(CAuditingCertView)
	ON_BN_CLICKED(IDC_BUTTON_AUDITING, OnButtonAuditing)
	ON_BN_CLICKED(IDC_BUTTON_PASS, OnButtonPass)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_AUDITING, OnItemchangedListAuditing)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAuditingCertView diagnostics

#ifdef _DEBUG
void CAuditingCertView::AssertValid() const
{
	CFormView::AssertValid();
}

void CAuditingCertView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAuditingCertView message handlers

void CAuditingCertView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();

	m_Faudit.SetIcon(IDI_ICON_FAUDIT);
	m_Paudit.SetIcon(IDI_ICON_PAUDIT);
	m_Naudit.SetIcon(IDI_ICON_IC);
	// TODO: Add your specialized code here and/or call the base class
	GetParentFrame()->SetWindowText("证书审核");

	m_List.SetWindowPos(NULL,0,0,1024,420,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	CString strname[10];
	strname[0]="证书序列号";
	strname[1]="申请者名称";
	strname[2]="国家";
	strname[3]="省份";
	strname[4]="城市";
	strname[5]="组织";
	strname[6]="组织单元";
	strname[7]="Email";
	strname[8]="安全Email";
	strname[9]="证书录入日期";
	for(int i=0;i<10;i++)
	{
		m_List.InsertColumn(i,strname[i],LVCFMT_CENTER,120);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO))->SetCurSel(0);

}

void CAuditingCertView::OnButtonAuditing() 
{
	// TODO: Add your control notification handler code here
	m_List.DeleteAllItems();
	m_List.SetRedraw(FALSE);
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//存在元素

	stuLIST * LIST=new stuLIST();
	stuCA CA;
	CString query;//查询语句
	int select=((CComboBox *)GetDlgItem(IDC_COMBO))->GetCurSel();
	if(select==0)//日期
	{
		CString dayB,dayE;
		GetDlgItemText(IDC_DATE_BEGIN,dayB);
		GetDlgItemText(IDC_DATE_END,dayE);
		query.Format("Select ID,USERINFO,INPUTTIME From CERTLIST Where INPUTTIME Between #%s# And #%s#  And CERTSTATE=0",dayB,dayE);
		
	}
	else//ID
	{
		CString id;
		GetDlgItemText(IDC_EDIT,id);
		if(id=="") return;
		query.Format("Select ID,USERINFO,INPUTTIME From CERTLIST Where ID=%s and CERTSTATE=0",id);
	}
	CA.Type=FInputD;
	strcpy(CA.SQL,query);
	LIST->CA=CA;
	((CMainFrame *)AfxGetMainWnd())->ShowFind(1);
	((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
	((CRaChildFrame*)GetParentFrame( ))->AddMsg("待审核证书查询指令加入消息队列成功，等待发送......",M_WARING);
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);
}

void CAuditingCertView::OnButtonPass() 
{
	// TODO: Add your control notification handler code here
	CString query;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//存在元素
	if (pos == NULL)
		return;
	else
	{
		while (pos)
		{
			stuLIST * LIST=new stuLIST();
			stuCA CA;
			CString nItem = m_List.GetItemText(m_List.GetNextSelectedItem(pos),0);
			query.Format("Select ID,USERINFO,USERCERT,USERKEY,CERTSTATE,AUDITIME From CERTLIST Where ID=%s",nItem);
			CA.Type=Audit;
			strcpy(CA.SQL,query);
			LIST->ID=atoi(nItem);
			LIST->CA=CA;
			((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
		}
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("证书审核指令加入消息队列成功，等待发送......",M_WARING);
	}
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);

}

void CAuditingCertView::OnDestroy() 
{
	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_pAuditing=NULL; // 清空窗口指针

	// TODO: Add your message handler code here
	
}

void CAuditingCertView::OnSelchangeCombo() //改变查询
{
	// TODO: Add your control notification handler code here
	int select=((CComboBox *)GetDlgItem(IDC_COMBO))->GetCurSel();
	if(select==0)//日期
	{
		GetDlgItem(IDC_DATE_BEGIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_DATE_END)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDIT)->ShowWindow(SW_HIDE);
	}
	else
	{
		GetDlgItem(IDC_DATE_BEGIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_DATE_END)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDIT)->ShowWindow(SW_SHOW);
	}
}

void CAuditingCertView::OnItemchangedListAuditing(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int count=m_List.GetSelectedCount();
	CString str;
	str.Format("%d",count);
	((CMainFrame *)AfxGetMainWnd())->SetStatusText(IDS_STRING_SELECT,str);
	*pResult = 0;
}
