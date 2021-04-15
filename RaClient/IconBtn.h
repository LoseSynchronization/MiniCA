#if !defined(AFX_ICONBTN_H__8A0464E0_C8AF_44DB_8960_D795B2BB5C87__INCLUDED_)
#define AFX_ICONBTN_H__8A0464E0_C8AF_44DB_8960_D795B2BB5C87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IconBtn.h : header file
//
#define	BTNST_INVALIDPRESSEDSTYLE		6

/////////////////////////////////////////////////////////////////////////////
// CIconBtn window
class CIconBtn : public CButton
{
// Construction
public:
	CIconBtn();
    enum	{	ST_ALIGN_HORIZ	= 0,			// Icon/bitmap on the left, text on the right
				ST_ALIGN_VERT,					// Icon/bitmap on the top, text on the bottom
				ST_ALIGN_HORIZ_RIGHT,			// Icon/bitmap on the right, text on the left
				ST_ALIGN_OVERLAP				// Icon/bitmap on the same space as text
			};
    enum	{	BTNST_PRESSED_LEFTRIGHT = 0,	// Pressed style from left to right (as usual)
				BTNST_PRESSED_TOPBOTTOM			// Pressed style from top to bottom
			};

// Attributes
public:
	POINT	m_ptImageOrg;
	POINT	m_ptPressedOffset;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIconBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetIcon(UINT nICON,UINT cx=16,UINT cy=16);
	virtual ~CIconBtn();

	// Generated message map functions
protected:
	//{{AFX_MSG(CIconBtn)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	DWORD SetPressedStyle(BYTE byStyle, BOOL bRepaint);
	void CancelHover();
	DWORD OnDrawBorder(CDC* pDC, CRect* pRect);
	DWORD OnDrawBackground(CDC* pDC, CRect* pRect);
	void PaintBk(CDC* pDC);
	void PrepareImageRect(BOOL bHasTitle, RECT* rpItem, CRect* rpTitle, BOOL bIsPressed, 
							DWORD dwWidth, DWORD dwHeight, CRect* rpImage);
	void DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed,
						BOOL bIsDisabled);
	void DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed,
							BOOL bIsDisabled);
	int m_nAlign;
	UINT m_nICON,m_cxIcon,m_cyIcon;
	BOOL		m_bIsFlat;			// Is a flat button?
	BOOL		m_bMouseOnButton;	// Is mouse over the button?
	BOOL		m_bDrawTransparent;	// Draw transparent?
	BOOL		m_bIsPressed;		// Is button pressed?
	BOOL		m_bIsFocused;		// Is button focused?
	BOOL		m_bIsDisabled;		// Is button disabled?
	BOOL		m_bIsDefault;		// Is default button?
	BOOL		m_bIsCheckBox;		// Is the button a checkbox?
	BYTE		m_byAlign;			// Align mode
	BOOL		m_bDrawBorder;		// Draw border?
	BOOL		m_bDrawFlatFocus;	// Draw focus rectangle for flat button?
	int			m_nCheck;			// Current value for checkbox
	UINT		m_nTypeStyle;		// Button style
	BOOL		m_bAlwaysTrack;		// Always hilight button?

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ICONBTN_H__8A0464E0_C8AF_44DB_8960_D795B2BB5C87__INCLUDED_)
