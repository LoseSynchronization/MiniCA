#if !defined(AFX_USBSOPAGE_H__0FF6E828_9A9D_4B2B_A10E_02A06C21A9A1__INCLUDED_)
#define AFX_USBSOPAGE_H__0FF6E828_9A9D_4B2B_A10E_02A06C21A9A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbSoPage.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbSoPage dialog

class CUsbSoPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbSoPage)

// Construction
public:
	CUsbSoPage();
	~CUsbSoPage();

// Dialog Data
	//{{AFX_DATA(CUsbSoPage)
	enum { IDD = IDD_PROPPAGE_SO };
	CColorListBox	m_List;
	CStatic	m_SoIcon;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbSoPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbSoPage)
	afx_msg void OnBUnlock();
	afx_msg void OnBInitKey();
	afx_msg void OnBSelpath();
	afx_msg void OnBWrite();
	afx_msg void OnBSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnRadioAnyone();
	afx_msg void OnRadioPin();
	afx_msg void OnRadioSopin();
	afx_msg void OnRadioNone();
	afx_msg void OnRadioAnyone2();
	afx_msg void OnRadioPin2();
	afx_msg void OnRadioSopin2();
	afx_msg void OnRadioNone2();
	afx_msg void OnBFormat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void GetUsbState();
	EPAS_HANDLE m_handle;
	EPAS_STATUS m_epsRet;
	CString m_Path;
	BYTE m_create,m_del;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBSOPAGE_H__0FF6E828_9A9D_4B2B_A10E_02A06C21A9A1__INCLUDED_)
