#if !defined(AFX_USBPROCPAGE_H__6FD5D920_31D2_48B3_BDE3_F55D8124AF85__INCLUDED_)
#define AFX_USBPROCPAGE_H__6FD5D920_31D2_48B3_BDE3_F55D8124AF85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbProcPage.h : header file
//
#include "ColorListBox.h"
#include "TextProgressCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbProcPage dialog

class CUsbProcPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbProcPage)

// Construction
public:
	CUsbProcPage();
	~CUsbProcPage();

// Dialog Data
	//{{AFX_DATA(CUsbProcPage)
	enum { IDD = IDD_PROPPAGE_PROC };
	CTextProgressCtrl	m_Progress;
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbProcPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbProcPage)
	afx_msg void OnBEnc();
	afx_msg void OnBDec();
	afx_msg void OnBsign();
	afx_msg void OnBVerify();
	afx_msg void OnBSeal();
	afx_msg void OnBOpen();
	afx_msg void OnBGetrand();
	virtual BOOL OnInitDialog();
	afx_msg void OnBsout();
	afx_msg void OnBsin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool GetUsbPriCert();
	bool GetUsbPubCert();
	void GetUsbState();
	char m_pubkey[3000];//公钥
	char m_prikey[3000]; //私钥
	ULONG m_pubkey_len,m_prikey_len; //公钥长度
	bool m_OpenPub,m_OpenPri;//是否开放功能
	EPAS_HANDLE m_handle;
	EPAS_STATUS m_epsRet;
	static void DrawProg(int i);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBPROCPAGE_H__6FD5D920_31D2_48B3_BDE3_F55D8124AF85__INCLUDED_)
