// UsbEvpPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbEvpPage.h"

#include "..\evp.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbEvpPage property page

IMPLEMENT_DYNCREATE(CUsbEvpPage, CPropertyPage)

CUsbEvpPage::CUsbEvpPage() : CPropertyPage(CUsbEvpPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbEvpPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_per=0;
}

CUsbEvpPage::~CUsbEvpPage()
{
}

void CUsbEvpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbEvpPage)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_LIST_EVP, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbEvpPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbEvpPage)
	ON_BN_CLICKED(IDC_BSOUT, OnBsout)
	ON_BN_CLICKED(IDC_BSIN, OnBsin)
	ON_BN_CLICKED(IDC_BENC, OnBenc)
	ON_BN_CLICKED(IDC_BDEC, OnBdec)
	ON_BN_CLICKED(IDC_BSEAL, OnBseal)
	ON_BN_CLICKED(IDC_BOPENSEAL, OnBopenseal)
	ON_BN_CLICKED(IDC_BDIGEST, OnBdigest)
	ON_BN_CLICKED(IDC_BSIGN, OnBsign)
	ON_BN_CLICKED(IDC_BVSIGN, OnBvsign)
	ON_BN_CLICKED(IDC_BRSACERT, OnBrsacert)
	ON_BN_CLICKED(IDC_BRSAKEY, OnBrsakey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbEvpPage message handlers
BOOL CUsbEvpPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_COMBO_CRYPT,"idea-cbc");
	SetDlgItemText(IDC_COMBO_DIGEST,"sha1");
	m_Progress.SetRange(0,100);
	m_Progress.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbEvpPage::OnBsout() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_INFILE,dlgOpen.GetPathName());

}

void CUsbEvpPage::OnBsin() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择保存文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_OUTFILE,dlgOpen.GetPathName());
	
}

void CUsbEvpPage::OnBenc() //对称加密
{
	// TODO: Add your control notification handler code here
	CString cpname,filein,fileout,pwd("11111111");
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_CRYPT,cpname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	if(!Crypt(cpname.GetBuffer(0),filein.GetBuffer(0),fileout.GetBuffer(0),
			pwd.GetBuffer(0),1,outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("加密文件成功");		
}

void CUsbEvpPage::OnBdec() //对称解密
{
	// TODO: Add your control notification handler code here
	CString cpname,filein,fileout,pwd("11111111");
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_CRYPT,cpname);
	m_Progress.SetPos(0);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	if(!Crypt(cpname.GetBuffer(0),filein.GetBuffer(0),fileout.GetBuffer(0),
			pwd.GetBuffer(0),0,outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("解密文件成功");
	
}


void CUsbEvpPage::OnBseal() //数字信封
{
	// TODO: Add your control notification handler code here
	CString cpname,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_CRYPT,cpname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
	/*得到公钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);

	if(!Seal(lpCert,lenCert,cpname.GetBuffer(0),filein.GetBuffer(0),
			fileout.GetBuffer(0),outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("封装文件成功");
}

void CUsbEvpPage::OnBopenseal() //打开数字信封
{
	// TODO: Add your control notification handler code here
	CString cpname,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_CRYPT,cpname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
	/*私钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);

	if(!OpenSeal(lpKey,lenKey,cpname.GetBuffer(0),filein.GetBuffer(0),
			fileout.GetBuffer(0),outMsg,DrawProg))
		m_List.AddMsg(outMsg,M_ERROR);
	else
		m_List.AddMsg("拆封文件成功");
	
}

void CUsbEvpPage::OnBdigest() //信息摘要
{
	// TODO: Add your control notification handler code here
	CString mdname,filein;
	char outMsg[100]="";
	unsigned char md_value[MAX_MD_SIZE]="";
	char buf[MAX_MD_SIZE*2]="";
	unsigned int md_len;
	GetDlgItemText(IDC_COMBO_DIGEST,mdname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	m_Progress.SetPos(0);

	if(!Digest(mdname.GetBuffer(0),filein.GetBuffer(0),md_value,&md_len, outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	for(unsigned i=0;i<md_len;i++)
	{
		sprintf((char *)&buf[i*2],"%02x",md_value[i]);//02x标示1个16进制变为2个字符，空补零
	}
	SetDlgItemText(IDC_EDIT_DIGEST,(char *)buf);
}

void CUsbEvpPage::OnBsign() //数字签名
{
	// TODO: Add your control notification handler code here
	CString mdname,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_DIGEST,mdname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);

	/*私钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);

	if(!Sign(lpKey,lenKey,mdname.GetBuffer(0),filein.GetBuffer(0),
		fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("数字签名成功");
}

void CUsbEvpPage::OnBvsign()// 签名验证
{
	// TODO: Add your control notification handler code here
	CString mdname,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_COMBO_DIGEST,mdname);
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
  	/*得到公钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);

	if(!VerifySign(lpCert,lenCert,mdname.GetBuffer(0),filein.GetBuffer(0),
		fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("验证签名成功");
	
}

void CUsbEvpPage::OnBrsacert() //公钥加密
{
	// TODO: Add your control notification handler code here
	CString cert,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
	/*得到公钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);

	if(!RSAEnc(lpCert,lenCert,filein.GetBuffer(0),fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("加密成功");
}

void CUsbEvpPage::OnBrsakey() //私钥解密
{
	// TODO: Add your control notification handler code here
	CString key,filein,fileout;
	char outMsg[100]="";
	GetDlgItemText(IDC_EDIT_INFILE,filein);
	GetDlgItemText(IDC_EDIT_OUTFILE,fileout);
	m_Progress.SetPos(0);
	/*根私钥*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);
	if(!RSADec(lpKey,lenKey,filein.GetBuffer(0), 
		  fileout.GetBuffer(0),outMsg,DrawProg))
	{
		m_List.AddMsg(outMsg,M_ERROR);
		return;
	}
	m_List.AddMsg("解密成功");
}
void CUsbEvpPage::DrawProg(int i)
{
	((CUsbEvpPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(8))->
		m_Progress.SetPos(i);
}
