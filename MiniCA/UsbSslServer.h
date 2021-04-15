#if !defined(AFX_USBSSLSERVER_H__033F6EC6_5155_4DED_A014_63E2F6677705__INCLUDED_)
#define AFX_USBSSLSERVER_H__033F6EC6_5155_4DED_A014_63E2F6677705__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbSslServer.h : header file
//
#include "ColorListBox.h"
#include "SslServerSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbSslServer dialog

class CUsbSslServer : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbSslServer)

// Construction
public:
	void CloseAllClient();
	CUsbSslServer();
	~CUsbSslServer();
	CSslServerSocket  m_ListeSock;
	CObList	m_ObSock;//连接列表

// Dialog Data
	//{{AFX_DATA(CUsbSslServer)
	enum { IDD = IDD_PROPPAGE_SSLSERVER };
	CColorListBox	m_ListC;
	CIPAddressCtrl	m_server_IP;
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbSslServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbSslServer)
	afx_msg void OnListen();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnCheck();
	afx_msg void OnBGetc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool server;//启动、关闭
	int m_type;//是否要求客户证书
	int GetIpAddress(const CString & sHostName,CString & sIpAddress);
	int GetLocalHostName(CString &sHostName);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBSSLSERVER_H__033F6EC6_5155_4DED_A014_63E2F6677705__INCLUDED_)
