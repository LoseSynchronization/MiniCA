// TextProgressCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TextProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl

CTextProgressCtrl::CTextProgressCtrl()
{
	m_nPos            = 0;
    m_nStepSize       = 1;
    m_nMax            = 100;
    m_nMin            = 0;
    m_bShowText       = TRUE;
    m_strText.Empty();
	m_colFore        = ::GetSysColor(COLOR_HIGHLIGHT);//进度条颜色
    m_colBk          =::GetSysColor(COLOR_WINDOW);//背景颜色，没有填充时候颜色
    m_colTextFore    =::GetSysColor(COLOR_HIGHLIGHT);//%50以前颜色
    m_colTextBk      =::GetSysColor(COLOR_WINDOW);//%50以后颜色

}

CTextProgressCtrl::~CTextProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CTextProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CTextProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextProgressCtrl message handlers

void CTextProgressCtrl::SetRange(int nLower, int nUpper)
{
    m_nMax = nUpper;
    m_nMin = nLower;
}

int CTextProgressCtrl::SetPos(int nPos)
{
	if (!::IsWindow(m_hWnd))
        return -1;
    int nOldPos = m_nPos;
    m_nPos = nPos;

    CRect rect;
    GetClientRect(rect);

    double Fraction = (double)(m_nPos - m_nMin) / ((double)(m_nMax - m_nMin));
    int nBarWidth = (int) (Fraction * rect.Width());

    if (nBarWidth != m_nBarWidth)
    {
        m_nBarWidth = nBarWidth;
        RedrawWindow();
    }

    return nOldPos;

}

void CTextProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
    if (m_nMin >= m_nMax) 
        return;
	if(m_nPos>m_nMax) return;
//	if(m_nPos==0) return;
    CRect LeftRect, RightRect, ClientRect;
    GetClientRect(ClientRect);

    double Fraction = (double)(m_nPos - m_nMin) / ((double)(m_nMax - m_nMin));


    LeftRect = RightRect = ClientRect;

    LeftRect.right = LeftRect.left + (int)((LeftRect.right - LeftRect.left)*Fraction);
    dc.FillSolidRect(LeftRect, m_colFore);

    RightRect.left = LeftRect.right;
    dc.FillSolidRect(RightRect, m_colBk);

    if (m_bShowText)
    {
        CString str;
        if (m_strText.GetLength())
            str = m_strText;
        else
            str.Format("%d%%", (int)(Fraction*100.0));

        dc.SetBkMode(TRANSPARENT);

        CRgn rgn;
        rgn.CreateRectRgn(LeftRect.left, LeftRect.top, LeftRect.right, LeftRect.bottom);
        dc.SelectClipRgn(&rgn);
        dc.SetTextColor(m_colTextBk);

        dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

        rgn.DeleteObject();
        rgn.CreateRectRgn(RightRect.left, RightRect.top, RightRect.right, RightRect.bottom);
        dc.SelectClipRgn(&rgn);
        dc.SetTextColor(m_colTextFore);

        dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    }	
	// Do not call CProgressCtrl::OnPaint() for painting messages
}

BOOL CTextProgressCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
//	return CProgressCtrl::OnEraseBkgnd(pDC);
}
