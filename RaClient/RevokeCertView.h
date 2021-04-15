#if !defined(AFX_REVOKECERTVIEW_H__A19494B6_C0F1_45DF_99E3_421B397D9A01__INCLUDED_)
#define AFX_REVOKECERTVIEW_H__A19494B6_C0F1_45DF_99E3_421B397D9A01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RevokeCertView.h : header file
//
#include "IconBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CRevokeCertView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CRevokeCertView : public CFormView
{
protected:
	CRevokeCertView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CRevokeCertView)
// Form Data
public:
	//{{AFX_DATA(CRevokeCertView)
	enum { IDD = IDD_FORMVIEW_REVOKE };
	CIconBtn	m_Find;
	CIconBtn	m_Mcrl;
	CIconBtn	m_Revoke;
	CListCtrl	m_List;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRevokeCertView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CRevokeCertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CRevokeCertView)
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeCombo();
	afx_msg void OnButtonRevoke();
	afx_msg void OnBCrl();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnButtonFind();
	afx_msg void OnItemchangedListRevoke(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	BOOL m_FindType;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REVOKECERTVIEW_H__A19494B6_C0F1_45DF_99E3_421B397D9A01__INCLUDED_)
