// UsbKey.h : main header file for the USBKEY application
//

#if !defined(AFX_USBKEY_H__41C2EAF4_A86A_4078_B274_DD0AD886E153__INCLUDED_)
#define AFX_USBKEY_H__41C2EAF4_A86A_4078_B274_DD0AD886E153__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsbKeyApp:
// See UsbKey.cpp for the implementation of this class
//

class CUsbKeyApp : public CWinApp
{
public:
	CUsbKeyApp();
	EPAS_HANDLE m_handle;
	bool m_VerifySo,m_VerifyUser;//��֤����Ա��ʾ
	CString m_SoPin;//����Ա����
//	bool m_PubKey,m_PriKey;//���Ź�Կ��˽Կ��ʾ
//	bool m_ExternKey;//�Ƿ�ʹ���ⲿ֤��
	bool m_ChangeKey;//��Կ֤���Ƿ�ı���

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsbKeyApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsbKeyApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBKEY_H__41C2EAF4_A86A_4078_B274_DD0AD886E153__INCLUDED_)
