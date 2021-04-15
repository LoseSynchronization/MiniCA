#if !defined(AFX_RACHILDFRAME_H__C8B3028A_57F6_464E_BBAC_3D053D403456__INCLUDED_)
#define AFX_RACHILDFRAME_H__C8B3028A_57F6_464E_BBAC_3D053D403456__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "infobar.h"
// RaChildFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRaChildFrame frame
#include "DlgBar.h"

class CRaChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CRaChildFrame)
public:
	CRaChildFrame();  
// Attributes
public:
	CDlgBar m_wndBar;
// Operations
public:
	void AddMsg(CString str,DWORD info=M_OK);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRaChildFrame)
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRaChildFrame();

	// Generated message map functions
	//{{AFX_MSG(CRaChildFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RACHILDFRAME_H__C8B3028A_57F6_464E_BBAC_3D053D403456__INCLUDED_)
