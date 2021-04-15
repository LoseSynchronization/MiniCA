#if !defined(AFX_INPUTCERTVIEW_H__0D88E4FF_4A0B_4436_8F69_D9A7ABE5A40C__INCLUDED_)
#define AFX_INPUTCERTVIEW_H__0D88E4FF_4A0B_4436_8F69_D9A7ABE5A40C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InputCertView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInputCertView form view
#include "IconBtn.h"

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif


class CInputCertView : public CFormView
{
protected:
	CInputCertView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CInputCertView)

// Form Data
public:
	//{{AFX_DATA(CInputCertView)
	enum { IDD = IDD_FORMVIEW_INPUT };
	CIconBtn	m_Cancle;
	CIconBtn	m_Apply;
	//}}AFX_DATA

// Attributes
public:
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInputCertView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CInputCertView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CInputCertView)
	afx_msg void OnButtonInputQuery();
	afx_msg void OnButtonApply();
	afx_msg void OnButtonCancle();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INPUTCERTVIEW_H__0D88E4FF_4A0B_4436_8F69_D9A7ABE5A40C__INCLUDED_)
