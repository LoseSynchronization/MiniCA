// UsbPwdPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbPwdPage.h"
#include "usbinfopage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbPwdPage property page

IMPLEMENT_DYNCREATE(CUsbPwdPage, CPropertyPage)

CUsbPwdPage::CUsbPwdPage() : CPropertyPage(CUsbPwdPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbPwdPage)
	//}}AFX_DATA_INIT
	m_handle=((CUsbKeyApp * )AfxGetApp())->m_handle;
	m_max=0;
	m_current=0;

}

CUsbPwdPage::~CUsbPwdPage()
{
}

void CUsbPwdPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbPwdPage)
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Control(pDX, IDC_STATIC_STATE, m_State);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbPwdPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbPwdPage)
	ON_BN_CLICKED(IDC_B_VERUSER, OnBVeruser)
	ON_BN_CLICKED(IDC_B_MODPWD, OnBModpwd)
	ON_BN_CLICKED(IDC_B_VERSO, OnBVerso)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbPwdPage message handlers
BOOL CUsbPwdPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	GetUsbState();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbPwdPage::GetUsbState()//得到usbkey状态，是否锁定
{
	BYTE create,del;
	((CUsbInfoPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(0))->GetAccessInfo(&create,&del,&m_max,&m_current);
	char buf[10]={0};
	SetDlgItemText(IDC_EDIT_TESTMAX,itoa(m_max,buf,10));
	SetDlgItemText(IDC_EDIT_TESTCURRENT,itoa(m_current,buf,10));
	if(m_current>=0)
	{
		m_State.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONUNLOCK));
		GetDlgItem(IDC_B_VERUSER)->EnableWindow(true);
		GetDlgItem(IDC_B_MODPWD)->EnableWindow(true);
	}
	if(m_current==0)
	{
		m_State.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LOCK));
		GetDlgItem(IDC_B_VERUSER)->EnableWindow(false);
		GetDlgItem(IDC_B_MODPWD)->EnableWindow(false);
	}
}


void CUsbPwdPage::OnBVeruser() //验证用户密码
{
	// TODO: Add your control notification handler code here
	CString strUsb;
	GetDlgItemText(IDC_EDIT_UPWD2,strUsb);
	if(strUsb=="")
	{
		m_List.AddMsg("输入为空",M_WARING);
		return;
	}

	if(USBKey_VerifyPin(m_handle,1,(UCHAR *)strUsb.GetBuffer(0))==FALSE)//验证用户口令	
		m_List.AddMsg("验证用户密码失败",M_ERROR);
	else
	{
		m_List.AddMsg("验证用户密码成功");
		((CUsbKeyApp * )AfxGetApp())->m_VerifyUser=true;
	}
	GetUsbState();	
	
}

void CUsbPwdPage::OnBVerso() //验证管理员密码
{
	// TODO: Add your control notification handler code here
	CString strUsb;
	GetDlgItemText(IDC_EDIT_SPWD,strUsb);
	if(strUsb=="")
	{
		m_List.AddMsg("输入为空",M_WARING);
		return;
	}

	if(USBKey_VerifyPin(m_handle,0,(UCHAR *)strUsb.GetBuffer(0))==FALSE)//验证用户口令	
		m_List.AddMsg("验证管理员失败",M_ERROR);
	else
	{
		((CUsbKeyApp * )AfxGetApp())->m_VerifySo=true;
		((CUsbKeyApp * )AfxGetApp())->m_SoPin=strUsb;
		m_List.AddMsg("验证管理员成功");
	}
		
}



void CUsbPwdPage::OnBModpwd() //修改用户密码
{
	// TODO: Add your control notification handler code here
	CString strUsb1,strUsb2;
	GetDlgItemText(IDC_EDIT_UPWD3,strUsb1);
	GetDlgItemText(IDC_EDIT_UPWD4,strUsb2);
	if(strUsb1==""||strUsb2=="")
	{
		m_List.AddMsg("输入为空",M_WARING);
		return;
	}

	if(USBKey_ChangePin(m_handle,0,(UCHAR *)strUsb1.GetBuffer(0),
		(UCHAR *)strUsb2.GetBuffer(0))==FALSE)//改变密码
		m_List.AddMsg("修改用户密码失败",M_ERROR);
	else
		m_List.AddMsg("修改用户密码成功");
	GetUsbState();	

}



BOOL CUsbPwdPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUsbState();	
	return CPropertyPage::OnSetActive();
}
