#if !defined(AFX_SSLCLIENTSOCKET_H__4766C0AD_1F90_4315_A1D4_008ED8112A3F__INCLUDED_)
#define AFX_SSLCLIENTSOCKET_H__4766C0AD_1F90_4315_A1D4_008ED8112A3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SslClientSocket.h : header file
//
#include <openssl/ssl.h>
#include <openssl/pkcs12.h>
#include "..\ca.h"
#define DER			    1 //FORMAT_ASN1
#define PEM			    3	/*定义格式*/
#define P12				5

#define MAXBUF 16384	//一次性最大接收长度?

enum OPERTYPE//操作类型
{
	Input,//录入
	Audit,//审核
	Made,//制作
	MadeOK,//制作成功，只用于客户端
	Revoke,//作废
	MadeCrl,//制作黑名单
	FInputD,//查找录入---待审核
	FAuditD,//查找审核---待制作
	FMadeD,//查找制作 ---有效
	FRevokeD//查找作废---无效
};

struct stuRA//接受用结构
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

struct stuCA//发送给服务器端用
{
	OPERTYPE Type;//操作类型
	char SQL[200];//SQL语句
	stuCA()
	{
		memset(this,0,sizeof(stuCA));
	}
};

struct stuLIST//链表
{
	int ID;//证书ID
	stuCA CA;//内容
	stuLIST()
	{
		memset(this,0,sizeof(stuLIST));
	}
};
/////////////////////////////////////////////////////////////////////////////
// CSslClientSocket command target

class CSslClientSocket : public CAsyncSocket
{
// Attributes
public:
	BOOL SockConnect(SSL_METHOD *meth,char *certfile,int certlen, char *keyfile,
		int keylen,	char * cafile, char * capath,LPCTSTR lpszHostAddress,
		UINT nHostPort,char * out);//普通套接字连接
	int SSlConnect(char * out);//ssl套接字连接
	int SSlReceive(char * buf,int len);
	int SSlSend(char * buf,int len);
	void SSlShouDown();
	SSL * m_Ssl;
	CListCtrl * m_AuditList, * m_MadeList, * m_RevokeList;
// Operations
public:
	CSslClientSocket();
	virtual ~CSslClientSocket();

// Overrides
public:
	BOOL GetComCount();//链表中是否有元素
	void AddCommand(stuLIST * LIST);//加入链表
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSslClientSocket)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CSslClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	X509 * LoadCert(char * cert,int certlen,char * outMsg);//枚举DER/PEM格式
	EVP_PKEY * LoadKey(char * key,int keylen,char * pass,char * outMsg);//枚举DER/PEM格式
	void InsertList(CListCtrl * pList,stuRA * pRa);
	SSL_CTX * m_Ctx;
	EVP_PKEY * load_key(BIO *bio, int format, char *pass,char * outMsg);
	X509 * load_cert(BIO *cert, int format,char * pwd,char * outMsg);
	BOOL m_ifCert,m_ifCrl;//是否接受证书、CRL
	char * m_pCertKey;//证书
	int m_CertLen,m_KeyLen;//证书长度
	int m_MaxCount;//最大纪录条数,用于进度条最大值
	CString m_CertID;
	CPtrList  m_ComList;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSLCLIENTSOCKET_H__4766C0AD_1F90_4315_A1D4_008ED8112A3F__INCLUDED_)
