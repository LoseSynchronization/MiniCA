// UsbProcPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbProcPage.h"
#include "usbinfopage.h"
#include "usbpwdpage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "..\evp.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbProcPage property page

IMPLEMENT_DYNCREATE(CUsbProcPage, CPropertyPage)

CUsbProcPage::CUsbProcPage() : CPropertyPage(CUsbProcPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbProcPage)
	//}}AFX_DATA_INIT
	m_handle=((CUsbKeyApp * )AfxGetApp())->m_handle;
	m_OpenPub=false;
	m_OpenPri=false;

}

CUsbProcPage::~CUsbProcPage()
{
}

void CUsbProcPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbProcPage)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_LIST_PROC, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbProcPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbProcPage)
	ON_BN_CLICKED(IDC_B_ENC, OnBEnc)
	ON_BN_CLICKED(IDC_B_DEC, OnBDec)
	ON_BN_CLICKED(IDC_BSIGN, OnBsign)
	ON_BN_CLICKED(IDC_B_VERIFY, OnBVerify)
	ON_BN_CLICKED(IDC_B_SEAL, OnBSeal)
	ON_BN_CLICKED(IDC_B_OPEN, OnBOpen)
	ON_BN_CLICKED(IDC_B_GETRAND, OnBGetrand)
	ON_BN_CLICKED(IDC_BSOUT, OnBsout)
	ON_BN_CLICKED(IDC_BSIN, OnBsin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbProcPage message handlers

void CUsbProcPage::GetUsbState()
{
	if(((CUsbKeyApp * )AfxGetApp())->m_VerifyUser!=true)//未认证用户-关闭
	{
		GetDlgItem(IDC_B_ENC)->EnableWindow(0);
		GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
		GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
		GetDlgItem(IDC_B_ENC)->EnableWindow(0);
		GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
		GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
		return;
	}

	else//使用USB共钥
	{

		if(((CUsbKeyApp * )AfxGetApp())->m_ChangeKey==false)//磁盘没有改变
		{
			if(m_OpenPub!=true&&GetUsbPubCert()==true)
			{
				GetDlgItem(IDC_B_ENC)->EnableWindow(1);
				GetDlgItem(IDC_B_VERIFY)->EnableWindow(1);
				GetDlgItem(IDC_B_SEAL)->EnableWindow(1);
			}
			
			if(m_OpenPri!=true&&GetUsbPriCert()==true)
			{
				GetDlgItem(IDC_B_DEC)->EnableWindow(1);
				GetDlgItem(IDC_BSIGN)->EnableWindow(1);
				GetDlgItem(IDC_B_OPEN)->EnableWindow(1);
			}
		}
		else if(((CUsbKeyApp * )AfxGetApp())->m_ChangeKey==true)//磁盘改变
		{

			GetDlgItem(IDC_B_ENC)->EnableWindow(0);
			GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
			GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
			GetDlgItem(IDC_B_DEC)->EnableWindow(0);
			GetDlgItem(IDC_BSIGN)->EnableWindow(0);
			GetDlgItem(IDC_B_OPEN)->EnableWindow(0);
	
			if(GetUsbPubCert()==true)//取得公钥//开放公钥程序
			{
				GetDlgItem(IDC_B_ENC)->EnableWindow(1);
				GetDlgItem(IDC_B_VERIFY)->EnableWindow(1);
				GetDlgItem(IDC_B_SEAL)->EnableWindow(1);
			}
			if(GetUsbPriCert()==true)//开放私钥程序
			{
				GetDlgItem(IDC_B_DEC)->EnableWindow(1);
				GetDlgItem(IDC_BSIGN)->EnableWindow(1);
				GetDlgItem(IDC_B_OPEN)->EnableWindow(1);
			}
			((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=false;

		}
	}
}

bool CUsbProcPage::GetUsbPubCert()//取得usb共钥
{
	if(USBKey_ReadCert(m_handle,1,(unsigned char *)m_pubkey,&m_pubkey_len)==FALSE)//成功
	{
		m_List.AddMsg("找不到USB公钥证书",M_ERROR);
		return FALSE;
	}
	m_OpenPub=true;
	m_List.AddMsg("获得公钥成功");
	return true;
}

bool CUsbProcPage::GetUsbPriCert()
{
	//////////////读出私钥文件///////////////////////////
	if(USBKey_ReadCert(m_handle,0,(unsigned char *)m_prikey,(ULONG *)&m_prikey_len)==FALSE)
	{
		m_List.AddMsg("获得私钥失败",M_ERROR);
		return false;
	}
	/////////////////////////////////////////////////////
	m_OpenPri=true;
	m_List.AddMsg("获得私钥成功");
	return true;

}

BOOL CUsbProcPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
//	GetUsbState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbProcPage::DrawProg(int i)
{
	((CUsbProcPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(2))->
		m_Progress.SetPos(i);
}

void CUsbProcPage::OnBEnc() //公钥加密
{
	// TODO: Add your control notification handler code here
	CString cert,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!RSAEnc(m_pubkey,m_pubkey_len,filein.GetBuffer(0),fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("加密成功");
}

void CUsbProcPage::OnBDec() //私钥解密
{
	// TODO: Add your control notification handler code here
	CString key,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
	if(!RSADec(m_prikey,m_prikey_len,filein.GetBuffer(0), 
		  fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("解密成功");
}

void CUsbProcPage::OnBsign() //数字签名-----使用签名私钥进行签名
{
	// TODO: Add your control notification handler code here
	CString mdname("sha1"),filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!Sign(m_prikey,m_prikey_len,mdname.GetBuffer(0),filein.GetBuffer(0),
		fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("数字签名成功");
}

void CUsbProcPage::OnBVerify() //验证数字签名---公钥
{
	// TODO: Add your control notification handler code here
	CString mdname("sha1"),filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!VerifySign(m_pubkey,m_pubkey_len,mdname.GetBuffer(0),filein.GetBuffer(0),
		fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("验证签名成功");
}

void CUsbProcPage::OnBSeal() //装信封--公钥
{
	// TODO: Add your control notification handler code here

	CString cpname("idea-cbc"),filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!Seal(m_pubkey,m_pubkey_len,cpname.GetBuffer(0),filein.GetBuffer(0),
			fileout.GetBuffer(0),outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("封装文件成功");
}

void CUsbProcPage::OnBOpen() //打开数字信封--私钥
{
	// TODO: Add your control notification handler code here
	CString cpname("idea-cbc"),filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!OpenSeal(m_prikey,m_prikey_len,cpname.GetBuffer(0),filein.GetBuffer(0),
			fileout.GetBuffer(0),outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("拆封文件成功");
}

void CUsbProcPage::OnBGetrand() 
{
	// TODO: Add your control notification handler code here
	CString strLeng;
	GetDlgItemText(IDC_EDIT_LEN,strLeng);
	if(strLeng=="")
	{
		m_List.AddMsg("长度为空",M_WARING);
		return;
	}

	UCHAR buf[1024]={0};
	USBKey_GetRandom(m_handle,atoi(strLeng),buf);
	CString str;
	SetDlgItemText(IDC_EDIT_RAND,(LPCTSTR)buf);

}

BOOL CUsbProcPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUsbState();
	return CPropertyPage::OnSetActive();
}

void CUsbProcPage::OnBsout() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_INFILE,dlgOpen.GetPathName());

}

void CUsbProcPage::OnBsin()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择保存文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_OUTFILE,dlgOpen.GetPathName());
}
