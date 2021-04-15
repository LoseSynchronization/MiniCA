// IconBtn.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "IconBtn.h"
#define	BTNST_OK						0

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIconBtn

CIconBtn::CIconBtn()
{
	m_nAlign = ST_ALIGN_HORIZ; //¶ÔÆë·½Ê½
	m_cxIcon=16;
	m_cyIcon=16;
	m_bIsFlat=FALSE;
	m_bIsPressed		= FALSE;
	m_bIsFocused		= FALSE;
	m_bIsDisabled		= FALSE;
	m_bMouseOnButton	= FALSE;
	m_byAlign = ST_ALIGN_HORIZ; 
	m_ptImageOrg.x = 3;
	m_ptImageOrg.y = 3;
	m_bDrawTransparent = FALSE;
	m_bIsCheckBox = FALSE;
	m_nCheck = 0;
	m_bAlwaysTrack = TRUE;
	SetPressedStyle(BTNST_PRESSED_LEFTRIGHT, FALSE);
	m_bIsDefault = FALSE;

}

CIconBtn::~CIconBtn()
{
}


BEGIN_MESSAGE_MAP(CIconBtn, CButton)
	//{{AFX_MSG_MAP(CIconBtn)
	ON_WM_KILLFOCUS()
	ON_WM_CAPTURECHANGED()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIconBtn message handlers

void CIconBtn::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	CDC*	pDC = CDC::FromHandle(lpDIS->hDC);

	// Checkbox?
	if (m_bIsCheckBox)
	{
		m_bIsPressed  =  (lpDIS->itemState & ODS_SELECTED) || (m_nCheck != 0);
	} // if

	m_bIsPressed = (lpDIS->itemState & ODS_SELECTED);
	m_bIsFocused  = (lpDIS->itemState & ODS_FOCUS);
	m_bIsDisabled = (lpDIS->itemState & ODS_DISABLED);

	CRect itemRect = lpDIS->rcItem;

	pDC->SetBkMode(TRANSPARENT);

	// Draw transparent?
	if (m_bDrawTransparent)
		PaintBk(pDC);
	else
		OnDrawBackground(pDC, &itemRect);

	// Draw button border
	OnDrawBorder(pDC, &itemRect);

	// Read the button's title
	CString sTitle;
	GetWindowText(sTitle);

	CRect captionRect = lpDIS->rcItem;

	DrawTheIcon(pDC, !sTitle.IsEmpty(), &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);

	// Write the button title (if any)
	if (sTitle.IsEmpty() == FALSE)
	{
		DrawTheText(pDC, (LPCTSTR)sTitle, &lpDIS->rcItem, &captionRect, m_bIsPressed, m_bIsDisabled);
	} // if

	if (m_bIsFlat == FALSE || (m_bIsFlat && m_bDrawFlatFocus))
	{
		// Draw the focus rect
		if (m_bIsFocused)
		{
			CRect focusRect = itemRect;
			focusRect.DeflateRect(3, 3);
			pDC->DrawFocusRect(&focusRect);
		} // if
	} // if
}


void CIconBtn::SetIcon(UINT nICON, UINT cx, UINT cy)
{
	m_nICON=nICON;
	m_cxIcon=cx;
	m_cyIcon=cy;
}

void CIconBtn::DrawTheText(CDC* pDC, LPCTSTR lpszText, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed, BOOL bIsDisabled)
{
	// Draw the button's title
	// If button is pressed then "press" title also
	if (m_bIsPressed && m_bIsCheckBox == FALSE)
		rpCaption->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);

	// Center text
	CRect centerRect = rpCaption;
	pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER | DT_CALCRECT);
	rpCaption->OffsetRect((centerRect.Width() - rpCaption->Width())/2, (centerRect.Height() - rpCaption->Height())/2);

	pDC->SetBkMode(TRANSPARENT);
	if (m_bIsDisabled)
	{
		rpCaption->OffsetRect(1, 1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DHILIGHT));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
		rpCaption->OffsetRect(-1, -1);
		pDC->SetTextColor(::GetSysColor(COLOR_3DSHADOW));
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} // if
	else
	{
		if (m_bMouseOnButton || m_bIsPressed) 
		{
			pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT));
			pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE));
		} // if
		else 
		{
			if (m_bIsFocused)
			{ 
				pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT)); 
				pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE)); 
			} // if
			else 
			{
				pDC->SetTextColor(::GetSysColor(COLOR_BTNTEXT)); 
				pDC->SetBkColor(::GetSysColor(COLOR_BTNFACE)); 
			} // else
		} //
		pDC->DrawText(lpszText, -1, rpCaption, DT_WORDBREAK | DT_CENTER);
	} // if
}

void CIconBtn::DrawTheIcon(CDC* pDC, BOOL bHasTitle, RECT* rpItem, CRect* rpCaption, BOOL bIsPressed,
							BOOL bIsDisabled)
{
	HICON icon=(HICON)LoadImage(AfxGetInstanceHandle(),MAKEINTRESOURCE(m_nICON),IMAGE_ICON,m_cxIcon,m_cyIcon,LR_DEFAULTCOLOR);
	CRect	rImage;
	PrepareImageRect(bHasTitle, rpItem, rpCaption, bIsPressed, m_cxIcon, m_cyIcon, &rImage);
	pDC->DrawState(	rImage.TopLeft(),
					rImage.Size(), 
					icon,
					(bIsDisabled ? DSS_DISABLED : DSS_NORMAL), 
					(CBrush*)NULL);
}

void CIconBtn::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	CancelHover();
}

void CIconBtn::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd*				wndUnderMouse = NULL;
	CWnd*				wndActive = this;
	TRACKMOUSEEVENT		csTME;

	CButton::OnMouseMove(nFlags, point);

	ClientToScreen(&point);
	wndUnderMouse = WindowFromPoint(point);

	// If the mouse enter the button with the left button pressed then do nothing
	if (nFlags & MK_LBUTTON && m_bMouseOnButton == FALSE) return;

	// If our button is not flat then do nothing
	if (m_bIsFlat == FALSE) return;

	if (m_bAlwaysTrack == FALSE)	wndActive = GetActiveWindow();

	if (wndUnderMouse && wndUnderMouse->m_hWnd == m_hWnd && wndActive)
	{
		if (!m_bMouseOnButton)
		{
			m_bMouseOnButton = TRUE;

			Invalidate();
			csTME.cbSize = sizeof(csTME);
			csTME.dwFlags = TME_LEAVE;
			csTME.hwndTrack = m_hWnd;
			::_TrackMouseEvent(&csTME);
		} // if
	} else CancelHover();
}

void CIconBtn::PrepareImageRect(BOOL bHasTitle, RECT *rpItem, CRect *rpTitle, BOOL bIsPressed, DWORD dwWidth, DWORD dwHeight, CRect *rpImage)
{
	CRect rBtn;

	rpImage->CopyRect(rpItem);

	switch (m_byAlign)
	{
		case ST_ALIGN_HORIZ:
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpImage->left += m_ptImageOrg.x;  
				rpTitle->left += dwWidth + m_ptImageOrg.x;
			}
			// Center image vertically
			rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);
			break;

		case ST_ALIGN_HORIZ_RIGHT:
			GetClientRect(&rBtn);
			if (bHasTitle == FALSE)
			{
				// Center image horizontally
				rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			}
			else
			{
				// Image must be placed just inside the focus rect
				rpTitle->right = rpTitle->Width() - dwWidth - m_ptImageOrg.x;
				rpTitle->left = m_ptImageOrg.x;
				rpImage->left = rBtn.right - dwWidth - m_ptImageOrg.x;
				// Center image vertically
				rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);
			}
			break;
		
		case ST_ALIGN_VERT:
			// Center image horizontally
			rpImage->left += ((rpImage->Width() - (long)dwWidth)/2);
			if (bHasTitle == FALSE)
			{
				// Center image vertically
				rpImage->top += ((rpImage->Height() - (long)dwHeight)/2);           
			}
			else
			{
				rpImage->top = m_ptImageOrg.y;
				rpTitle->top += dwHeight;
			}
			break;

		case ST_ALIGN_OVERLAP:
			break;
	} // switch
    
	// If button is pressed then press image also
	if (bIsPressed && m_bIsCheckBox == FALSE)
		rpImage->OffsetRect(m_ptPressedOffset.x, m_ptPressedOffset.y);
}

void CIconBtn::PaintBk(CDC *pDC)
{
	CClientDC clDC(GetParent());
	CRect rect;
	CRect rect1;

	GetClientRect(rect);

	GetWindowRect(rect1);
	GetParent()->ScreenToClient(rect1);

/*	if (m_dcBk.m_hDC == NULL)
	{
		m_dcBk.CreateCompatibleDC(&clDC);
		m_bmpBk.CreateCompatibleBitmap(&clDC, rect.Width(), rect.Height());
		m_pbmpOldBk = m_dcBk.SelectObject(&m_bmpBk);
		m_dcBk.BitBlt(0, 0, rect.Width(), rect.Height(), &clDC, rect1.left, rect1.top, SRCCOPY);
	} // if

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcBk, 0, 0, SRCCOPY);
*/}

DWORD CIconBtn::OnDrawBackground(CDC *pDC, CRect *pRect)
{
	COLORREF	crColor;

	if (m_bIsFlat == FALSE)
	{
		if (m_bIsFocused || m_bIsDefault)
		{
			CBrush br(RGB(0,0,0));  
			pDC->FrameRect(pRect, &br);
			pRect->DeflateRect(1, 1);
		} // if
	} // if

	if (m_bMouseOnButton || m_bIsPressed)
		crColor = ::GetSysColor(COLOR_BTNFACE);
	else
	{
		if (m_bIsFocused)
			crColor = ::GetSysColor(COLOR_BTNFACE);
		else
			crColor = ::GetSysColor(COLOR_BTNFACE);
	} // else

	CBrush		brBackground(crColor);

	pDC->FillRect(pRect, &brBackground);

	return BTNST_OK;
}

DWORD CIconBtn::OnDrawBorder(CDC *pDC, CRect *pRect)
{
	// Draw pressed button
	if (m_bIsPressed)
	{
		if (m_bIsFlat)
		{
			if (m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNSHADOW), ::GetSysColor(COLOR_BTNHILIGHT));
		}
		else    
		{
			CBrush brBtnShadow(GetSysColor(COLOR_BTNSHADOW));
			pDC->FrameRect(pRect, &brBtnShadow);
		}
	}
	else // ...else draw non pressed button
	{
		CPen penBtnHiLight(PS_SOLID, 0, GetSysColor(COLOR_BTNHILIGHT)); // White
		CPen pen3DLight(PS_SOLID, 0, GetSysColor(COLOR_3DLIGHT));       // Light gray
		CPen penBtnShadow(PS_SOLID, 0, GetSysColor(COLOR_BTNSHADOW));   // Dark gray
		CPen pen3DDKShadow(PS_SOLID, 0, GetSysColor(COLOR_3DDKSHADOW)); // Black

		if (m_bIsFlat)
		{
			if (m_bMouseOnButton && m_bDrawBorder)
				pDC->Draw3dRect(pRect, ::GetSysColor(COLOR_BTNHILIGHT), ::GetSysColor(COLOR_BTNSHADOW));
		}
		else
		{
			// Draw top-left borders
			// White line
			CPen* pOldPen = pDC->SelectObject(&penBtnHiLight);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->left, pRect->top);
			pDC->LineTo(pRect->right, pRect->top);
			// Light gray line
			pDC->SelectObject(pen3DLight);
			pDC->MoveTo(pRect->left+1, pRect->bottom-1);
			pDC->LineTo(pRect->left+1, pRect->top+1);
			pDC->LineTo(pRect->right, pRect->top+1);
			// Draw bottom-right borders
			// Black line
			pDC->SelectObject(pen3DDKShadow);
			pDC->MoveTo(pRect->left, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->bottom-1);
			pDC->LineTo(pRect->right-1, pRect->top-1);
			// Dark gray line
			pDC->SelectObject(penBtnShadow);
			pDC->MoveTo(pRect->left+1, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->bottom-2);
			pDC->LineTo(pRect->right-2, pRect->top);
			//
			pDC->SelectObject(pOldPen);
		} // else
	} // else

	return BTNST_OK;
}

void CIconBtn::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	UINT nBS;

	nBS = GetButtonStyle();

	// Set initial control type
	m_nTypeStyle = nBS & SS_TYPEMASK;

	// Check if this is a checkbox
	if (nBS & BS_CHECKBOX) m_bIsCheckBox = TRUE;

	// Set initial default state flag
	if (m_nTypeStyle == BS_DEFPUSHBUTTON)
	{
		// Set default state for a default button
		m_bIsDefault = TRUE;

		// Adjust style for default button
		m_nTypeStyle = BS_PUSHBUTTON;
	} // If

	// You should not set the Owner Draw before this call
	// (don't use the resource editor "Owner Draw" or
	// ModifyStyle(0, BS_OWNERDRAW) before calling PreSubclassWindow() )
//	ASSERT(m_nTypeStyle != BS_OWNERDRAW);

	// Switch to owner-draw
	ModifyStyle(SS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);
	
	CButton::PreSubclassWindow();
}

void CIconBtn::CancelHover()
{
	if (m_bIsFlat)
	{
		if (m_bMouseOnButton)
		{
			m_bMouseOnButton = FALSE;
			Invalidate();
		} // if
	} // if

}

DWORD CIconBtn::SetPressedStyle(BYTE byStyle, BOOL bRepaint)
{
	switch (byStyle)
	{
		case BTNST_PRESSED_LEFTRIGHT:
			m_ptPressedOffset.x = 1;
			m_ptPressedOffset.y = 1;
			break;
		case BTNST_PRESSED_TOPBOTTOM:
			m_ptPressedOffset.x = 0;
			m_ptPressedOffset.y = 2;
			break;
		default:
			return BTNST_INVALIDPRESSEDSTYLE;
	} // switch

	if (bRepaint)	Invalidate();

	return BTNST_OK;
}
