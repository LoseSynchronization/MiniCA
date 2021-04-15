// RevokeCertView.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "RevokeCertView.h"
#include "MainFrm.h"
#include <direct.h>
#include <errno.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRevokeCertView

IMPLEMENT_DYNCREATE(CRevokeCertView, CFormView)

CRevokeCertView::CRevokeCertView()
	: CFormView(CRevokeCertView::IDD)
{
	//{{AFX_DATA_INIT(CRevokeCertView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	((CRaclientApp *)AfxGetApp())->m_SslSocket.m_RevokeList=&m_List;
	m_FindType=false;
}

CRevokeCertView::~CRevokeCertView()
{
}

void CRevokeCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRevokeCertView)
	DDX_Control(pDX, IDC_BUTTON_FIND, m_Find);
	DDX_Control(pDX, IDC_B_CRL, m_Mcrl);
	DDX_Control(pDX, IDC_BUTTON_REVOKE, m_Revoke);
	DDX_Control(pDX, IDC_LIST_REVOKE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRevokeCertView, CFormView)
	//{{AFX_MSG_MAP(CRevokeCertView)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON_REVOKE, OnButtonRevoke)
	ON_BN_CLICKED(IDC_B_CRL, OnBCrl)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_BUTTON_FIND, OnButtonFind)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_REVOKE, OnItemchangedListRevoke)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRevokeCertView diagnostics

#ifdef _DEBUG
void CRevokeCertView::AssertValid() const
{
	CFormView::AssertValid();
}

void CRevokeCertView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CRevokeCertView message handlers

void CRevokeCertView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->m_pRevoke=NULL; // ��մ���ָ��
	
}

void CRevokeCertView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class

	m_Find.SetIcon(IDI_ICON_CERT);
	m_Revoke.SetIcon(IDI_ICON_REVOKE);
	m_Mcrl.SetIcon(IDI_ICON_MCRL);
	// TODO: Add your specialized code here and/or call the base class
	GetParentFrame()->SetWindowText("֤������");

	m_List.SetWindowPos(NULL,0,0,1024,420,SWP_NOMOVE|SWP_NOZORDER | SWP_NOACTIVATE);
	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	CString strname[10];
	strname[0]="֤�����к�";
	strname[1]="����������";
	strname[2]="����";
	strname[3]="ʡ��";
	strname[4]="����";
	strname[5]="��֯";
	strname[6]="��֯��Ԫ";
	strname[7]="Email";
	strname[8]="��ȫEmail";
	strname[9]="֤����������";
	for(int i=0;i<10;i++)
	{
		m_List.InsertColumn(i,strname[i],LVCFMT_CENTER,120);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO))->SetCurSel(0);
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(1);
}

void CRevokeCertView::OnSelchangeCombo() 
{
	// TODO: Add your control notification handler code here
	int select=((CComboBox *)GetDlgItem(IDC_COMBO))->GetCurSel();
	if(select==0)//����
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

void CRevokeCertView::OnButtonRevoke() //֤������
{
	// TODO: Add your control notification handler code here
	stuCA CA;
	CString query;
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//����Ԫ��
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;
	else
	{
		while (pos)
		{
			stuLIST * LIST=new stuLIST();
			stuCA CA;
			CString nItem = m_List.GetItemText(m_List.GetNextSelectedItem(pos),0);
			query.Format("Select ID,CERTSTATE,REVOKETIME From CERTLIST Where ID=%s",nItem);
			CA.Type=Revoke;
			strcpy(CA.SQL,query);
			LIST->ID=atoi(nItem);
			LIST->CA=CA;
			((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
		}
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("֤������ָ�������Ϣ���гɹ����ȴ�����......",M_WARING);
	}
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);
}

void CRevokeCertView::OnBCrl() //����������
{
	// TODO: Add your control notification handler code here
	CString m_strPath;
	GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	m_strPath.ReleaseBuffer ();
	int nPos;
	nPos=m_strPath.ReverseFind ('\\');
	m_strPath=m_strPath.Left (nPos);
	CString lpszPath = m_strPath + "\\CRL";

	if(_mkdir(lpszPath) == -1)
	{
		if(errno==EEXIST)//Ŀ¼�Ѿ�����
		{
			((CMainFrame *)AfxGetMainWnd())->m_PathCrl=lpszPath;
		}
		if(errno==ENOENT)//Ŀ¼û�з���
		{
			((CRaChildFrame*)GetParentFrame( ))->AddMsg("Ŀ¼����",M_ERROR);
			return;
		}
	}
	else
		((CMainFrame *)AfxGetMainWnd())->m_PathCrl=lpszPath;

	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//����Ԫ��
	stuLIST * LIST=new stuLIST();
	stuCA CA;
	CA.Type=MadeCrl;
	strcpy(CA.SQL,"Select ID,REVOKETIME From CERTLIST Where CERTSTATE=-1");
	LIST->CA=CA;
	((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
	((CRaChildFrame*)GetParentFrame( ))->AddMsg("����������ָ�������Ϣ���гɹ����ȴ�����......",M_WARING);
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);
}

void CRevokeCertView::OnRadio1() //��ѯ��Ч
{
	// TODO: Add your control notification handler code here
	m_FindType=false;
	m_Find.SetIcon(IDI_ICON_CERT);
	m_Find.Invalidate(FALSE);
}

void CRevokeCertView::OnRadio2() //��ѯ����
{
	// TODO: Add your control notification handler code here
	m_FindType=true;
	GetDlgItem(IDC_BUTTON_REVOKE)->EnableWindow(0);
	m_Find.SetIcon(IDI_ICON_FCRL);
	m_Find.Invalidate(FALSE);

}

void CRevokeCertView::OnButtonFind() 
{
	// TODO: Add your control notification handler code here
	m_List.DeleteAllItems();
	m_List.SetRedraw(FALSE);
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//����Ԫ��
	((CMainFrame *)AfxGetMainWnd())->ShowFind(1);

	stuLIST * LIST=new stuLIST();
	stuCA CA;
	CString query;//��ѯ���
	
	if(m_FindType)//��ѯ����
	{		
		query.Format("Select ID,USERINFO,REVOKETIME From CERTLIST Where CERTSTATE=-1");
		CA.Type=FRevokeD;
		strcpy(CA.SQL,query);
	}
	else////��ѯ��Ч
	{
		
		int select=((CComboBox *)GetDlgItem(IDC_COMBO))->GetCurSel();
		if(select==0)//����
		{
			CString dayB,dayE;
			GetDlgItemText(IDC_DATE_BEGIN,dayB);
			GetDlgItemText(IDC_DATE_END,dayE);
			query.Format("Select ID,USERINFO,MADETIME,REVOKETIME From CERTLIST Where MADETIME Between #%s# And #%s#  And CERTSTATE=2",dayB,dayE);
			
		}
		else//ID
		{
			CString id;
			GetDlgItemText(IDC_EDIT,id);
			if(id=="")
				return;
			query.Format("Select ID,USERINFO,MADETIME,REVOKETIME From CERTLIST Where ID=%s and CERTSTATE=1",id);
		}
		
		CA.Type=FMadeD;
		strcpy(CA.SQL,query);
		GetDlgItem(IDC_BUTTON_REVOKE)->EnableWindow(1);

	}
	LIST->CA=CA;
	((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
	((CRaChildFrame*)GetParentFrame( ))->AddMsg("֤����Ч/���ϲ�ѯָ�������Ϣ���гɹ����ȴ�����......",M_WARING);
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);

}

void CRevokeCertView::OnItemchangedListRevoke(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int count=m_List.GetSelectedCount();
	CString str;
	str.Format("%d",count);
	((CMainFrame *)AfxGetMainWnd())->SetStatusText(IDS_STRING_SELECT,str);	
	*pResult = 0;
}
