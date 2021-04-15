// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A80D7EA4_BB4A_4622_A06C_5B59E8EC712D__INCLUDED_)
#define AFX_STDAFX_H__A80D7EA4_BB4A_4622_A06C_5B59E8EC712D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
void SockMsgBox(DWORD error);
void GetSockError(DWORD error,char * out);
#include "Sslstruct.h"
#include "..\UsbKeyApi.h"


#include <afxsock.h>		// MFC socket extensions

#define M_OK		10000
#define M_ERROR		20000
#define M_WARING	30000


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A80D7EA4_BB4A_4622_A06C_5B59E8EC712D__INCLUDED_)
