#if !defined(AFX_SSLSERVERSOCKET_H__743B3028_F922_4137_9156_47A3BE019520__INCLUDED_)
#define AFX_SSLSERVERSOCKET_H__743B3028_F922_4137_9156_47A3BE019520__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SslServerSocket.h : header file
//
#include "ColorListBox.h"
#include "..\ca.h"


/////////////////////////////////////////////////////////////////////////////
// CSslServerSocket command target
#pragma warning(disable:4146) 
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","adoEOF")

class CSslServerSocket : public CAsyncSocket
{
// Attributes
public:
	SSL_CTX * InitCtx(SSL_METHOD *meth,char *certfile,int certlen, char *keyfile,int keylen,
			char * cafile, char * capath,int VerType,CColorListBox * plist,CObList	* pObSock/*连接列表*/,
			_ConnectionPtr pConnection/*数据库连接*/,char * out);
	BOOL CreateLisenSock( UINT nSocketPort = 0, long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
	int SSlReceive(char * buf,int len);
	int SSlSend(char * buf,int len);
	void SSlShouDown();
	CSslServerSocket * m_pSocket;//接受
// Operations
public:
	CSslServerSocket();
	virtual ~CSslServerSocket();
// Overrides
public:
	CSslServerSocket(int type);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSslServerSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSslServerSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	int Rand(const char *file,int dont_warn,char * outMsg);
	X509 * LoadCert(char * cert,int certlen,char * outMsg);//枚举DER/PEM格式
	EVP_PKEY * LoadKey(char * key,int keylen,char * pass,char * outMsg);//枚举DER/PEM格式
	BOOL GetPeerInfo(SSL * ssl,stuCLIENTINFO * stu);
	stuCLIENTINFO m_CLIENTINFO;
private:
	static char * NewCrlMem(UINT len);
	CObList	* m_pObSock;//连接列表
	CColorListBox *	m_pList;
	_ConnectionPtr m_pConnection;
	SSL_CTX * m_Ctx;
	SSL * m_Ssl;
	int m_type;//类型---www还是ra
	int m_Rcount;//纪录条数
	X509 * load_cert(BIO *cert, int format,char * pwd,char * outMsg);
	EVP_PKEY * load_key(BIO *bio, int format, char *pass,char * outMsg);
	int static Verify(int ok, X509_STORE_CTX *ctx);
	void SSlWww(char * file,int len, char *out);//发送网页信息
	void DisplayError(_com_error &e);

	enum OPERTYPE//操作类型
	{
		Input,//录入
		Audit,//审核
		Made,//制作
		MadeOK,//制作成功，只用于客户端
		Revoke,//作废
		MadeCrl,//制作黑名单
		FInputD,//查找已经录入---待审核
		FAuditD,//查找已经审核---待制作
		FMadeD,//查找已经制作 ---有效
		FRevokeD//查找已经作废---无效
	};

	struct stuRA//客户端接受用结构
	{	
		OPERTYPE Type;//操作类型
		BOOL State;//操作状态 成功，失败
		int ID;//证书ID
		int CertL;//公钥长度
		int KeyL;//私钥长度
		stuSUBJECT SUBJECT;//申请者信息
		char Time[12];//操作时间2003-12-06
		stuRA()
		{
			memset(this,0,sizeof(stuRA));
		}
	};

	struct stuCA//服务器接收用
	{
		OPERTYPE Type;//操作类型
		char SQL[200];//SQL语句
		stuCA()
		{
			memset(this,0,sizeof(stuCA));
		}
	};
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSLSERVERSOCKET_H__743B3028_F922_4137_9156_47A3BE019520__INCLUDED_)
