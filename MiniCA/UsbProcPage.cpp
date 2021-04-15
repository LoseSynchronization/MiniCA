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
	if(((CUsbKeyApp * )AfxGetApp())->m_VerifyUser!=true)//δ��֤�û�-�ر�
	{
		GetDlgItem(IDC_B_ENC)->EnableWindow(0);
		GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
		GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
		GetDlgItem(IDC_B_ENC)->EnableWindow(0);
		GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
		GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
		return;
	}

	else//ʹ��USB��Կ
	{

		if(((CUsbKeyApp * )AfxGetApp())->m_ChangeKey==false)//����û�иı�
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
		else if(((CUsbKeyApp * )AfxGetApp())->m_ChangeKey==true)//���̸ı�
		{

			GetDlgItem(IDC_B_ENC)->EnableWindow(0);
			GetDlgItem(IDC_B_VERIFY)->EnableWindow(0);
			GetDlgItem(IDC_B_SEAL)->EnableWindow(0);
			GetDlgItem(IDC_B_DEC)->EnableWindow(0);
			GetDlgItem(IDC_BSIGN)->EnableWindow(0);
			GetDlgItem(IDC_B_OPEN)->EnableWindow(0);
	
			if(GetUsbPubCert()==true)//ȡ�ù�Կ//���Ź�Կ����
			{
				GetDlgItem(IDC_B_ENC)->EnableWindow(1);
				GetDlgItem(IDC_B_VERIFY)->EnableWindow(1);
				GetDlgItem(IDC_B_SEAL)->EnableWindow(1);
			}
			if(GetUsbPriCert()==true)//����˽Կ����
			{
				GetDlgItem(IDC_B_DEC)->EnableWindow(1);
				GetDlgItem(IDC_BSIGN)->EnableWindow(1);
				GetDlgItem(IDC_B_OPEN)->EnableWindow(1);
			}
			((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=false;

		}
	}
}

bool CUsbProcPage::GetUsbPubCert()//ȡ��usb��Կ
{
	if(USBKey_ReadCert(m_handle,1,(unsigned char *)m_pubkey,&m_pubkey_len)==FALSE)//�ɹ�
	{
		m_List.AddMsg("�Ҳ���USB��Կ֤��",M_ERROR);
		return FALSE;
	}
	m_OpenPub=true;
	m_List.AddMsg("��ù�Կ�ɹ�");
	return true;
}

bool CUsbProcPage::GetUsbPriCert()
{
	//////////////����˽Կ�ļ�///////////////////////////
	if(USBKey_ReadCert(m_handle,0,(unsigned char *)m_prikey,(ULONG *)&m_prikey_len)==FALSE)
	{
		m_List.AddMsg("���˽Կʧ��",M_ERROR);
		return false;
	}
	/////////////////////////////////////////////////////
	m_OpenPri=true;
	m_List.AddMsg("���˽Կ�ɹ�");
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

void CUsbProcPage::OnBEnc() //��Կ����
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
	m_List.AddMsg("���ܳɹ�");
}

void CUsbProcPage::OnBDec() //˽Կ����
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
	m_List.AddMsg("���ܳɹ�");
}

void CUsbProcPage::OnBsign() //����ǩ��-----ʹ��ǩ��˽Կ����ǩ��
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
	m_List.AddMsg("����ǩ���ɹ�");
}

void CUsbProcPage::OnBVerify() //��֤����ǩ��---��Կ
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
	m_List.AddMsg("��֤ǩ���ɹ�");
}

void CUsbProcPage::OnBSeal() //װ�ŷ�--��Կ
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
		m_List.AddMsg("��װ�ļ��ɹ�");
}

void CUsbProcPage::OnBOpen() //�������ŷ�--˽Կ
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
		m_List.AddMsg("����ļ��ɹ�");
}

void CUsbProcPage::OnBGetrand() 
{
	// TODO: Add your control notification handler code here
	CString strLeng;
	GetDlgItemText(IDC_EDIT_LEN,strLeng);
	if(strLeng=="")
	{
		m_List.AddMsg("����Ϊ��",M_WARING);
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
	"�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="ѡ���ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_INFILE,dlgOpen.GetPathName());

}

void CUsbProcPage::OnBsin()
{
	// TODO: Add your control notification handler code here
	CFileDialog dlgOpen(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
	"�����ļ�(*.*)|*.*||",NULL);
	dlgOpen.m_ofn.lpstrTitle="ѡ�񱣴��ļ�";//������
	if(dlgOpen.DoModal()!=IDOK) return;
	SetDlgItemText(IDC_EDIT_OUTFILE,dlgOpen.GetPathName());
}
