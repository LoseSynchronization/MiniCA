#if !defined(AFX_USBINFOPAGE_H__D4F006C7_F924_4534_82FD_C6578E4593D1__INCLUDED_)
#define AFX_USBINFOPAGE_H__D4F006C7_F924_4534_82FD_C6578E4593D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbInfoPage.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbInfoPage dialog

class CUsbInfoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbInfoPage)

// Construction
public:
	bool Format();
	bool SetProperty(BYTE * create,BYTE * del);
	bool GetAccessInfo(BYTE * create,BYTE * del,BYTE * max,BYTE * counter);
	CUsbInfoPage();
	~CUsbInfoPage();

// Dialog Data
	//{{AFX_DATA(CUsbInfoPage)
	enum { IDD = IDD_PROPPAGE_KEYINFO };
	CColorListBox	m_List;
	CTreeCtrl	m_Tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbInfoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbInfoPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuCreatedir();
	afx_msg void OnMenuDeldir();
	afx_msg void OnMenuKeyfile();
	afx_msg void OnMenuPopfile();
	afx_msg void OnMenuDelfile();
	afx_msg void OnMenuPutfile();
	afx_msg void OnBOk();
	afx_msg void OnBCanle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	EPAS_HANDLE m_handle;
	EPAS_STATUS m_epsRet;
	int m_type;//�������ͣ�0-Ŀ¼��1-�ļ�,-1-�޲���
	bool PutFile(CString id);//�ϴ��ļ�
	bool CreateDir(CString id);//����Ŀ¼
	CString Conver(int i);//ת��-1----�κ���
	void GetFileDirInfo(UINT type,DWORD id);//�õ�Ŀ¼���ļ���Ϣ
	void GetFreeDevice();//�õ�ʣ����̿ռ�
	bool ListDir(unsigned long parDid,HTREEITEM hItem);//����Ŀ¼
	CImageList m_imgList;
	ULONG m_FreeDevice;//ʣ����̿ռ�
	bool OperateMsg(CString operand,EPAS_STATUS status);//������Ϣ
	bool GetSysInfo();
	ULONG GetParentID();
	ULONG GetID();//�õ�Ŀ¼���ļ���ID
	bool GetDir();//�õ�Ŀ¼�ṹ


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBINFOPAGE_H__D4F006C7_F924_4534_82FD_C6578E4593D1__INCLUDED_)
