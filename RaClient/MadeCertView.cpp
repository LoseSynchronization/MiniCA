// MadeCertView.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "MadeCertView.h"
#include "RaChildFrame.h"
#include "MainFrm.h"
#include <direct.h>
#include <errno.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView
IMPLEMENT_DYNCREATE(CMadeCertView, CFormView)

CMadeCertView::CMadeCertView()
	: CFormView(CMadeCertView::IDD)
{
	//{{AFX_DATA_INIT(CMadeCertView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_select=-1;
	((CRaclientApp *)AfxGetApp())->m_SslSocket.m_MadeList=&m_List;

}

CMadeCertView::~CMadeCertView()
{
}

void CMadeCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMadeCertView)
	DDX_Control(pDX, IDC_BUTTON_LINEANDMADE, m_Made);
	DDX_Control(pDX, IDC_BUTTON_AUT_MADE, m_Fmade);
	DDX_Control(pDX, IDC_LIST_MADE, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMadeCertView, CFormView)
	//{{AFX_MSG_MAP(CMadeCertView)
	ON_BN_CLICKED(IDC_BUTTON_LINEANDMADE, OnButtonLineandmade)
	ON_BN_CLICKED(IDC_BUTTON_AUT_MADE, OnButtonAutMade)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MADE, OnClickListMade)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO, OnSelchangeCombo)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_MADE, OnItemchangedListMade)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView diagnostics

#ifdef _DEBUG
void CMadeCertView::AssertValid() const
{
	CFormView::AssertValid();
}

void CMadeCertView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMadeCertView message handlers

void CMadeCertView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	m_Fmade.SetIcon(IDI_ICON_MADE);
	m_Made.SetIcon(IDI_ICON_FMADE);
	((CComboBox *)GetDlgItem(IDC_COMBO))->SetCurSel(0);

	// TODO: Add your specialized code here and/or call the base class
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
	strname[9]="֤���������";
	for(int i=0;i<10;i++)
	{
		m_List.InsertColumn(i,strname[i],LVCFMT_CENTER,120);
	}
	GetParentFrame()->SetWindowText("֤������");

}

void CMadeCertView::OnButtonLineandmade() //��ѯ������
{
	// TODO: Add your control notification handler code here
	m_List.DeleteAllItems();
	m_List.SetRedraw(FALSE);
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//����Ԫ��
	((CMainFrame *)AfxGetMainWnd())->ShowFind(1);
	CString query;//��ѯ���
	stuLIST * LIST=new stuLIST();
	stuCA CA;
	int select=((CComboBox *)GetDlgItem(IDC_COMBO))->GetCurSel();
	if(select==0)//����
	{
		CString dayB,dayE;
		GetDlgItemText(IDC_DATE_BEGIN,dayB);
		GetDlgItemText(IDC_DATE_END,dayE);
		query.Format("Select ID,USERINFO,AUDITIME From CERTLIST Where AUDITIME Between #%s# And #%s#  And CERTSTATE=1",dayB,dayE);

	}
	else//ID
	{
		CString id;
		GetDlgItemText(IDC_EDIT,id);
		if(id=="") return;
		query.Format("Select ID,USERINFO,AUDITIME From CERTLIST Where ID=%s and CERTSTATE=1",id);
	}
	CA.Type=FAuditD;//������
	strcpy(CA.SQL,query);
	LIST->CA=CA;
	((CRaclientApp *)AfxGetApp())->m_SslSocket.AddCommand((stuLIST *)LIST);
	((CRaChildFrame*)GetParentFrame( ))->AddMsg("������֤���ѯָ�������Ϣ���гɹ����ȴ�����......",M_WARING);
	if(!Select)
		((CRaclientApp *)AfxGetApp())->m_SslSocket.AsyncSelect(FD_WRITE|FD_CLOSE);
}


void CMadeCertView::OnButtonAutMade() //֤������
{
	// TODO: Add your control notification handler code here
	CString m_strPath;
	GetModuleFileName(NULL,m_strPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	m_strPath.ReleaseBuffer ();
	int nPos;
	nPos=m_strPath.ReverseFind ('\\');
	m_strPath=m_strPath.Left (nPos);
	CString lpszPath = m_strPath + "\\CERT";

	if(_mkdir(lpszPath) == -1)
	{
		if(errno==EEXIST)//Ŀ¼�Ѿ�����
		{
			((CMainFrame *)AfxGetMainWnd())->m_PathCert=lpszPath;
		}
		if(errno==ENOENT)//Ŀ¼û�з���
		{
			((CRaChildFrame*)GetParentFrame( ))->AddMsg("Ŀ¼����",M_ERROR);
			return;
		}
	}
	else
		((CMainFrame *)AfxGetMainWnd())->m_PathCert=lpszPath;

	CString query;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	BOOL Select=((CRaclientApp *)AfxGetApp())->m_SslSocket.GetComCount();//����Ԫ��
	if (pos == NULL)
		return;
	else
	{
		while (pos)
		{
			stuLIST * LIST=new stuLIST();
			stuCA CA;
			CString nItem = m_List.GetItemText(m_List.GetNextSelectedItem(pos),0);
			query.Format("Select ID,USERCERT,USERKEY,CERTSTATE,MADETIME From CERTLIST Where ID=%s",nItem);
			CA.Type=Made;
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

void CMadeCertView::OnClickListMade(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_select=m_List.GetSelectionMark();
	if(m_select==-1) return;
	m_List.SetItemState(m_select,LVIS_SELECTED,LVIS_SELECTED);
	m_List.SetFocus();
	m_num=m_List.GetItemText(m_select,0);//�ڲ����

//	*pResult = 0;
}

void CMadeCertView::OnDestroy() 
{
	CFormView::OnDestroy();
	((CMainFrame*)AfxGetMainWnd())->m_pMade=NULL; // ��մ���ָ��

	// TODO: Add your message handler code here
	
}

void CMadeCertView::OnSelchangeCombo() 
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

void CMadeCertView::OnItemchangedListMade(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	int count=m_List.GetSelectedCount();
	CString str;
	str.Format("%d",count);
	((CMainFrame *)AfxGetMainWnd())->SetStatusText(IDS_STRING_SELECT,str);

	*pResult = 0;
}
