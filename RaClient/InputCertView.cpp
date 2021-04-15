// InputCertView.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "InputCertView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInputCertView
IMPLEMENT_DYNCREATE(CInputCertView, CFormView)

CInputCertView::CInputCertView()
	: CFormView(CInputCertView::IDD)
{
	//{{AFX_DATA_INIT(CInputCertView)
	//}}AFX_DATA_INIT
}

CInputCertView::~CInputCertView()
{
}

void CInputCertView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInputCertView)
	DDX_Control(pDX, IDC_BUTTON_CANCLE, m_Cancle);
	DDX_Control(pDX, IDC_BUTTON_APPLY, m_Apply);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInputCertView, CFormView)
	//{{AFX_MSG_MAP(CInputCertView)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_CANCLE, OnButtonCancle)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInputCertView diagnostics

#ifdef _DEBUG
void CInputCertView::AssertValid() const
{
	CFormView::AssertValid();
}

void CInputCertView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CInputCertView message handlers
void CInputCertView::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	m_Apply.SetIcon(IDI_ICON_I);
	m_Cancle.SetIcon(IDI_ICON_IC);
	
	for(int i=IDC_CHECK1;i<=IDC_CHECK9;i++)
	{
		((CButton*)GetDlgItem(i))->SetCheck(true);
	}
	GetParentFrame()->SetWindowText("证书申请");
	GetDlgItem(IDC_EDIT1)->SetWindowText("个体名称");
	GetDlgItem(IDC_EDIT2)->SetWindowText("中国");
	GetDlgItem(IDC_EDIT3)->SetWindowText("河北");
	GetDlgItem(IDC_EDIT4)->SetWindowText("石家庄");
	GetDlgItem(IDC_EDIT5)->SetWindowText("全球商务");
	GetDlgItem(IDC_EDIT6)->SetWindowText("商务部");
	GetDlgItem(IDC_EDIT7)->SetWindowText("hpxs@hotmail.com");
	GetDlgItem(IDC_EDIT8)->SetWindowText("hpxs@hotmail.com");

	GetDlgItem(IDC_COMBO_L)->SetWindowText("1024");
	GetDlgItem(IDC_EDIT_DAY)->SetWindowText("365");

}




void CInputCertView::OnButtonApply() //申请按钮
{

	// TODO: Add your control notification handler code here
	stuCERT sCERT;

	CString str;
	GetDlgItemText(IDC_EDIT1,str);
	if(str.IsEmpty())
	{
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("名称不能为空",M_ERROR);
		return;
	}
	stuCA CA;
	strncpy((char *)sCERT.SUBJECT.CN,str,sizeof(sCERT.SUBJECT.CN));
	GetDlgItemText(IDC_EDIT2,str);
	strncpy((char *)sCERT.SUBJECT.C,str,sizeof(sCERT.SUBJECT.C));
	GetDlgItemText(IDC_EDIT3,str);
	strncpy((char *)sCERT.SUBJECT.ST,str,sizeof(sCERT.SUBJECT.ST));
	GetDlgItemText(IDC_EDIT4,str);
	strncpy((char *)sCERT.SUBJECT.L,str,sizeof(sCERT.SUBJECT.L));
	GetDlgItemText(IDC_EDIT5,str);
	strncpy((char *)sCERT.SUBJECT.O,str,sizeof(sCERT.SUBJECT.O));
	GetDlgItemText(IDC_EDIT6,str);
	strncpy((char *)sCERT.SUBJECT.OU,str,sizeof(sCERT.SUBJECT.OU));
	GetDlgItemText(IDC_EDIT7,str);
	strncpy((char *)sCERT.SUBJECT.MAIL,str,sizeof(sCERT.SUBJECT.MAIL));
	GetDlgItemText(IDC_EDIT8,str);
	strncpy((char *)sCERT.SUBJECT.PMAIL,str,sizeof(sCERT.SUBJECT.PMAIL));

	sCERT.KUSAGE.DS=((CButton *)GetDlgItem(IDC_CHECK1))->GetCheck();
	sCERT.KUSAGE.NR=((CButton *)GetDlgItem(IDC_CHECK2))->GetCheck();
	sCERT.KUSAGE.KE=((CButton *)GetDlgItem(IDC_CHECK3))->GetCheck();
	sCERT.KUSAGE.DE=((CButton *)GetDlgItem(IDC_CHECK4))->GetCheck();
	sCERT.KUSAGE.KA=((CButton *)GetDlgItem(IDC_CHECK5))->GetCheck();
	sCERT.KUSAGE.KC=((CButton *)GetDlgItem(IDC_CHECK6))->GetCheck();
	sCERT.KUSAGE.CS=((CButton *)GetDlgItem(IDC_CHECK7))->GetCheck();
	sCERT.KUSAGE.EO=((CButton *)GetDlgItem(IDC_CHECK8))->GetCheck();
	sCERT.KUSAGE.DO=((CButton *)GetDlgItem(IDC_CHECK9))->GetCheck();

	sCERT.EKUSAGE.SA=((CButton *)GetDlgItem(IDC_CHECK10))->GetCheck();
	sCERT.EKUSAGE.CA=((CButton *)GetDlgItem(IDC_CHECK11))->GetCheck();
	sCERT.EKUSAGE.CS=((CButton *)GetDlgItem(IDC_CHECK12))->GetCheck();
	sCERT.EKUSAGE.EP=((CButton *)GetDlgItem(IDC_CHECK13))->GetCheck();
	sCERT.EKUSAGE.TS=((CButton *)GetDlgItem(IDC_CHECK14))->GetCheck();
	sCERT.EKUSAGE.msCC=((CButton *)GetDlgItem(IDC_CHECK15))->GetCheck();
	sCERT.EKUSAGE.msCTLS=((CButton *)GetDlgItem(IDC_CHECK16))->GetCheck();
	sCERT.EKUSAGE.msSGC=((CButton *)GetDlgItem(IDC_CHECK17))->GetCheck();
	sCERT.EKUSAGE.msEFS=((CButton *)GetDlgItem(IDC_CHECK18))->GetCheck();
	sCERT.EKUSAGE.msSC=((CButton *)GetDlgItem(IDC_CHECK19))->GetCheck();
	sCERT.EKUSAGE.IP=((CButton *)GetDlgItem(IDC_CHECK20))->GetCheck();

	CA.Type=Input;
	if(((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlSend((char *)&CA,sizeof(CA))>0)
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("发送证书录入指令头成功",M_WARING);
	else
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("发送证书录入指令头失败",M_ERROR);
	if(((CRaclientApp *)AfxGetApp())->m_SslSocket.SSlSend((char *)&sCERT,sizeof(sCERT))>0)
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("发送证书录入指令成功,等待服务器回应......",M_WARING);
	else
		((CRaChildFrame*)GetParentFrame( ))->AddMsg("发送证书录入指令失败",M_ERROR);

}


void CInputCertView::OnButtonCancle() 
{
	// TODO: Add your control notification handler code here
}

void CInputCertView::OnDestroy() 
{
	CFormView::OnDestroy();
	// TODO: Add your message handler code here
	((CMainFrame*)AfxGetMainWnd())->m_pInput=NULL; // 清空窗口指针
}
