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

/*void CUsbCertPage::OnBPri() //ѡ��˽Կ
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"˽Կ֤���ļ�(*.crt;*.cer)|*.crt;*.cer|�����ļ�(*.*)|*.*||",NULL  );
	dlgOpen.m_ofn.lpstrTitle="ѡ��˽Կ֤��";//������
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
	//��˽Կ�ļ����˽Կ
	UCHAR	certbuff[3000];
	asn__data *kk=(asn__data*)(new char[sizeof(asn__data)]);//˽Կ
	CFile f(m_PriKey,CFile::modeRead);
	kk->length=f.Read(certbuff,3000);
	kk->value=(UCHAR*)certbuff;
	f.Close();	
	//��˽Կ�������ɽ���˽Կ�ĶԳ���Կ
    UCHAR Dec_key[32]={0};
	UINT4 Dec_keylen=32;       
	if(RTN_OK!=CreateKeyFromPassword(ATTRIB_SDBI_KEY,(UCHAR *)m_Password.GetBuffer(32),
		m_Password.GetLength(),Dec_key,&Dec_keylen))
	{
		m_List.AddMsg("���ɽ�����Կʧ�ܡ�",M_ERROR);
		delete kk;
		return;
	}
	//�öԳ���Կ����˽Կ
	UCHAR data[1024]={0};         //���ܺ��˽Կ�ļ�
	UINT4 datalen=1024;	         //���ܺ��˽Կ�ļ�����
	if(RTN_OK!=CryptionProc(ATTRIB_SDBI_KEY,Dec_key,Dec_keylen,DECRYPT,kk->value,kk->length,data,&datalen))
	{
		m_List.AddMsg("����˽Կʧ��",M_ERROR);
		delete kk;
		return;
	}

    UCHAR Enc_key[32]={0};
	UINT4 Enc_keylen=32;       
	//���ɼ�����Ҫ
	if(RTN_OK!=CreateKeyFromPassword(ATTRIB_SDBI_KEY,(UCHAR *)m_Newword.GetBuffer(32),
		m_Newword.GetLength(),Enc_key,&Enc_keylen))
	{
		m_List.AddMsg("���ɼ�����Կʧ�ܡ�",M_ERROR);
		delete kk;
		return;
	}

	//�öԳ���Կ����˽Կ
	UCHAR outbuf[1024];             //���ܺ��˽Կ�ļ�
	UINT4 outlen=1024;	         //���ܺ��˽Կ�ļ�����
	if(RTN_OK!=CryptionProc(ATTRIB_SDBI_KEY,Enc_key,Enc_keylen,ENCRYPT,data,datalen,outbuf,&outlen))
	{
		m_List.AddMsg("����˽Կʧ��",M_ERROR);
		delete kk;
		return;
	}
	else
	{
		f.Open(m_PriKey,CFile::modeCreate|CFile::modeWrite);
		f.Write(outbuf,outlen);
		f.Close();	
		m_List.AddMsg("�޸�˽Կ����ɹ�");
	}
	//��˽Կ���ܿ���
	delete kk;

}
*/
void CUsbCertPage::OnBPath() //�������·�������·�������ļ��򸲸�
{
	// TODO: Add your control notification handler code here
	LPITEMIDLIST pidlRoot=NULL; 
	SHGetSpecialFolderLocation(m_hWnd,CSIDL_DRIVES ,&pidlRoot); 
	BROWSEINFO bi;   //���봫��Ĳ���,�����������ṹ�Ĳ����ĳ�ʼ�� 
	CString strDisplayName;   //�����õ�,��ѡ��Ļ�ҳ��·��,�൱���ṩһ�������� 
	bi.hwndOwner=GetSafeHwnd();   //�õ�������Handleֵ 
	bi.pidlRoot=0;   //���������������������õ���. 
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   //�õ�������ָ��, 
	bi.lpszTitle="ѡ���ļ����·��,·�������е��ļ���������!!";   //���ñ��� 
	bi.ulFlags=BIF_RETURNONLYFSDIRS    ;   //���ñ�־ 
	bi.lpfn=NULL; 
	bi.lParam=0; 
	bi.iImage=0;   //���������һЩ�޹صĲ���������,�����������, 
	ITEMIDLIST * pidl;  
	pidl=SHBrowseForFolder(&bi);   //�򿪶Ի��� 
	if(!pidl)
		return;
	SHGetPathFromIDList(pidl,bi.pszDisplayName);	
	strDisplayName.ReleaseBuffer();   //�������GetBuffer()���Ӧ 
	m_Path=strDisplayName;
	SetDlgItemText(IDC_EDIT_PATH,m_Path);	
}

void CUsbCertPage::OnBPub() //ѡ��Կ��ѡ��p12
{
	// TODO: Add your control notification handler code here
	if(m_Type==1)//ѡ��Կ
	{
		CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"��Կ֤���ļ�(*.crt;*.cer)|*.crt;*.cer|�����ļ�(*.*)|*.*||",NULL);
		dlgOpen.m_ofn.lpstrTitle="ѡ��Կ֤���ļ�";//������
		if(dlgOpen.DoModal()!=IDOK) return;
		m_cert=dlgOpen.GetPathName();
		SetDlgItemText(IDC_EDIT_P12,m_cert);
		
	}
	else//ѡ��p12
	{
		CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
			"������Ϣ����(*.db;*.pfx;*.p12)|*.db;*.pfx;*.p12|�����ļ�(*.*)|*.*||",NULL);
		dlgOpen.m_ofn.lpstrTitle="ѡ�������Ϣ�����ļ�";//������
		if(dlgOpen.DoModal()!=IDOK) return;
		m_p12=dlgOpen.GetPathName();
		SetDlgItemText(IDC_EDIT_P12,m_p12);
	
	}
}

void CUsbCertPage::OnBKey() //ѡ��˽Կ
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"˽Կ֤���ļ�(*.crt;*.cer)|*.crt;*.cer|�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="ѡ��˽Կ֤���ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	m_key=dlgOpen.GetPathName();
	SetDlgItemText(IDC_EDIT_KEY,m_key);
	
}

void CUsbCertPage::OnBOk() //ִ�в���
{
	// TODO: Add your control notification handler code here
	if(m_Type!=2&&m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}
	
	if(m_Type==0)//��ȡ֤�����
	{
		//��ȡp12�ļ�
		CString pwd,pwd2;
		GetDlgItemText(IDC_EDIT_PASSWORD,pwd);
	/*if(pwd=="")
		{
			m_List.AddMsg("��������ܿ���!",M_WARING);
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
			m_List.AddMsg("�ֽ�P12�ļ������ɹ�");	
	}

	else if(m_Type==1)//�ϲ�֤�����
	{
		CString fileout;
		fileout=m_Path+"\\Pkcs12.pfx";
		CString pwd,pwd2;
		GetDlgItemText(IDC_EDIT_PASSWORD2,pwd2);
		//	if(pwd2=="")
		//	{
		//		m_List.AddMsg("��������ܿ���!",M_WARING);
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
	else//�޸�����
	{
		CString pwd,pwd2,fileOut;
		GetDlgItemText(IDC_EDIT_PASSWORD,pwd);
/*		if(pwd=="")
		{
			m_List.AddMsg("��������ܿ���!",M_WARING);
			return;
		}

*/		GetDlgItemText(IDC_EDIT_PASSWORD2,pwd2);
/*		if(pwd2=="")
		{
			m_List.AddMsg("��������ܿ���!",M_WARING);
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
		SetDlgItemText(IDC_B_PUB,"ѡ��P12");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(0);
		GetDlgItem(IDC_B_KEY)->EnableWindow(0);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}
	else if(m_Type==1)
	{
		GetDlgItem(IDC_EDIT_P12)->EnableWindow(1);
		SetDlgItemText(IDC_B_PUB,"ѡ��Կ");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(1);
		GetDlgItem(IDC_B_KEY)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}
	else
	{
		GetDlgItem(IDC_EDIT_P12)->EnableWindow(1);
		SetDlgItemText(IDC_B_PUB,"ѡ��P12");
		GetDlgItem(IDC_B_PUB)->EnableWindow(1);	
		GetDlgItem(IDC_EDIT_PASSWORD)->EnableWindow(1);	
		
		GetDlgItem(IDC_EDIT_KEY)->EnableWindow(0);
		GetDlgItem(IDC_B_KEY)->EnableWindow(0);	
		GetDlgItem(IDC_EDIT_PASSWORD2)->EnableWindow(1);	
		
	}

}

void CUsbCertPage::OnRParse() //��ȡ֤�����
{
	// TODO: Add your control notification handler code here
	m_Type=0;
	SetCheck();
	
}

void CUsbCertPage::OnRCreate() //�ϲ�֤�����
{
	// TODO: Add your control notification handler code here
	m_Type=1;
	SetCheck();
	
}

void CUsbCertPage::OnRChangep() //�޸��������
{
	// TODO: Add your control notification handler code here
	m_Type=2;
	SetCheck();
}



void CUsbCertPage::OnBsout() //ѡ�������ļ�
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"֤���ļ�(*.crt;*.cer;*.pem;*.der;*.p12;*.pfx)|*.crt;*.cer;*.pem;*.der;*.p12;*.pfx|�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="ѡ��֤���ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_INFILE,dlgOpen.GetPathName());
}

void CUsbCertPage::OnBsin() //ѡ������ļ�
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"֤���ļ�(*.crt;*.cer;*.pem;*.der;*.p12;*.pfx)|*.crt;*.cer;*.pem;*.der;*.p12;*.pfx|�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="����֤���ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_OUTFILE,dlgOpen.GetPathName());
	
}

void CUsbCertPage::OnBptod() //PEM-->DER 
{
	// TODO: Add your control notification handler code here
	char out[100]={0};
	//��������ļ�������ļ�
	CString infile,outfile;
	GetDlgItemText(IDC_EDIT_INFILE,infile);
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(infile=="")
	{
		m_List.AddMsg("û��ѡ�������ļ�",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("û��ָ������ļ�",M_WARING);
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
		m_List.AddMsg("û��ѡ�������ļ�",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("û��ָ������ļ�",M_WARING);
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
		m_List.AddMsg("û��ѡ��Կ�ļ�",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_OUTFILE,outfile);
	if(outfile=="")
	{
		m_List.AddMsg("û��ѡ��˽Կ�ļ�",M_WARING);
		return;
	}

	if(CertPairCheck(infile.GetBuffer(0),outfile.GetBuffer(0),out))
		m_List.AddMsg("��˽Կ��ƥ��");
	else
	{
		m_List.AddMsg(out,M_ERROR);
	}
//	GeneratePair(out);
}
