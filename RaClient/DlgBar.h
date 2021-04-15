#if !defined(AFX_DLGBAR_H__A1754170_9AFA_4BED_A49F_573E90996339__INCLUDED_)
#define AFX_DLGBAR_H__A1754170_9AFA_4BED_A49F_573E90996339__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBar.h : header file
//
#include "ColorListBox.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBar dialog

class CDlgBar : public CDialogBar
{
// Construction
public:
	BOOL OnInitDialogBar();
	CDlgBar(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBar)
	enum { IDD = IDD_DIALOGBAR };
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBar)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBar)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBAR_H__A1754170_9AFA_4BED_A49F_573E90996339__INCLUDED_)
