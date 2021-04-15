// UsbCaPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbCaPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include "..\ca.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbCaPage property page

IMPLEMENT_DYNCREATE(CUsbCaPage, CPropertyPage)

CUsbCaPage::CUsbCaPage() : CPropertyPage(CUsbCaPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbCaPage)
	//}}AFX_DATA_INIT
	m_CertFormat=PEM;
}

CUsbCaPage::~CUsbCaPage()
{
}

void CUsbCaPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbCaPage)
	DDX_Control(pDX, IDC_LIST_CA, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbCaPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbCaPage)
	ON_BN_CLICKED(IDC_B_PATH, OnBPath)
	ON_BN_CLICKED(IDC_B_PATH4, OnBPath4)
	ON_BN_CLICKED(IDC_B_CRL, OnBCrl)
	ON_BN_CLICKED(IDC_B_MKROOT, OnBMkroot)
	ON_BN_CLICKED(IDC_B_MKREQ, OnBMkreq)
	ON_BN_CLICKED(IDC_B_MKCERT, OnBMkcert)
	ON_BN_CLICKED(IDC_CHECK, OnCheck)
	ON_BN_CLICKED(IDC_B_MKCERT2, OnBMkcert2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbCaPage message handlers
BOOL CUsbCaPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetDlgItemText(IDC_EDIT_C,"�й�");
	SetDlgItemText(IDC_EDIT_ST,"�ӱ�");
	SetDlgItemText(IDC_EDIT_L,"ʯ��ׯ");
	SetDlgItemText(IDC_EDIT_O,"��λ����");
	SetDlgItemText(IDC_EDIT_OU,"��������");
	SetDlgItemText(IDC_COMBO_L,"1024");
	SetDlgItemText(IDC_EDIT_DAY,"365");
	SetDlgItemText(IDC_EDIT_SN,"100");
	SetDlgItemText(IDC_EDIT_CN,"��������");
	SetDlgItemText(IDC_EDIT_E,"hpxs@hotmail.com");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbCaPage::OnBPath() //�������·�������·�������ļ��򸲸�
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

void CUsbCaPage::OnBMkroot() //������֤��
{
	// TODO: Add your control notification handler code here
	if(m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}
	char out[100]={0};
	stuSUBJECT root;
	CString str,strSN;
	GetDlgItemText(IDC_EDIT_C,str);
	strncpy((char *)root.C,str,sizeof(root.C));
	GetDlgItemText(IDC_EDIT_ST,str);
	strncpy((char *)root.ST,str,sizeof(root.ST));
	GetDlgItemText(IDC_EDIT_L,str);
	strncpy((char *)root.L,str,sizeof(root.L));
	GetDlgItemText(IDC_EDIT_O,str);
	strncpy((char *)root.O,str,sizeof(root.O));
	GetDlgItemText(IDC_EDIT_OU,str);
	strncpy((char *)root.OU,str,sizeof(root.OU));
	GetDlgItemText(IDC_EDIT_CN,str);
	strncpy((char *)root.CN,str,sizeof(root.CN));
	GetDlgItemText(IDC_EDIT_E,str);
	strncpy((char *)root.MAIL,str,sizeof(root.MAIL));

/*	strncpy((char *)root.PMAIL,str,sizeof(root.PMAIL));
	strncpy((char *)root.T,"T",sizeof(root.T));
	strncpy((char *)root.D,"D",sizeof(root.D));
	strncpy((char *)root.G,"G",sizeof(root.G));
	strncpy((char *)root.I,"I",sizeof(root.I));
	strncpy((char *)root.NAME,"NAME",sizeof(root.NAME));
	strncpy((char *)root.S,"S",sizeof(root.S));
	strncpy((char *)root.QUAL,"QUAL",sizeof(root.QUAL));
	strncpy((char *)root.STN,"STN",sizeof(root.STN));
	strncpy((char *)root.PW,"PW",sizeof(root.PW));
	strncpy((char *)root.ADD,"ADD",sizeof(root.ADD));
*/

	GetDlgItemText(IDC_EDIT_DAY,str);
	if(str=="")
	{
		m_List.AddMsg("�������Ч��!",M_WARING);
		return;
	}

	GetDlgItemText(IDC_EDIT_SN,strSN);
	CString cert=m_Path+"\\RootCert.crt";
	CString key=m_Path+"\\RootKey.crt";
	if(MakeRoot(&root,1024,atoi(strSN),atoi(str),cert.GetBuffer(0),key.GetBuffer(0),out,m_CertFormat))
		m_List.AddMsg("��֤�������ɹ�");
	else
		m_List.AddMsg(out,M_ERROR);	
}

void CUsbCaPage::OnBMkreq() 
{
	// TODO: Add your control notification handler code here
	if(m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}
	
	char out[100]="";
	stuSUBJECT req;
	CString str;
	GetDlgItemText(IDC_EDIT_C,str);
	strncpy((char *)req.C,str,sizeof(req.C));
	GetDlgItemText(IDC_EDIT_ST,str);
	strncpy((char *)req.ST,str,sizeof(req.ST));
	GetDlgItemText(IDC_EDIT_L,str);
	strncpy((char *)req.L,str,sizeof(req.L));
	GetDlgItemText(IDC_EDIT_O,str);
	strncpy((char *)req.O,str,sizeof(req.O));
	GetDlgItemText(IDC_EDIT_OU,str);
	strncpy((char *)req.OU,str,sizeof(req.OU));
	GetDlgItemText(IDC_EDIT_CN,str);
	strncpy((char *)req.CN,str,sizeof(req.CN));
	GetDlgItemText(IDC_EDIT_E,str);
	strncpy((char *)req.MAIL,str,sizeof(req.MAIL));
	
	GetDlgItemText(IDC_EDIT_DAY,str);
	if(str=="")
	{
		m_List.AddMsg("�������Ч��!",M_WARING);
		return;
	}
	CString reqf=m_Path+"\\Req.txt";
	CString key=m_Path+"\\UserKey.crt";
	
	if(MakeReq(&req,1024,reqf.GetBuffer(0),key.GetBuffer(0),out,m_CertFormat))
	{
		SetDlgItemText(IDC_EDIT4,reqf);
		m_List.AddMsg("Req�����ɹ�");
	}
	else
		m_List.AddMsg(out,M_ERROR);		
}


void CUsbCaPage::OnBMkcert() 
{
	// TODO: Add your control notification handler code here
	if(m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}

	CString req,day,outCert,strSN;
	GetDlgItemText(IDC_EDIT4,req);
	if(req=="")
	{
		m_List.AddMsg("��ѡ��֤�������ļ�!",M_WARING);
		return;
	}
	GetDlgItemText(IDC_EDIT_DAY,day);
	if(day=="")
	{
		m_List.AddMsg("�������Ч��!",M_WARING);
		return;
	}
	char out[1024]={0};
	stuKEYUSAGE KUSAGE;
	memset(&KUSAGE,1,sizeof(stuKEYUSAGE));
	KUSAGE.CS=FALSE;
	stuEKEYUSAGE EKUSAGE;
	memset(&EKUSAGE,0,sizeof(stuEKEYUSAGE));
	EKUSAGE.CA=TRUE;

	/*�õ�����Կ*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*��˽Կ*/
	hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);
	
	GetDlgItemText(IDC_EDIT_SN,strSN);

	outCert=m_Path+"\\UserCert.crt";
	
	if(MakeCert(lpCert,lenCert,lpKey,lenKey,atoi(strSN),0,
		atoi(day),req.GetBuffer(0),&KUSAGE,&EKUSAGE,outCert.GetBuffer(0),out,m_CertFormat))
		m_List.AddMsg("֤�������ɹ�");
	else
		m_List.AddMsg(out,M_ERROR);
}
void CUsbCaPage::OnBMkcert2() //ֱ������֤��
{
	// TODO: Add your control notification handler code here
	char out[1024]={0};
	char cert[2048]={0},key[1024]={0};
	int certl=0,keyl=0;
	CString day,strSN;
	stuCERT sCERT;
	CString str;
	GetDlgItemText(IDC_EDIT_C,str);
	strncpy((char *)sCERT.SUBJECT.C,str,sizeof(sCERT.SUBJECT.C));
	GetDlgItemText(IDC_EDIT_ST,str);
	strncpy((char *)sCERT.SUBJECT.ST,str,sizeof(sCERT.SUBJECT.ST));
	GetDlgItemText(IDC_EDIT_L,str);
	strncpy((char *)sCERT.SUBJECT.L,str,sizeof(sCERT.SUBJECT.L));
	GetDlgItemText(IDC_EDIT_O,str);
	strncpy((char *)sCERT.SUBJECT.O,str,sizeof(sCERT.SUBJECT.O));
	GetDlgItemText(IDC_EDIT_OU,str);
	strncpy((char *)sCERT.SUBJECT.OU,str,sizeof(sCERT.SUBJECT.OU));
	GetDlgItemText(IDC_EDIT_CN,str);
	strncpy((char *)sCERT.SUBJECT.CN,str,sizeof(sCERT.SUBJECT.CN));
	GetDlgItemText(IDC_EDIT_E,str);
	strncpy((char *)sCERT.SUBJECT.MAIL,str,sizeof(sCERT.SUBJECT.MAIL));
	GetDlgItemText(IDC_EDIT_DAY,day);

	if(m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}

	if(day=="")
	{
		m_List.AddMsg("�������Ч��!",M_WARING);
		return;
	}

	/*�õ�����Կ*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*��˽Կ*/
	hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);
	
	GetDlgItemText(IDC_EDIT_SN,strSN);
	
	if(DirectCert(lpCert,lenCert,lpKey,lenKey,atoi(strSN),0,atoi(day),&sCERT,1024,
		cert,&certl,key,&keyl,out/*,m_CertFormat*/))
	{
		CString outCert=m_Path+"\\UserCert.pem";
		CString outKey=m_Path+"\\UserKey.pem";
		FILE * pfc=fopen(outCert,"w");
		fwrite(cert,sizeof(char),certl,pfc);
		fclose(pfc);
		pfc=fopen(outKey,"w");
		fwrite(key,sizeof(char),keyl,pfc);
		fclose(pfc);
		m_List.AddMsg("����֤��ɹ�");
	}
	else
		m_List.AddMsg("����֤��ʧ��",M_ERROR);

}

void CUsbCaPage::OnBPath4() //req�ļ�
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"֤������(*.txt)|*.txt|�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="ѡ��֤�������ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	CString key=dlgOpen.GetPathName();
	SetDlgItemText(IDC_EDIT4,key);
	
}

void CUsbCaPage::OnBCrl() 
{
	// TODO: Add your control notification handler code here
	if(m_Path=="") 
	{
		m_List.AddMsg("��ѡ�����·��!",M_WARING);
		return;
	}

	char out[100]={0};
	CString outCrl=m_Path+"\\HpxsCrl.crl";
	/*�õ�����Կ*/
	HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
	DWORD lenCert = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgCert=LoadResource(NULL,hRsrc);
	LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
	/*��˽Կ*/
	hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
	DWORD lenKey = SizeofResource(NULL, hRsrc); 
	HGLOBAL hgKey=LoadResource(NULL,hRsrc);
	LPSTR lpKey=(LPSTR)LockResource(hgKey);
	
	time_t t;
	time(&t);
	char * Crl=NULL;
	stuREVOKE * Head=NULL;//���������
	AddRevoke(Head,1,t);//���ӱ���
	AddRevoke(Head,2,t);
	AddRevoke(Head,3,t);

	if(MakeCrl(lpCert,lenCert,lpKey,lenKey,Head,NULL,Crl,NULL,outCrl.GetBuffer(0),out))
		m_List.AddMsg(out);
	else
		m_List.AddMsg(out,M_ERROR);

}

void CUsbCaPage::OnCheck() //ѡ��֤���ʽ---�����
{
	// TODO: Add your control notification handler code here
	int check=((CButton *)GetDlgItem(IDC_CHECK))->GetCheck();
	if(check) m_CertFormat=DER;
	else m_CertFormat=PEM;
}

