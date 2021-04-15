#if !defined(AFX_PROGSTATUSBAR_H__3D0D2883_3A65_4D57_9759_CD93A8F3D8EE__INCLUDED_)
#define AFX_PROGSTATUSBAR_H__3D0D2883_3A65_4D57_9759_CD93A8F3D8EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProgStatusBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgStatusBar window

class CProgStatusBar : public CStatusBar
{
// Construction
public:
	CProgStatusBar();

// Attributes
public:
	CProgressCtrl m_wndProgQuery;//≤È—Ø
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgStatusBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void ShowProg(BOOL);
	virtual ~CProgStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CProgStatusBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGSTATUSBAR_H__3D0D2883_3A65_4D57_9759_CD93A8F3D8EE__INCLUDED_)
