// ColorListBox.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "ColorListBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListBox

CColorListBox::CColorListBox()
{
}

CColorListBox::~CColorListBox()
{
}


BEGIN_MESSAGE_MAP(CColorListBox, CListBox)
	//{{AFX_MSG_MAP(CColorListBox)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListBox message handlers
void CColorListBox::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{
	// TODO: Add your code to draw the specified item
	if ((int)lpDIS->itemID < 0)
		return; 

	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	COLORREF crText;
	CString sText;
	COLORREF crNorm;
	HICON icon;
	switch(lpDIS->itemData)
	{
		case M_OK:
			crNorm=RGB(0,128,0);
			icon=AfxGetApp()->LoadIcon(IDI_ICON_OK);
			break;
		case M_ERROR:
			crNorm=RGB(255,0,0);
			icon=AfxGetApp()->LoadIcon(IDI_ICON_ERROR);
			break;
		case M_WARING:
			crNorm=RGB(0,0,255);
			icon=AfxGetApp()->LoadIcon(IDI_ICON_WARING);
			break;
	}


	// 字符串颜色
	COLORREF crHilite = RGB(255-GetRValue(crNorm), 255-GetGValue(crNorm), 255-GetBValue(crNorm));
	CRect rectBK(lpDIS->rcItem.left+22,lpDIS->rcItem.top,lpDIS->rcItem.right+18,lpDIS->rcItem.bottom);


	// 如果被选中，使用高亮色会矩形
	if ((lpDIS->itemState & ODS_SELECTED) &&
		 (lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		CBrush brush(crNorm);
		pDC->FillRect(rectBK, &brush);
	}

	// 如果取消选中，恢复
	if (!(lpDIS->itemState & ODS_SELECTED) &&	(lpDIS->itemAction & ODA_SELECT))
	{
		CBrush brush(::GetSysColor(COLOR_WINDOW));
		pDC->FillRect(rectBK, &brush);
	}	 	

	// 绘制焦点矩形
	if ((lpDIS->itemAction & ODA_FOCUS) && (lpDIS->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDIS->rcItem); 

	// 取消焦点矩形
	if ((lpDIS->itemAction & ODA_FOCUS) &&	!(lpDIS->itemState & ODS_FOCUS))
		pDC->DrawFocusRect(&lpDIS->rcItem); 


	// 透明背景
	int nBkMode = pDC->SetBkMode(TRANSPARENT);

	
	if (lpDIS->itemData)		
	{
		if (lpDIS->itemState & ODS_SELECTED)
			crText = pDC->SetTextColor(crHilite);
		else if (lpDIS->itemState & ODS_DISABLED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		else
			crText = pDC->SetTextColor(crNorm);
	}
	
	else
	{
		if (lpDIS->itemState & ODS_SELECTED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
		else if (lpDIS->itemState & ODS_DISABLED)
			crText = pDC->SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
		else
			crText = pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}


	// 显示字符串
	GetText(lpDIS->itemID, sText);
	CRect rect = lpDIS->rcItem;

	// 字符格式
	UINT nFormat = DT_LEFT | DT_SINGLELINE | DT_VCENTER;
	if (GetStyle() & LBS_USETABSTOPS)
		nFormat |= DT_EXPANDTABS;
	

	pDC->DrawText(sText, -1, &rectBK, nFormat | DT_CALCRECT&DT_CENTER);
	pDC->DrawText(sText, -1, &rectBK, nFormat);
	DrawIconEx(lpDIS->hDC,rect.left+2,rect.top+1,icon,16,16,0,NULL, DI_NORMAL | DI_COMPAT);
	pDC->SetTextColor(crText); 
	pDC->SetBkMode(nBkMode);		
}

void CColorListBox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your code to determine the size of specified item
	//设置每一项的高度
	lpMeasureItemStruct->itemHeight = ::GetSystemMetrics(SM_CYMENU);
	
}

int CColorListBox::AddMsg(CString lpszItem,DWORD info)
{
	int nItem = AddString(lpszItem);
	if (nItem >= 0)
		SetItemData(nItem,info);
	int numList=GetCount()-1;
	SetTopIndex(numList);
	SetCurSel(numList);
	//水平滚动
	int max_width=0;
	CSize sz;
	CClientDC dc(this);
	for(int i=0;i<GetCount();i++)
	{
		GetText(i,lpszItem);
		sz=dc.GetTextExtent(lpszItem);
		if(max_width<sz.cx)
			max_width=sz.cx;
	}
	SendMessage(LB_SETHORIZONTALEXTENT,max_width,0);

	return nItem;
}
