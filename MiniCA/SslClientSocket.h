#if !defined(AFX_SSLCLIENTSOCKET_H__E2CC9DFD_E9AC_4564_AB55_EFD930215D2B__INCLUDED_)
#define AFX_SSLCLIENTSOCKET_H__E2CC9DFD_E9AC_4564_AB55_EFD930215D2B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SslClientSocket.h : header file
//
#include "ColorListBox.h"


/////////////////////////////////////////////////////////////////////////////
// CSslClientSocket command target

class CSslClientSocket : public CAsyncSocket
{
// Attributes
public:
	CColorListBox *	m_pList;
	BOOL SockConnect(SSL_METHOD *meth,char *certfile,int certlen, char *keyfile,
		int keylen,		char * cafile, char * capath,CColorListBox * plist,
		LPCTSTR lpszHostAddress, UINT nHostPort,char * out);//普通套接字连接
	int SSlConnect(stuSERVERINFO * stu,char * out);//ssl套接字连接

// Operations
public:
	CSslClientSocket();
	virtual ~CSslClientSocket();
	SSL * m_Ssl;

// Overrides
public:
	int SSlReceive(char * buf,int len);
	int SSlSend(char * buf,int len);
	void SSlShouDown();
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSslClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSslClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	int Rand(const char *file,int dont_warn,char * outMsg);
	void GetPeerInfo(SSL * ssl,stuSERVERINFO * stu);//得到对方信息
	X509 * LoadCert(char * cert,int certlen,char * outMsg);//枚举DER/PEM格式
	EVP_PKEY * LoadKey(char * key,int keylen,char * pass,char * outMsg);//枚举DER/PEM格式

private:
	SSL_CTX * m_Ctx;
	EVP_PKEY * load_key(BIO *bio, int format, char *pass,char * outMsg);
	X509 * load_cert(BIO *cert, int format,char * pwd,char * outMsg);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSLCLIENTSOCKET_H__E2CC9DFD_E9AC_4564_AB55_EFD930215D2B__INCLUDED_)
