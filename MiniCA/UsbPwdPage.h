#if !defined(AFX_USBPWDPAGE_H__9C23B543_AE60_4E1A_AB28_872840AF1E01__INCLUDED_)
#define AFX_USBPWDPAGE_H__9C23B543_AE60_4E1A_AB28_872840AF1E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbPwdPage.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbPwdPage dialog

class CUsbPwdPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbPwdPage)

// Construction
public:
	CUsbPwdPage();
	~CUsbPwdPage();
	void GetUsbState();

// Dialog Data
	//{{AFX_DATA(CUsbPwdPage)
	enum { IDD = IDD_PROPPAGE_PWD };
	CColorListBox	m_List;
	CStatic	m_State;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbPwdPage)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbPwdPage)
	afx_msg void OnBVeruser();
	afx_msg void OnBModpwd();
	virtual BOOL OnInitDialog();
	afx_msg void OnBVerso();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	EPAS_HANDLE m_handle;
	EPAS_STATUS m_epsRet;
	BYTE m_max,m_current;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBPWDPAGE_H__9C23B543_AE60_4E1A_AB28_872840AF1E01__INCLUDED_)
