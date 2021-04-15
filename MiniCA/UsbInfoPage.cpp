// UsbInfoPage.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "UsbInfoPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUsbInfoPage property page

IMPLEMENT_DYNCREATE(CUsbInfoPage, CPropertyPage)

CUsbInfoPage::CUsbInfoPage() : CPropertyPage(CUsbInfoPage::IDD)
{
	//{{AFX_DATA_INIT(CUsbInfoPage)
	//}}AFX_DATA_INIT
	m_handle=((CUsbKeyApp * )AfxGetApp())->m_handle;
	m_type=-1;
}

CUsbInfoPage::~CUsbInfoPage()
{
}

void CUsbInfoPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUsbInfoPage)
	DDX_Control(pDX, IDC_LIST_INFO, m_List);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CUsbInfoPage, CPropertyPage)
	//{{AFX_MSG_MAP(CUsbInfoPage)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnRclickTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_COMMAND(ID_MENU_CREATEDIR, OnMenuCreatedir)
	ON_COMMAND(ID_MENU_DELDIR, OnMenuDeldir)
	ON_COMMAND(ID_MENU_KEYFILE, OnMenuKeyfile)
	ON_COMMAND(ID_MENU_POPFILE, OnMenuPopfile)
	ON_COMMAND(ID_MENU_DELFILE, OnMenuDelfile)
	ON_COMMAND(ID_MENU_PUTFILE, OnMenuPutfile)
	ON_BN_CLICKED(IDC_B_OK, OnBOk)
	ON_BN_CLICKED(IDC_B_CANLE, OnBCanle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//////////////////////////////////////////////////////////////////////////

bool CUsbInfoPage::OperateMsg(CString operand,EPAS_STATUS status)//״̬�����ֲ���
{
	CString info;
	bool b_result=false;
    switch( status )
    {
	case FT_SUCCESS:
		info="�����ɹ�";
		b_result=true;
		break;
	case FT_CANNOT_OPEN_DRIVER:
		info=("Error: Can't open the driver");
		break;
	case FT_INVALID_DRVR_VERSION:
		info=("Error : Driver version not supported.");
		break;
	case FT_INVALID_COMMAND:
		info= ("Error : Invalid command sent to API.");
		break;
	case FT_ACCESS_DENIED:
		info= ("Error : Access denied.");
		break;
	case FT_ALREADY_ZERO: 
		info= ("Error : Counter already zero.");
		break;
	case FT_UNIT_NOT_FOUND:
		info= ("Error : Device not found.");
		break;
	case FT_DEVICE_REMOVED:
		info= ("Error : Device removed.");
		break;
	case FT_COMMUNICATIONS_ERROR: 
		info= ("Error : Device communication error.");
		break;
	case FT_DIR_NOT_FOUND:
		info= ("Error : Directory does not exist.");
		break;
	case FT_FILE_NOT_FOUND:
		info= ("Error : File not found.");
		break;
	case FT_MEM_CORRUPT:
		info= ("Error : Device memory is corrupted.");
		break;
	case FT_INTERNAL_HW_ERROR:
		info= ("Error : Internal hardware error.");
		break;
	case FT_INVALID_RESP_SIZE:
		info= ("Error : Invalid response received from the device.");
		break;
	case FT_PIN_EXPIRED: 
		info= ("Error : PIN retry attempts has expired.");
		break;
	case FT_ALREADY_EXISTS: 
		info= ("Error : Directory or file already exist.");
		break;
	case FT_NOT_ENOUGH_MEMORY: 
		info= ("Error : Not enough memory to perform the operation.");
		break;
	case FT_INVALID_PARAMETER: 
		info= ("Error : Invalid parameter sent to API.");
		break;
	case FT_INPUT_TOO_LONG: 
		info= ("Error : Input data is too long.");
		break;
	case FT_INVALID_FILE_SELECTED: 
		info= ("Error : Invalid file selected or operation.");
		break;
	case FT_DEVICE_IN_USE: 
		info= ("Error : The device is currently in use.");
		break;
	case FT_INVALID_API_VERSION: 
		info= ("Error : The version of this library is not supported.");
		break;
	case FT_TIME_OUT_ERROR: 
		info= ("Error : Communication time-out.");
		break;
	case FT_ITEM_NOT_FOUND: 
		info= ("Error : Item not found."); 
		break;
	case FT_COMMAND_ABORTED: 
		info= ("Error : Communication error, command aborted.");
		break;
	case FT_INVALID_STATUS: 
		info= ("Error : Invalid status.");
		break;
	default: 
		info= ("Error : An unknown error occurred.");
    }
	if(b_result!=true)
		m_List.AddMsg(operand+"   "+info,M_ERROR);
	return b_result;
}

/////////////////////////////////////////////////////////////////////////////
// CUsbInfoPage message handlers
bool CUsbInfoPage::ListDir(unsigned long parDid,HTREEITEM hItem)//����Ŀ¼�ṹ
{
	EPAS_STATUS retval = FT_SUCCESS;
	EPAS_FILEINFO fi;
	ZeroMemory(&fi,sizeof(fi));
	retval = epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,parDid,NULL);
	if(!OperateMsg("epas_ChangeDir",retval))
		return false;
	for(int i=0;i<255;i++)
	{
		retval = epas_Directory(m_handle,0,i,&fi,sizeof(fi));
		if(FT_SUCCESS!=retval)
			break;
		if(EPAS_FILETYPE_DIR == fi.ucFileType)
		{
			CString strID;
			strID.Format("%X",fi.ulID);
			HTREEITEM hItemB=m_Tree.InsertItem(strID,1,2,hItem);
			m_Tree.SetItemData(hItemB,1);//Ŀ¼1
			ListDir(fi.ulID,hItemB);
			retval = epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,parDid,NULL);
			if(!OperateMsg("epas_ChangeDir",retval))
				return false;
		}
		if(EPAS_FILETYPE_DATA == fi.ucFileType)
		{
			CString strID;
			strID.Format("%X",fi.ulID);
			HTREEITEM hItemA=m_Tree.InsertItem(strID,3,3,hItem);
			m_Tree.SetItemData(hItemA,2);//�ļ�2
		}
		if(EPAS_FILETYPE_KEY== fi.ucFileType)//��ҩ
		{	
			CString strID;
			strID.Format("%X",fi.ulID);
			HTREEITEM hItemA=m_Tree.InsertItem(strID,4,4,hItem);
			m_Tree.SetItemData(hItemA,2);//�ļ�2

		}
		if(EPAS_FILETYPE_UNUSED == fi.ucFileType)
			break;
	}
	m_Tree.Expand(hItem,TVE_EXPAND);
	m_Tree.SetRedraw(TRUE);
	return true;	
}

bool CUsbInfoPage::GetDir() //ȡ��Ŀ¼�ṹ
{
	// TODO: Add your control notification handler code here
	m_Tree.SetRedraw(FALSE);
	m_Tree.DeleteAllItems();
	HTREEITEM m_hRoot=m_Tree.InsertItem("Root",0,0);
	m_Tree.SetItemData(m_hRoot,0);//��Ŀ¼
	return ListDir(0,m_hRoot);
}

bool CUsbInfoPage::GetSysInfo()
{
	EPAS_SYSINFO sysInfo;
	ZeroMemory(&sysInfo,sizeof(sysInfo));
	EPAS_STATUS m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_SYSINFO,NULL,&sysInfo,sizeof(sysInfo));
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Free memory space:  %d bytes",sysInfo.ulFreeSpace);
		m_FreeDevice=sysInfo.ulFreeSpace;//�õ�ʣ����̿ռ�
		printf("\n=>> Max directory levels: %d",sysInfo.ucMaxDirLevels);
		printf("\n=>> File system type: %d",sysInfo.ucFileSysType);
	}
/*
	EPAS_VERSIONINFO version;
	ZeroMemory(&version,sizeof(version));

	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_VERSIONINFO,NULL,&version,sizeof(version));
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Firmware Version: %d.%d\n=>> Product Code: %X",
				version.ucFwVerMajor,
				version.ucFwVerMinor,
				version.ucProductCode);		
	}
	
	unsigned long capa = 0;
	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_CAPABILITIES,NULL,&capa,sizeof(capa));
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Capabilities: %X",capa);
	}
	
	
	unsigned long memSize = 0;
	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_MEM_SIZE,NULL,&memSize,sizeof(memSize));
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Total memory size: %d bytes",memSize);
	}

	char fName[EPAS_FRIENDLY_NAME_SIZE+1];
	ZeroMemory(fName,EPAS_FRIENDLY_NAME_SIZE);
	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_FRIENDLY_NAME,NULL,fName,EPAS_FRIENDLY_NAME_SIZE);
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Friendly token name: %s",fName);
	}
	
	unsigned long sn[2];
	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_SERNUM,NULL,sn,sizeof(sn));
	if(OperateMsg("epas_GetProperty",m_epsRet))
	{
		printf("\n=>> Hardware serial number: 0x%08lX%08lX",sn[0],sn[1]);
	}
*/	return true;
}
void CUsbInfoPage::GetFreeDevice()
{
	GetSysInfo();
	CString strFree;
	strFree.Format("%d",m_FreeDevice);
	GetDlgItem(IDC_EDIT)->SetWindowText(strFree);

}

ULONG CUsbInfoPage::GetID()//�õ��ļ���Ŀ¼ID
{
	HTREEITEM handle=m_Tree.GetSelectedItem();
	if(handle==0)
		return -1;
	CString selectF=m_Tree.GetItemText(handle);
	char iBuf[80]={0};
	ULONG id;
	strcpy(iBuf,selectF);
	sscanf(iBuf,"%lx",&id);
	return id;

}

ULONG CUsbInfoPage::GetParentID()//�õ���id
{	
	HTREEITEM handle=m_Tree.GetSelectedItem();
	if(handle==0)
		return -1;
	ULONG id;
	HTREEITEM hParent=m_Tree.GetParentItem(handle);
	CString selectF=m_Tree.GetItemText(hParent);
	if(m_Tree.GetItemText(hParent)=="Root")	
		id=0;
	else
	{
		char iBuf[80]={0};
		strcpy(iBuf,selectF);
		sscanf(iBuf,"%lx",&id);
		
	}
	return id;


}

CString CUsbInfoPage::Conver(int i)
{
	if(i==0)
		return "�κ���";
	if(i==1)
		return "�û�";
	if(i==2)
		return "����Ա";
	if(i==7)
		return "��ֹ";
	else
		return "��֪��";

}

void CUsbInfoPage::GetFileDirInfo(UINT type,DWORD id)//�õ�Ŀ¼���ļ���Ϣ
{
	if(type==1000)//��Ŀ¼
	{
		SetDlgItemText(IDC_EDIT_ID,"ROOT");
		SetDlgItemText(IDC_EDIT_TYPE,"ROOT");
		SetDlgItemText(IDC_EDIT_SPACE,"ROOT");
		SetDlgItemText(IDC_EDIT_READ,"ROOT");
		SetDlgItemText(IDC_EDIT_WRITE,"ROOT");
		SetDlgItemText(IDC_EDIT_CRYPT,"ROOT");
		return;
	}
	EPAS_FILEINFO fileInfo;
    m_epsRet=epas_GetFileInfo(m_handle,type,id,0,&fileInfo,sizeof(EPAS_FILEINFO));
	if(OperateMsg("epas_GetFileInfo",m_epsRet))
	{
		char buf[10]={0};
		SetDlgItemText(IDC_EDIT_ID,itoa(fileInfo.ulID,buf,16));
		SetDlgItemText(IDC_EDIT_TYPE,itoa(fileInfo.ucFileType,buf,10));
		SetDlgItemText(IDC_EDIT_SPACE,itoa(fileInfo.ulFileSize,buf,10));

		SetDlgItemText(IDC_EDIT_READ,Conver(fileInfo.ucReadAccess));
		SetDlgItemText(IDC_EDIT_WRITE,Conver(fileInfo.ucWriteAccess));
		SetDlgItemText(IDC_EDIT_CRYPT,Conver(fileInfo.ucCryptAccess));
		
	}
}

BOOL CUsbInfoPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_imgList.Create(24,24,TRUE|ILC_COLOR8,2,2);
	HICON hIcon = NULL;

	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_ROOT), IMAGE_ICON, 24, 24, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_DIRC), IMAGE_ICON, 24, 24, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICON_DIRO), IMAGE_ICON, 24, 24, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICONFILE), IMAGE_ICON, 24, 24, 0);
	m_imgList.Add(hIcon);
	hIcon = (HICON)::LoadImage(::AfxGetInstanceHandle(), 
		MAKEINTRESOURCE(IDI_ICONKEY), IMAGE_ICON, 24, 24, 0);
	m_imgList.Add(hIcon);

	m_Tree.SetImageList(&m_imgList,TVSIL_NORMAL);

//	m_Tree.SetBkColor(RGB(200,100,0));

	epas_ResetSecurityState(m_handle,0);
	GetDir();
	GetFreeDevice();
//	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CUsbInfoPage::OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	HTREEITEM handle=m_Tree.GetSelectedItem();
	if(handle==NULL) return;
//	m_Tree.SetCheck(handle,TRUE);
	DWORD info=m_Tree.GetItemData(handle);
	
	POINT point;
	GetCursorPos(&point);
	CMenu menu;
	menu.LoadMenu(IDR_MENU_INFO);
	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup);
//	if(m_VerifySo==false)
//		pPopup->EnableMenuItem(ID_MENU_FORMAT,MF_BYCOMMAND|MF_GRAYED); 
	switch(info)
	{
	case 0: //��Ŀ¼
		pPopup->EnableMenuItem(ID_MENU_DELDIR,MF_BYCOMMAND|MF_GRAYED); 
		pPopup->EnableMenuItem(ID_MENU_DELFILE,MF_BYCOMMAND|MF_GRAYED); 
	break;
	case 1://Ŀ¼
		pPopup->EnableMenuItem(ID_MENU_CREATEDIR,MF_BYCOMMAND|MF_GRAYED); 
		pPopup->EnableMenuItem(ID_MENU_POPFILE,MF_BYCOMMAND|MF_GRAYED); 
		pPopup->EnableMenuItem(ID_MENU_DELFILE,MF_BYCOMMAND|MF_GRAYED); 
		break;
	case 2://�ļ�
		pPopup->EnableMenuItem(ID_MENU_DELDIR,MF_BYCOMMAND|MF_GRAYED); 
	//	pPopup->EnableMenuItem(ID_MENU_POPFILE,MF_BYCOMMAND|MF_GRAYED); 
	//	pPopup->EnableMenuItem(ID_MENU_DELFILE,MF_BYCOMMAND|MF_GRAYED); 
		break;
	}

	pPopup->TrackPopupMenu(TPM_LEFTBUTTON|TPM_RIGHTBUTTON|TPM_LEFTALIGN,
		point.x, point.y, this, NULL);
	menu.DestroyMenu();     	
//	*pResult = 0;
}


void CUsbInfoPage::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM handle=m_Tree.GetSelectedItem();
	if(handle==0)
		return ;
	DWORD info=m_Tree.GetItemData(handle);
	if(!info)
	{
		GetFileDirInfo(1000,0);
		return;//��Ŀ¼
	}
	ULONG id=GetID();
	if(info==1)//Ŀ¼
	{
		EPAS_STATUS m_epsRet=epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,0,NULL);
		if(OperateMsg("epas_ChangeDir",m_epsRet))
		    GetFileDirInfo(EPAS_DIR_BY_ID,id);//�õ�Ŀ¼��Ϣ
		
	}
	if(info==2) //�ļ�,�ƶ���ǰĿ¼Ϊ������
	{
		BeginWaitCursor(); 
		EPAS_STATUS m_epsRet=epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,GetParentID(),NULL);
		OperateMsg("epas_ChangeDir",m_epsRet);
		//�õ��ļ���Ϣ
	    GetFileDirInfo(0,id);
		EndWaitCursor();
		return;
	}
	BeginWaitCursor(); //Ŀ¼
	if(m_Tree.GetItemText(handle)=="Root")
		id=0;
	m_epsRet=epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,id,NULL);
	OperateMsg("epas_ChangeDir",m_epsRet);
	EndWaitCursor();	
	*pResult = 0;
}

bool CUsbInfoPage::CreateDir(CString id)
{
	EPAS_DIRINFO di;
	ZeroMemory(&di,sizeof(EPAS_DIRINFO));
	char iBuf[80]={0};
	strcpy(iBuf,id);
	sscanf(iBuf,"%lx",&di.ulID);
	BeginWaitCursor(); 
	m_epsRet=epas_ChangeDir(m_handle,EPAS_DIR_BY_LONG_ID,0,NULL);
	m_epsRet = epas_CreateDir(m_handle,0,NULL,NULL,&di,sizeof(di));
	EndWaitCursor();
	if(!OperateMsg("epas_CreateDir",m_epsRet))
		return false;
	else
		return true;
}


void CUsbInfoPage::OnMenuCreatedir() 
{
	// TODO: Add your command handler code here
	m_type=0;	
	m_List.AddMsg("������Ŀ¼ID",M_WARING);
	GetDlgItem(IDC_EDIT_INPUTID)->SetFocus();

}

void CUsbInfoPage::OnMenuDeldir() 
{
	// TODO: Add your command handler code here
	ULONG id=GetID();
	if(id==-1) return;
	BeginWaitCursor(); 
	m_epsRet = epas_DeleteDir(m_handle,EPAS_DIR_BY_LONG_ID,id,NULL);
	EndWaitCursor();
	if(!OperateMsg("epas_DeleteDir",m_epsRet))
		return ;
	GetDir();
	GetFreeDevice();
	((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=true;

	
}

void CUsbInfoPage::OnMenuKeyfile() 
{
	// TODO: Add your command handler code here
	BeginWaitCursor(); 
	EPAS_FILEINFO fi;
	unsigned char pucKey1[16];
	unsigned char pucKey2[16];
	unsigned char pucTarget[16];
	unsigned long ulWritten;
	UCHAR buf[2]={11};
	UCHAR *p=buf;
	MD5_HMAC(
		NULL,
		0,
		p,
		lstrlen((char*)p),
		pucKey1,
		pucKey2,
		pucTarget
		);

	// Create first key file.
	ZeroMemory(&fi, sizeof(EPAS_FILEINFO));
	
	fi.ulID = 100;
	fi.ulFileSize = 16;
	fi.ucFileType = EPAS_FILETYPE_KEY;
	fi.ucReadAccess = EPAS_ACCESS_NONE;
	fi.ucWriteAccess = EPAS_ACCESS_ANYONE;
	fi.ucCryptAccess = EPAS_ACCESS_ANYONE;
	
	m_epsRet = epas_CreateFile(
		m_handle,
		0,
		&fi,
		sizeof(EPAS_FILEINFO)
		);
	
	m_epsRet = epas_Write(
		m_handle,
		0,
		0,
		pucKey1,
		16,
		&ulWritten);
	OperateMsg("epas_key1",m_epsRet);
	// Create second key file.
	ZeroMemory(&fi, sizeof(EPAS_FILEINFO));
	
	fi.ulID = 200;
	fi.ulFileSize = 16;
	fi.ucFileType = EPAS_FILETYPE_KEY;
	fi.ucReadAccess = EPAS_ACCESS_NONE;
	fi.ucWriteAccess = EPAS_ACCESS_ANYONE;
	fi.ucCryptAccess = EPAS_ACCESS_ANYONE;
	
	m_epsRet = epas_CreateFile(
		m_handle,
		0,
		&fi,
		sizeof(EPAS_FILEINFO)
		);
		
	m_epsRet = epas_Write(
		m_handle,
		0,
		0,
		pucKey2,
		16,
		&ulWritten);
	OperateMsg("epas_key2",m_epsRet);
	EndWaitCursor();
	GetDir();
	GetFreeDevice();
	
}

bool CUsbInfoPage::PutFile(CString id)
{
	CFileDialog dlg(true,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"�����ļ�(*.*)|*.*||",NULL );
	if(dlg.DoModal()!=IDOK) return false;
	CString filename=dlg.GetPathName();
	CFile File;
	if(!File.Open(filename, CFile::modeRead | CFile::typeBinary))
		return false;
	int len=File.GetLength();		//�õ��ļ���С
	EPAS_FILEINFO fi;
	ZeroMemory(&fi,sizeof(EPAS_FILEINFO));
	BeginWaitCursor(); 
	char iBuf[80]={0};
	strcpy(iBuf,id);
	sscanf(iBuf,"%lx",&fi.ulID);
	fi.ucFileType = EPAS_FILETYPE_DATA;
	fi.ulFileSize = len;
	fi.ucReadAccess = EPAS_ACCESS_ANYONE;
	fi.ucWriteAccess = EPAS_ACCESS_ANYONE;
	fi.ucCryptAccess = EPAS_ACCESS_ANYONE;
	
	m_epsRet = epas_CreateFile(
		m_handle,//�豸������
		0,//����Ϊ0
		&fi,
		sizeof(EPAS_FILEINFO)//fi�����������ߴ�
		);	
	if(!OperateMsg("epas_CreateFile",m_epsRet))
		return false;
	
	File.Seek(0,CFile::begin);
	BYTE m_buf[8000]={0};
	unsigned long num=File.Read(m_buf, 8000);
	
	unsigned long ulWritten;
	m_epsRet = epas_Write(
		m_handle,//�豸������
		0,//����Ϊ0
		0,//����ļ�ͷ��ƫ��seek
		m_buf,//�����ļ����ݵĻ�����
		num,//Ҫд��ߴ�
		&ulWritten//�ɹ�д��ߴ�
		);
	OperateMsg("epas_Write",m_epsRet);
	if(num!=ulWritten)
	{
		m_List.AddMsg("д���С�����",M_ERROR);
		return false;
	}
	epas_CloseFile(m_handle);
	OperateMsg("epas_CloseFile",m_epsRet);
	EndWaitCursor();
	return true;
}

void CUsbInfoPage::OnMenuPutfile() 
{
	// TODO: Add your command handler code here
	m_type=1;
	m_List.AddMsg("�������ļ�ID",M_WARING);
	GetDlgItem(IDC_EDIT_INPUTID)->SetFocus();

}

void CUsbInfoPage::OnMenuPopfile() 
{
	// TODO: Add your command handler code here
	EPAS_FILEINFO fi;
	unsigned long ulReaded;
	BYTE pBuf[8000];
	// First, you must open the file and get the information
	// of it.
	ULONG id=GetID();
	if(id==-1) return;
	BeginWaitCursor(); 
	m_epsRet = epas_OpenFile(//���ļ�
		m_handle,
		0,//���ڵ�ǰȨ��
		id,//�ļ�ID
		&fi,//�ļ��ṹ
		sizeof(EPAS_FILEINFO)//�ṹ����
		);
	if (OperateMsg("Open file",m_epsRet))
	{
		m_epsRet = epas_Read(//���ļ�
			m_handle,
			0,//����Ϊ0
			0,//ƫ��
			pBuf,//Ŀ�Ļ�����
			fi.ulFileSize,//Ҫ���ߴ�
			&ulReaded//�ɹ��ߴ�
			);
		if(!OperateMsg("Read file",m_epsRet))
		{
			EndWaitCursor();
			return ;
		}
	}
	else
	{
		EndWaitCursor();
		return ;
	}
	EndWaitCursor();
	
	CFileDialog dlg(false,NULL,NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"�����ļ�(*.*)|*.*||",NULL );
	if(dlg.DoModal()!=IDOK) return ;
	CString filename=dlg.GetPathName();
	CFile File;
	if(!File.Open(filename, CFile::modeCreate|CFile::modeWrite))
		return ;
	File.Write(pBuf,ulReaded);
	File.Close();
	m_List.AddMsg("�����ɹ�");
}

void CUsbInfoPage::OnMenuDelfile() 
{
	// TODO: Add your command handler code here
	ULONG id=GetID();
	if(id==-1) return;
	BeginWaitCursor(); 
	m_epsRet = epas_DeleteFile(
		m_handle,
		0,//����Ϊ0
		id//�ļ�ID
		);
	if(!OperateMsg("del file",m_epsRet))
		return ;
	EndWaitCursor();
	GetDir();
	GetFreeDevice();
	((CUsbKeyApp * )AfxGetApp())->m_ChangeKey=true;

}


bool CUsbInfoPage::GetAccessInfo(BYTE * create,BYTE * del,BYTE *max, BYTE *counter)
{
	EPAS_ACCESSINFO aInfo;
	m_epsRet = epas_GetProperty(m_handle,EPAS_PROP_ACCESSINFO,NULL,&aInfo,sizeof(aInfo));
	if(!OperateMsg("epas_GetProperty",m_epsRet))
		return false;
	*create=aInfo.ucCreateAccess;
	*del=aInfo.ucDeleteAccess;
	*max=aInfo.ucMaxPinRetries;
	*counter=aInfo.ucCurPinCounter;
	return true;
}

bool CUsbInfoPage::SetProperty(BYTE * create, BYTE * del)
{
	BYTE crea,delte,max,counter;
	GetAccessInfo(&crea,&delte,&max,&counter);
	EPAS_ACCESSINFO ai;
	ZeroMemory(&ai,sizeof(ai));
	ai.ucCreateAccess = *create;
	ai.ucDeleteAccess = *del;
	ai.ucMaxPinRetries = max;
	ai.ucCurPinCounter = counter;
	
	m_epsRet = epas_SetProperty(m_handle,
		EPAS_PROP_ACCESSINFO,
		NULL,
		&ai,
		sizeof(ai));
	return OperateMsg("epas_SetProperty",m_epsRet);

}

BOOL CUsbInfoPage::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	GetDir();
	GetFreeDevice();
	
	return CPropertyPage::OnSetActive();
}

void CUsbInfoPage::OnBOk() //ִ�в���
{
	// TODO: Add your control notification handler code here
	if(m_type==-1)
		return;
	CString id;
	GetDlgItemText(IDC_EDIT_INPUTID,id);
	if(id=="")
	{
		m_List.AddMsg("IDΪ��",M_WARING);
		return;
	}
	if(m_type==0)//Ŀ¼
	{
		if(CreateDir(id))
			m_List.AddMsg("����Ŀ¼�ɹ�");
		else
			m_List.AddMsg("����Ŀ¼ʧ��",M_ERROR);
	}
	else if(m_type==1)//�ļ�
	{
		if(PutFile(id))
			m_List.AddMsg("�ϴ��ļ��ɹ�");
		else
			m_List.AddMsg("�ϴ��ļ�ʧ��",M_ERROR);
	}
	m_type=-1;
	GetDir();
	GetFreeDevice();

}

void CUsbInfoPage::OnBCanle() //ȡ������
{
	// TODO: Add your control notification handler code here
	m_type=-1;
}


bool CUsbInfoPage::Format()
{
	BeginWaitCursor(); 
	m_epsRet = epas_DeleteDir(m_handle,EPAS_DIR_BY_LONG_ID,EPAS_ROOT_DIR,NULL);
	EndWaitCursor();
	if(OperateMsg("FORMAT",m_epsRet))
		return true;
	else 
		return false;
}
