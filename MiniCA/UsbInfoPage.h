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
	int m_type;//操作类型，0-目录，1-文件,-1-无操作
	bool PutFile(CString id);//上传文件
	bool CreateDir(CString id);//创建目录
	CString Conver(int i);//转换-1----任何人
	void GetFileDirInfo(UINT type,DWORD id);//得到目录、文件信息
	void GetFreeDevice();//得到剩余磁盘空间
	bool ListDir(unsigned long parDid,HTREEITEM hItem);//查找目录
	CImageList m_imgList;
	ULONG m_FreeDevice;//剩余磁盘空间
	bool OperateMsg(CString operand,EPAS_STATUS status);//操作信息
	bool GetSysInfo();
	ULONG GetParentID();
	ULONG GetID();//得到目录、文件的ID
	bool GetDir();//得到目录结构


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBINFOPAGE_H__D4F006C7_F924_4534_82FD_C6578E4593D1__INCLUDED_)
