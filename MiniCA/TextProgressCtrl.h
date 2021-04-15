#if !defined(AFX_TEXTPROGRESSCTRL_H__452F1F02_3638_40C2_81AC_7829607D7CBD__INCLUDED_)
#define AFX_TEXTPROGRESSCTRL_H__452F1F02_3638_40C2_81AC_7829607D7CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextProgressCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl window

class CTextProgressCtrl : public CProgressCtrl
{
// Construction
public:
	CTextProgressCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextProgressCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	int SetPos(int nPos);
	void SetRange(int nLower, int nUpper);
	virtual ~CTextProgressCtrl();

	// Generated message map functions
protected:
    int         m_nPos, 
                m_nStepSize, 
                m_nMax, 
                m_nMin;
    CString     m_strText;
    BOOL        m_bShowText;
    int         m_nBarWidth;
    COLORREF    m_colFore,
                m_colBk,
                m_colTextFore,
                m_colTextBk;

	//{{AFX_MSG(CTextProgressCtrl)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTPROGRESSCTRL_H__452F1F02_3638_40C2_81AC_7829607D7CBD__INCLUDED_)
