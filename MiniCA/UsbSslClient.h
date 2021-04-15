#if !defined(AFX_USBSSLCLIENT_H__8BCB9C4E_9FD5_4F8A_B4D9_50D530BB0D51__INCLUDED_)
#define AFX_USBSSLCLIENT_H__8BCB9C4E_9FD5_4F8A_B4D9_50D530BB0D51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbSslClient.h : header file
//
#include "ColorListBox.h"
#include "SslClientSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbSslClient dialog

class CUsbSslClient : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbSslClient)

// Construction
public:
	CUsbSslClient();
	~CUsbSslClient();

// Dialog Data
	//{{AFX_DATA(CUsbSslClient)
	enum { IDD = IDD_PROPPAGE_SSLCLIENT };
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbSslClient)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbSslClient)
	afx_msg void OnBConnect();
	afx_msg void OnBDiscon();
	afx_msg void OnBSend();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_ConnectTime;
	CSslClientSocket m_clientSock;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBSSLCLIENT_H__8BCB9C4E_9FD5_4F8A_B4D9_50D530BB0D51__INCLUDED_)
