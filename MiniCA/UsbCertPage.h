#if !defined(AFX_USBCERTPAGE_H__BA3DE6AC_0660_49FF_9937_D50BDA157C2E__INCLUDED_)
#define AFX_USBCERTPAGE_H__BA3DE6AC_0660_49FF_9937_D50BDA157C2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbCertPage.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbCertPage dialog

class CUsbCertPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbCertPage)
private:
	void SetCheck();
	CString m_Path;
// Construction
public:
	CUsbCertPage();
	~CUsbCertPage();
	CString m_PriKey;
	CString m_p12;
	CString m_cert;
	CString m_key;

// Dialog Data
	//{{AFX_DATA(CUsbCertPage)
	enum { IDD = IDD_PROPPAGE_EXT };
	CColorListBox	m_List;
	int		m_Type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbCertPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbCertPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnBptod();
	afx_msg void OnBPath();
	afx_msg void OnBPub();
	afx_msg void OnBKey();
	afx_msg void OnBOk();
	afx_msg void OnRParse();
	afx_msg void OnRCreate();
	afx_msg void OnRChangep();
	afx_msg void OnBdtop();
	afx_msg void OnBsout();
	afx_msg void OnBsin();
	afx_msg void OnBCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBCERTPAGE_H__BA3DE6AC_0660_49FF_9937_D50BDA157C2E__INCLUDED_)
