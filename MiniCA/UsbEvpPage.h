#if !defined(AFX_USBEVPPAGE_H__F03905CF_F75D_4068_8C58_2E825A31C4DD__INCLUDED_)
#define AFX_USBEVPPAGE_H__F03905CF_F75D_4068_8C58_2E825A31C4DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbEvpPage.h : header file
//
#include "ColorListBox.h"
#include "TextProgressCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbEvpPage dialog

class CUsbEvpPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbEvpPage)

// Construction
public:
	CUsbEvpPage();
	~CUsbEvpPage();

// Dialog Data
	//{{AFX_DATA(CUsbEvpPage)
	enum { IDD = IDD_PROPPAGE_EVP };
	CTextProgressCtrl	m_Progress;
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbEvpPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	static void DrawProg(int i);
	// Generated message map functions
	//{{AFX_MSG(CUsbEvpPage)
	afx_msg void OnBsout();
	afx_msg void OnBsin();
	afx_msg void OnBenc();
	afx_msg void OnBdec();
	virtual BOOL OnInitDialog();
	afx_msg void OnBseal();
	afx_msg void OnBopenseal();
	afx_msg void OnBdigest();
	afx_msg void OnBsign();
	afx_msg void OnBvsign();
	afx_msg void OnBrsacert();
	afx_msg void OnBrsakey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_per;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBEVPPAGE_H__F03905CF_F75D_4068_8C58_2E825A31C4DD__INCLUDED_)
