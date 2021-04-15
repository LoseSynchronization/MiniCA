#if !defined(AFX_LOGDLG_H__39A6DFAB_25BB_4804_8512_DEFB3963E468__INCLUDED_)
#define AFX_LOGDLG_H__39A6DFAB_25BB_4804_8512_DEFB3963E468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogDlg.h : header file
//

#include "ColorListBox.h"
#include "IconBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CLogDlg dialog

class CLogDlg : public CDialog
{
// Construction
public:
	CLogDlg(CWnd* pParent = NULL);   // standard constructor
	int m_ConnectTime;
private:
	CRect m_dlgRect_big; //全部对话框大的
	CRect m_dlgRect_small;//显示大小-----小的
// Dialog Data
	//{{AFX_DATA(CLogDlg)
	enum { IDD = IDD_DIALOG_LOGO };
	CIconBtn	m_Ok;
	CIconBtn	m_Cancel;
	CColorListBox	m_List;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGDLG_H__39A6DFAB_25BB_4804_8512_DEFB3963E468__INCLUDED_)
