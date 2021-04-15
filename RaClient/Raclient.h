// Raclient.h : main header file for the RACLIENT application
//

#if !defined(AFX_RACLIENT_H__A7853BED_C9A3_4332_872A_0D35049515DC__INCLUDED_)
#define AFX_RACLIENT_H__A7853BED_C9A3_4332_872A_0D35049515DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "SslClientSocket.h"


#define UNIQE_NAME "{1AB792D6-EEF2-4528-9A84-91356811E7A4}"//定义唯一的，以免冲突
#define ra_MSG "{D48CA923-4925-41cb-8F56-ABAAAFCEF787}"

/////////////////////////////////////////////////////////////////////////////
// CRaclientApp:
// See Raclient.cpp for the implementation of this class
//
class CRaclientApp : public CWinApp
{
public:
	CSslClientSocket m_SslSocket;
	CRaclientApp();
	bool m_candisconnect,m_canconnect;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRaclientApp)
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	HMENU m_hMDIMenu;
	HMENU m_hMenu;
	HACCEL m_hMDIAccel;
	HANDLE m_hOneInstance;
	
	CBitmap m_bmp1,m_bmp2,m_bmp3,m_bmp4;
public:
	void Connect();
	void Discon();
	//{{AFX_MSG(CRaclientApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnSysDisconnect();
	afx_msg void OnUpdateSysDisconnect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RACLIENT_H__A7853BED_C9A3_4332_872A_0D35049515DC__INCLUDED_)
