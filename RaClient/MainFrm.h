// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__207545B8_1118_494A_8A20_F2EFED467B26__INCLUDED_)
#define AFX_MAINFRM_H__207545B8_1118_494A_8A20_F2EFED467B26__INCLUDED_
#include "raChildFrame.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ProgStatusBar.h"
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
// Operations
public:
	CRaChildFrame *m_pInput,*m_pAuditing,*m_pMade,*m_pRevoke;
	CImageList	m_imageList;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_PathCert,m_PathCrl;//Â·¾¶
	void SetStatusText(int nPane,CString str);
	void ShowFind(BOOL);
	void SetStatusIcon(int nPane,UINT nICON);
	int SetPos(int nPos);
	void SetRange(int nLower, int nUpper);
	void AddDialogBarInfo(int index, CString msg,int info=M_OK);
	void SetToolBarShow();
	void SetToolBarHide();
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CProgStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnInputUnit();
	afx_msg void OnAuditingCert();
	afx_msg void OnMadeMade();
	afx_msg void OnCertRevoke();
	//}}AFX_MSG
	afx_msg LRESULT OnRaMsg( WPARAM wParam,LPARAM lParam );
	afx_msg BOOL ShowTips(UINT id,NMHDR* PNMHDR,LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__207545B8_1118_494A_8A20_F2EFED467B26__INCLUDED_)
