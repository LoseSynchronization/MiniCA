#if !defined(AFX_USBRASERVER_H__5BC63D2B_9DFE_4DD6_8BCF_FB200739786E__INCLUDED_)
#define AFX_USBRASERVER_H__5BC63D2B_9DFE_4DD6_8BCF_FB200739786E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UsbRaServer.h : header file
//
#include "ColorListBox.h"
#include "SslServerSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CUsbRaServer dialog

class CUsbRaServer : public CPropertyPage
{
	DECLARE_DYNCREATE(CUsbRaServer)

// Construction
public:
	void CloseAllClient();
	CUsbRaServer();
	~CUsbRaServer();
	_ConnectionPtr m_pConnection;
	void DisplayError(_com_error &e);
	CObList	m_ObSock;//连接列表

// Dialog Data
	//{{AFX_DATA(CUsbRaServer)
	enum { IDD = IDD_PROPPAGE_RASERVER };
	CIPAddressCtrl	m_server_IP;
	CColorListBox	m_ListC;
	CColorListBox	m_List;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CUsbRaServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CUsbRaServer)
	afx_msg void OnListen();
	virtual BOOL OnInitDialog();
	afx_msg void OnBGetc();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CSslServerSocket * m_pListeSock;//构造函数带参数
private:
	bool server;//启动、关闭
	int GetIpAddress(const CString & sHostName,CString & sIpAddress);
	int GetLocalHostName(CString &sHostName);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USBRASERVER_H__5BC63D2B_9DFE_4DD6_8BCF_FB200739786E__INCLUDED_)
