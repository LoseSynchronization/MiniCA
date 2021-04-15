// UsbSoPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbSoPage.h"
#include "usbinfopage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbSoPage property page

IMPLEMENT_DYNCREATE(CUsbSoPage, CPropertyPage)

CUsbSoPage::CUsbSoPage() : CPropertyPage(CUsbSoPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbSoPage)
	//}}AFX_DATA_INIT
	m_handle=((CUsbKeyApp * )AfxGetApp())->m_handle;
}

CUsbSoPage::~CUsbSoPage()
{
}

void CUsbSoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbSoPage)
	DDX_Control(pDX, IDC_LIST_SO, m_List);
	DDX_Control(pDX, IDC_STATIC_SOLOCK, m_SoIcon);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbSoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbSoPage)
	ON_BN_CLICKED(IDC_B_UNLOCK, OnBUnlock)
	ON_BN_CLICKED(IDC_BInitKey, OnBInitKey)
	ON_BN_CLICKED(IDC_B_SELPATH, OnBSelpath)
	ON_BN_CLICKED(IDC_B_WRITE, OnBWrite)
	ON_BN_CLICKED(IDC_B_SET, OnBSet)
	ON_BN_CLICKED(IDC_RADIO_ANYONE, OnRadioAnyone)
	ON_BN_CLICKED(IDC_RADIO_PIN, OnRadioPin)
	ON_BN_CLICKED(IDC_RADIO_SOPIN, OnRadioSopin)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnRadioNone)
	ON_BN_CLICKED(IDC_RADIO_ANYONE2, OnRadioAnyone2)
	ON_BN_CLICKED(IDC_RADIO_PIN2, OnRadioPin2)
	ON_BN_CLICKED(IDC_RADIO_SOPIN2, OnRadioSopin2)
	ON_BN_CLICKED(IDC_RADIO_NONE2, OnRadioNone2)
	ON_BN_CLICKED(IDC_B_FORMAT, OnBFormat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUsbSoPage message handlers
BOOL CUsbSoPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	GetUsbState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbSoPage::OnBUnlock() //����,ͬʱ�����û����Դ���>0����������
{
	// TODO: Add your control notification handler code here
	CString soPin=((CUsbKeyApp * )AfxGetApp())->m_SoPin;
	if(USBKey_UnlockPin(m_handle,0,(UCHAR *)soPin.GetBuffer(0))==FALSE)//����
		m_List.AddMsg("����ʧ��",M_ERROR);
	else
		m_List.AddMsg("�����ɹ�");
	GetUsbState();	
	
}


void CUsbSoPage::OnBInitKey() //��ʼ��usb
{
	// TODO: Add your control notification handler code here
	CString strUsb;
	GetDlgItemText(IDC_EDIT_UPWD,strUsb);
	if(strUsb=="")
	{
		m_List.AddMsg("����Ϊ��",M_WARING);
		return;
	}
	UCHAR out[100]={0};
	BeginWaitCursor(); 
	if(USBKey_InitKey(m_handle,(UCHAR *)strUsb.GetBuffer(0))==FALSE)//�ı�����Ϊ11111111
	{
		EndWaitCursor();
		m_List.AddMsg("��ʼ��usbʧ��",M_ERROR);
	}
	else
	{
		EndWaitCursor();
		m_List.AddMsg("��ʼ��usb�ɹ�");
		((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=true;
	}

}

void CUsbSoPage::OnBSelpath() //ѡ��֤��·��
{
	// TODO: Add your control notification handler code here
	LPITEMIDLIST pidlRoot=NULL; 
	SHGetSpecialFolderLocation(m_hWnd,CSIDL_DRIVES ,&pidlRoot); 
	BROWSEINFO bi;   //���봫��Ĳ���,�����������ṹ�Ĳ����ĳ�ʼ�� 
	CString strDisplayName;   //�����õ�,��ѡ��Ļ�ҳ��·��,�൱���ṩһ�������� 
	bi.hwndOwner=GetSafeHwnd();   //�õ�������Handleֵ 
	bi.pidlRoot=0;   //���������������������õ���. 
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   //�õ�������ָ��, 
	bi.lpszTitle="ѡ��֤���ļ���";   //���ñ��� 
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

void CUsbSoPage::OnBWrite() //д��֤��
{
	// TODO: Add your control notification handler code here
	// TODO: Add your control notification handler code here
	//��Կ֤���ļ�,ID:1001 dwCertType=1
	if(m_Path=="")
	{
		m_List.AddMsg("·��Ϊ��",M_WARING);
		return;
	}
	//��ȡ˽Կ���ݲ�����˽Կ
/*	CString m_Pwd;
	GetDlgItemText(IDC_EDIT_PRIPWD,m_Pwd);
	if(m_Pwd=="")
	{
		m_List.AddMsg("����Ϊ��",M_WARING);
		return;
	}
*/
	BeginWaitCursor();
	BYTE	certbuff[3000]={0},keybuff[3000]={0};
	UINT	len;
	CString fname=m_Path+"\\UserCert.crt";
	CFile f(fname,CFile::modeRead);
	len=f.Read(certbuff,3000);
	f.Close();


	if(!USBKey_WriteCert(m_handle,1,certbuff,len))
	{
		m_List.AddMsg("д�빫Կ�ļ�ʧ��!",M_ERROR);
		EndWaitCursor();
		return;
	}

	fname=m_Path+"\\UserKey.crt";
	f.Open(fname,CFile::modeRead);
	len=f.Read(keybuff,3000);
	f.Close();

	//˽Կ�ļ�ID:1002
	if(USBKey_WriteCert(m_handle,0,keybuff,len)==FALSE)
		m_List.AddMsg("д��˽Կ�ļ�ʧ��!",M_ERROR);
	else
	{
		m_List.AddMsg("д�ļ��ɹ�!");	
		((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=true;
	}

	EndWaitCursor();
}

void CUsbSoPage::OnBSet() //��������
{
	// TODO: Add your control notification handler code here
	if(((CUsbInfoPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(0))->SetProperty(&m_create,&m_del))
		m_List.AddMsg("���óɹ�");
}


void CUsbSoPage::OnRadioAnyone() 
{
	// TODO: Add your control notification handler code here
	m_create=0;
	
}

void CUsbSoPage::OnRadioPin() 
{
	// TODO: Add your control notification handler code here
	m_create=1;
	
}

void CUsbSoPage::OnRadioSopin() 
{
	// TODO: Add your control notification handler code here
	m_create=2;
	
}

void CUsbSoPage::OnRadioNone() 
{
	// TODO: Add your control notification handler code here
	m_create=7;
	
}

void CUsbSoPage::OnRadioAnyone2() 
{
	// TODO: Add your control notification handler code here
	m_del=0;

}

void CUsbSoPage::OnRadioPin2() 
{
	// TODO: Add your control notification handler code here
	m_del=1;

}

void CUsbSoPage::OnRadioSopin2() 
{
	// TODO: Add your control notification handler code here
	m_del=2;
	
}

void CUsbSoPage::OnRadioNone2() 
{
	// TODO: Add your control notification handler code here
	m_del=7;
	
}

void CUsbSoPage::GetUsbState()
{
	// TODO: Add extra initialization here
	for(int i=0;i<8;i++)
	{
		((CButton *)GetDlgItem(10017+i))->SetCheck(0);
	}
	BYTE max,current;
	if(((CUsbInfoPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(0))->GetAccessInfo(&m_create,&m_del,&max,&current)==false)
		return;
	if(current==0)
		m_SoIcon.SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_LOCK));
	else
		m_SoIcon.SetIcon(AfxGetApp()->LoadIcon(IDI_ICONUNLOCK));

	if(m_create==7) ((CButton *)GetDlgItem(10017+3))->SetCheck(1);
	else
		((CButton *)GetDlgItem(10017+m_create))->SetCheck(1);
	if(m_del==7) ((CButton *)GetDlgItem(10021+3))->SetCheck(1);
	else
		((CButton *)GetDlgItem(10021+m_del))->SetCheck(1);
	if(((CUsbKeyApp * )AfxGetApp())->m_VerifySo!=true)//��֤ʧ��
	{
		GetDlgItem(IDC_B_FORMAT)->EnableWindow(0);
		GetDlgItem(IDC_B_SET)->EnableWindow(0);
		GetDlgItem(IDC_BInitKey)->EnableWindow(0);
		GetDlgItem(IDC_B_SELPATH)->EnableWindow(0);
		GetDlgItem(IDC_B_WRITE)->EnableWindow(0);
		GetDlgItem(IDC_B_UNLOCK)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_UPWD)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow(0);
		GetDlgItem(IDC_EDIT_PRIPWD)->EnableWindow(0);
		GetDlgItem(IDC_LIST_SO)->EnableWindow(0);
		for(int i=10017;i<10025;i++)
			GetDlgItem(i)->EnableWindow(0);
	}
	else
	{
		GetDlgItem(IDC_B_FORMAT)->EnableWindow(1);
		GetDlgItem(IDC_B_SET)->EnableWindow(1);
		GetDlgItem(IDC_BInitKey)->EnableWindow(1);
		GetDlgItem(IDC_B_SELPATH)->EnableWindow(1);
		GetDlgItem(IDC_B_WRITE)->EnableWindow(1);
		GetDlgItem(IDC_B_UNLOCK)->EnableWindow(1);
		GetDlgItem(IDC_EDIT_UPWD)->EnableWindow(1);
		GetDlgItem(IDC_EDIT_PATH)->EnableWindow(1);
		GetDlgItem(IDC_EDIT_PRIPWD)->EnableWindow(1);
		GetDlgItem(IDC_LIST_SO)->EnableWindow(1);
		for(int i=10017;i<10025;i++)
			GetDlgItem(i)->EnableWindow(1);
	}

}

BOOL CUsbSoPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetUsbState();
	return CPropertyPage::OnSetActive();
}


void CUsbSoPage::OnBFormat() 
{
	// TODO: Add your control notification handler code here
	if(((CUsbInfoPage *)((CPropertySheet *)AfxGetMainWnd())->GetPage(0))->Format())
	{
		m_List.AddMsg("��ʽ���ɹ�");
		((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=true;
	}
	else
		m_List.AddMsg("��ʽ��ʧ��",M_ERROR);
}
