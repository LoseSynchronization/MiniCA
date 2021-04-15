// UsbCertPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbCertPage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "..\ca.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbCertPage property page

IMPLEMENT_DYNCREATE(CUsbCertPage, CPropertyPage)

CUsbCertPage::CUsbCertPage() : CPropertyPage(CUsbCertPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbCertPage)
	m_Type = 0;
	//}}AFX_DATA_INIT
}

CUsbCertPage::~CUsbCertPage()
{
}

void CUsbCertPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbCertPage)
	DDX_Control(pDX, IDC_LIST_CERT, m_List);
	DDX_Radio(pDX, IDC_R_PARSE, m_Type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbCertPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbCertPage)
	ON_BN_CLICKED(IDC_BPTOD, OnBptod)
	ON_BN_CLICKED(IDC_B_PATH, OnBPath)
	ON_BN_CLICKED(IDC_B_PUB, OnBPub)
	ON_BN_CLICKED(IDC_B_KEY, OnBKey)
	ON_BN_CLICKED(IDC_B_OK, OnBOk)
	ON_BN_CLICKED(IDC_R_PARSE, OnRParse)
	ON_BN_CLICKED(IDC_R_CREATE, OnRCreate)
	ON_BN_CLICKED(IDC_R_CHANGEP, OnRChangep)
	ON_BN_CLICKED(IDC_BDTOP, OnBdtop)
	ON_BN_CLICKED(IDC_BSOUT, OnBsout)
	ON_BN_CLICKED(IDC_BSIN, OnBsin)
	ON_BN_CLICKED(IDC_B_CHECK, OnBCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbCertPage message handlers
BOOL CUsbCertPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	SetCheck();
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*void CUsbCertPage::OnBPri() //选择私钥
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"私钥证书文件(*.crt;*.cer)|*.crt;*.cer|所有文件(*.*)|*.*||",NULL  );
	dlgOpen.m_ofn.lpstrTitle="选择私钥证书";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	m_PriKey=dlgOpen.GetPathName();
	SetDlgItemText(IDC_EDIT_PRI,m_PriKey);
}

void CUsbCertPage::OnBChange() 
{
	// TODO: Add your control notification handler code here
	CString msg,m_Password,m_Newword;
	GetDlgItemText(IDC_EDIT_OLD,m_Password);
	GetDlgItemText(IDC_EDIT_NEW,m_Newword);
	//从私钥文件获得私钥
	UCHAR	certbuff[3000];
	asn__data *kk=(asn__data*)(new char[sizeof(asn__data)]);//私钥
	CFile f(m_PriKey,CFile::modeRead);
	kk->length=f.Read(certbuff,3000);
	kk->value=(UCHAR*)certbuff;
	f.Close();	
	//用私钥口令生成解密私钥的对称密钥
    UCHAR Dec_key[32]={0};
	UINT4 Dec_keylen=32;       
	if(RTN_OK!=CreateKeyFromPassword(ATTRIB_SDBI_KEY,(UCHAR *)m_Password.GetBuffer(32),
		m_Password.GetLength(),Dec_key,&Dec_keylen))
	{
		m_List.AddMsg("生成解密密钥失败。",M_ERROR);
		delete kk;
		return;
	}
	//用对称密钥解密私钥
	UCHAR data[1024]={0};         //解密后的私钥文件
	UINT4 datalen=1024;	         //解密后的私钥文件长度
	if(RTN_OK!=CryptionProc(ATTRIB_SDBI_KEY,Dec_key,Dec_keylen,DECRYPT,kk->value,kk->length,data,&datalen))
	{
		m_List.AddMsg("解密私钥失败",M_ERROR);
		delete kk;
		return;
	}

    UCHAR Enc_key[32]={0};
	UINT4 Enc_keylen=32;       
	//生成加密密要
	if(RTN_OK!=CreateKeyFromPassword(ATTRIB_SDBI_KEY,(UCHAR *)m_Newword.GetBuffer(32),
		m_Newword.GetLength(),Enc_key,&Enc_keylen))
	{
		m_List.AddMsg("生成加密密钥失败。",M_ERROR);
		delete kk;
		return;
	}

	//用对称密钥加密私钥
	UCHAR outbuf[1024];             //加密后的私钥文件
	UINT4 outlen=1024;	         //加密后的私钥文件长度
	if(RTN_OK!=CryptionProc(ATTRIB_SDBI_KEY,Enc_key,Enc_keylen,ENCRYPT,data,datalen,outbuf,&outlen))
	{
		m_List.AddMsg("加密私钥失败",M_ERROR);
		delete kk;
		return;
	}
	else
	{
		f.Open(m_PriKey,CFile::modeCreate|CFile::modeWrite);
		f.Write(outbuf,outlen);
		f.Close();	
		m_List.AddMsg("修改私钥密码成功");
	}
	//用私钥解密口令
	delete kk;

}
*/
void CUsbCertPage::OnBPath() //设置输出路径，如果路径下有文件则覆盖
{
	// TODO: Add your control notification handler code here
	LPITEMIDLIST pidlRoot=NULL; 
	SHGetSpecialFolderLocation(m_hWnd,CSIDL_DRIVES ,&pidlRoot); 
	BROWSEINFO bi;   //必须传入的参数,下面就是这个结构的参数的初始化 
	CString strDisplayName;   //用来得到,你选择的活页夹路径,相当于提供一个缓冲区 
	bi.hwndOwner=GetSafeHwnd();   //得到父窗口Handle值 
	bi.pidlRoot=0;   //这个变量就是我们在上面得到的. 
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   //得到缓冲区指针, 
	bi.lpszTitle="选择文件输出路径,路径下已有的文件将被覆盖!!";   //设置标题 
	bi.ulFlags=BIF_RETURNONLYFSDIRS    ;   //设置标志 
	bi.lpfn=NULL; 
	bi.lParam=0; 
	bi.iImage=0;   //上面这个是一些无关的参数的设置,最好设置起来, 
	ITEMIDLIST * pidl;  
	pidl=SHBrowseForFolder(&bi);   //打开对话框 
	if(!pidl)
		return;
	SHGetPathFromIDList(pidl,bi.pszDisplayName);	
	strDisplayName.ReleaseBuffer();   //和上面的GetBuffer()相对应 
	m_Path=strDisplayName;
	SetDlgItemText(IDC_EDIT_PATH,m_Path);	
}

void CUsbCertPage::OnBPub() //选择公钥，选择p12
{
	// TODO: Add your control notification handler code here
	if(m_Type==1)//选择共钥
	{
		CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"公钥证书文件(*.crt;*.cer)|*.crt;*.cer|所有文件(*.*)|*.*||",NULL);
		dlgOpen.m_ofn.lpstrTitle="选择公钥证书文件";//标题条
		if(dlgOpen.DoModal()!=IDOK) return;
		m_cert=dlgOpen.GetPathName();
		SetDlgItemText(IDC_EDIT_P12,m_cert);
		
	}
	else//选择p12
	{
		CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"个人信息交换(*.db;*.pfx;*.p12)|*.db;*.pfx;*.p12|所有文件(*.*)|*.*||",NULL);
		dlgOpen.m_ofn.lpstrTitle="选择个人信息交换文件";//标题条
		if(dlgOpen.DoModal()!=IDOK) return;
		m_p12=dlgOpen.GetPathName();
		SetDlgItemText(IDC_EDIT_P12,m_p12);
	
	}
}

void CUsbCertPage::OnBKey() //选择私钥
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"私钥证书文件(*.crt;*.cer)|*.crt;*.cer|所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择私钥证书文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	m_key=dlgOpen.GetPathName();
	SetDlgItemText(IDC_EDIT_KEY,m_key);
	
}

void CUsbCertPage::OnBOk() //执行操作
{
	// TODO: Add your control notification handler code here
	if(m_Type!=2&&m_Path=="") 
	{
		m_List.AddMsg("请选择输出路径!",M_WARING);
		return;
	}
	
	if(m_Type==0)//提取证书操作
	{
		//读取p12文件
		CString pwd,pwd2;
		GetDlgItemText(IDC_EDIT_PASSWORD,pwd);
	/*if(pwd=="")
		{
			m_List.AddMsg("请给出解密口令!",M_WARING);
			return;
		}
	*/	
		CString filein,certout,keyout;
		certout=m_Path+"\\UserCert.crt";
		keyout=m_Path+"\\UserPriKey.crt";	
		GetDlgItemText(IDC_EDIT_PASSWORD2,pwd2);

		char out[100]={0};
		if(!ParseDB(m_p12.GetBuffer(0),pwd.GetBuffer(0),certout.GetBuffer(0),keyout.GetBuffer(0),PEM,out))
			m_List.AddMsg(out,M_ERROR);

		else//ok
			m_List.AddMsg("分解P12文件操作成功");	
	}

	else if(m_Type==1)//合并证书操作
	{
		CString fileout;
		fileout=m_Path+"\\Pkcs12.pfx";
		CString pwd,pwd2;
		GetDlgItemText(IDC_EDIT_PASSWORD2,pwd2);
		//	if(pwd2=="")
		//	{
		//		m_List.AddMsg("请给出加密口令!",M_WARING);
		//		return;
		//	}
		GetDlgItemText(IDC_EDIT_PASSWORD,pwd);
		
		char out[100]={0};
		if(CreateDB(fileout.GetBuffer(0),pwd2.GetBuffer(0),m_cert.GetBuffer(0),
			m_key.GetBuffer(0),out))
			m_List.AddMsg(out);
		else
			m_List.AddMsg(out,M_ERROR);
	}
	else//修改密码
	{
		CString pwd,pwd2,fileOut;
		GetDlgItemText(IDC_EDIT_PASSWORD,pwd);
/*		if(pwd=="")
		{
			m_List.AddMsg("请给出解密口令!",M_WARING);
			return;
		}

*/		GetDlgItemText(IDC_EDIT_PASSWORD2,pwd2);
/*		if(pwd2=="")
		{
			m_List.AddMsg("请给出加密口令!",M_WARING);
			return;
		}

*/		char out[100]={0};
		if(ChangePB(m_p12.GetBuffer(0),pwd.GetBuffer(0),pwd2.GetBuffer(0),m_p12.GetBuffer(0),out))
			m_List.AddMsg(out);
		else
			m_List.AddMsg(out,M_ERROR);

	}
}

void CUsbCertPage::SetCheck()
{
	SetDlgItemText(IDC_EDIT_P12,"");
	SetDlgItemText(IDC_EDIT_PASSWORD,"");
	SetDlgItemText(IDC_EDIT_KEY,"");
	SetDlgItemText(IDC_EDIT_PASSWORD2,"");
	
	if(m_Type==0)
	{
		
		GetDlgItem(IDC_EDIT_P12)->EnableWindow(1);
		SetDlgItemText(IDC_B_PUB,"选择P12");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(0);
		GetDlgItem(IDC_B_KEY)->EnableWindow(0);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}
	else if(m_Type==1)
	{
		GetDlgItem(IDC_EDIT_P12)->EnableWindow(1);
		SetDlgItemText(IDC_B_PUB,"选择公钥");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(1);
		GetDlgItem(IDC_B_KEY)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}
	else
	{
		GetDlgItem(IDC_EDIT_P12)->EnableWindow(1);
		SetDlgItemText(IDC_B_PUB,"选择P12");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(0);
		GetDlgItem(IDC_B_KEY)->EnableWindow(0);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}

}

void CUsbCertPage::OnRParse() //提取证书操作
{
	// TODO: Add your control notification handler code here
	m_Type=0;
	SetCheck();
	
}

void CUsbCertPage::OnRCreate() //合并证书操作
{
	// TODO: Add your control notification handler code here
	m_Type=1;
	SetCheck();
	
}

void CUsbCertPage::OnRChangep() //修改密码操作
{
	// TODO: Add your control notification handler code here
	m_Type=2;
	SetCheck();
}



void CUsbCertPage::OnBsout() //选择输入文件
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"证书文件(*.crt;*.cer;*.pem;*.der;*.p12;*.pfx)|*.crt;*.cer;*.pem;*.der;*.p12;*.pfx|所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="选择证书文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_INFILE,dlgOpen.GetPathName());
}

void CUsbCertPage::OnBsin() //选择输出文件
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"证书文件(*.crt;*.cer;*.pem;*.der;*.p12;*.pfx)|*.crt;*.cer;*.pem;*.der;*.p12;*.pfx|所有文件(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="保存证书文件";//标题条
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_OUTFILE,dlgOpen.GetPathName());
	
}

void CUsbCertPage::OnBptod() //PEM-->DER 
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	//获得输入文件和输出文件
	CString infile,outfile;
	GetDlgItemText(IDC_EDIT_INFILE,infile);
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(infile=="")
	{
		m_List.AddMsg("没有选择输入文件",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("没有指定输出文件",M_WARING);
		return;
	}
	
	if(CertFormatConver(infile.GetBuffer(0),0,NULL,outfile.GetBuffer(0),DER,out))
		m_List.AddMsg(out);
	else
		m_List.AddMsg(out,M_ERROR);

}


void CUsbCertPage::OnBdtop() //DER-->PEM
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	CString infile,outfile;
	GetDlgItemText(IDC_EDIT_INFILE,infile);
	if(infile=="")
	{
		m_List.AddMsg("没有选择输入文件",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("没有指定输出文件",M_WARING);
		return;
	}

	if(CertFormatConver(infile.GetBuffer(0),0,NULL,outfile.GetBuffer(0),PEM,out))
		m_List.AddMsg(out);
	else
		m_List.AddMsg(out,M_ERROR);
}


void CUsbCertPage::OnBCheck() 
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	CString infile,outfile;
	GetDlgItemText(IDC_EDIT_INFILE,infile);
	if(infile=="")
	{
		m_List.AddMsg("没有选择公钥文件",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("没有选择私钥文件",M_WARING);
		return;
	}

	if(CertPairCheck(infile.GetBuffer(0),outfile.GetBuffer(0),out))
		m_List.AddMsg("公私钥对匹配");
	else
	{
		m_List.AddMsg(out,M_ERROR);
	}
//	GeneratePair(out);
}
