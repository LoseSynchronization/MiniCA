#if !defined(AFX_COLORLISTBOX_H__4DC6E762_4FBB_4F05_B65A_82DD2A7F7B68__INCLUDED_)
#define AFX_COLORLISTBOX_H__4DC6E762_4FBB_4F05_B65A_82DD2A7F7B68__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorListBox.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CColorListBox window

class CColorListBox : public CListBox
{
// Construction
public:
	CColorListBox();
	int AddMsg(CString lpszItem, DWORD info=M_OK);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorListBox)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDIS);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorListBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorListBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORLISTBOX_H__4DC6E762_4FBB_4F05_B65A_82DD2A7F7B68__INCLUDED_)
