#if !defined(AFX_USBCAPAGE_H__5AD36C39_E124_4AE2_8D7A_2A7D11A740F4__INCLUDED_)
#define AFX_USBCAPAGE_H__5AD36C39_E124_4AE2_8D7A_2A7D11A740F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbCaPage.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbCaPage dialog

class CUsbCaPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbCaPage)

// Construction
public:
	CUsbCaPage();
	~CUsbCaPage();
	CString m_Path;

// Dialog Data
	//{{AFX_DATA(CUsbCaPage)
	enum { IDD = IDD_PROPPAGE_CA };
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbCaPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbCaPage)
	afx_msg void OnBPath();
	virtual BOOL OnInitDialog();
	afx_msg void OnBPath4();
	afx_msg void OnBCrl();
	afx_msg void OnBMkroot();
	afx_msg void OnBMkreq();
	afx_msg void OnBMkcert();
	afx_msg void OnCheck();
	afx_msg void OnBMkcert2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_CertFormat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBCAPAGE_H__5AD36C39_E124_4AE2_8D7A_2A7D11A740F4__INCLUDED_)
