#if !defined(AFX_USBKEYSHEET_H__9DB24E37_D9EE_4165_8D65_13C58BC84E81__INCLUDED_)
#define AFX_USBKEYSHEET_H__9DB24E37_D9EE_4165_8D65_13C58BC84E81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbKeySheet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUsbKeySheet
#define WM_SYSTEMTRAY WM_USER+100	//系统托盘消息

class CUsbKeySheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CUsbKeySheet)

// Construction
public:
	CUsbKeySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CUsbKeySheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CImageList m_imgList;
// Attributes
public:
	NOTIFYICONDATA m_nid;//托盘

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsbKeySheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsbKeySheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CUsbKeySheet)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBKEYSHEET_H__9DB24E37_D9EE_4165_8D65_13C58BC84E81__INCLUDED_)
