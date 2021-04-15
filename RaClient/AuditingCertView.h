#if !defined(AFX_AUDITINGCERTVIEW_H__713B8247_A2E1_49D9_9C83_F1D84FFAF399__INCLUDED_)
#define AFX_AUDITINGCERTVIEW_H__713B8247_A2E1_49D9_9C83_F1D84FFAF399__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AuditingCertView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAuditingCertView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "IconBtn.h"

class CAuditingCertView : public CFormView
{
protected:
	CAuditingCertView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CAuditingCertView)
// Form Data
public:
	//{{AFX_DATA(CAuditingCertView)
	enum { IDD = IDD_FORMVIEW_AUDIT };
	CIconBtn	m_Naudit;
	CIconBtn	m_Paudit;
	CIconBtn	m_Faudit;
	CListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:
	CString m_num;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAuditingCertView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CAuditingCertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CAuditingCertView)
	afx_msg void OnButtonAuditing();
	afx_msg void OnButtonPass();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnItemchangedListAuditing(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUDITINGCERTVIEW_H__713B8247_A2E1_49D9_9C83_F1D84FFAF399__INCLUDED_)
