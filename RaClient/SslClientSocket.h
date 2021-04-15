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
#define PEM			    3	/*�����ʽ*/
#define P12				5

#define MAXBUF 16384	//һ���������ճ���?

enum OPERTYPE//��������
{
	Input,//¼��
	Audit,//���
	Made,//����
	MadeOK,//�����ɹ���ֻ���ڿͻ���
	Revoke,//����
	MadeCrl,//����������
	FInputD,//����¼��---�����
	FAuditD,//�������---������
	FMadeD,//�������� ---��Ч
	FRevokeD//��������---��Ч
};

struct stuRA//�����ýṹ
{	
	OPERTYPE Type;//��������
	BOOL State;//����״̬ �ɹ���ʧ��
	int ID;//֤��ID
	int CertL;//��Կ����
	int KeyL;//˽Կ����
	stuSUBJECT SUBJECT;//��������Ϣ
	char Time[12];//����ʱ��2003-12-06
	stuRA()
	{
		memset(this,0,sizeof(stuRA));
	}
};

struct stuCA//���͸�����������
{
	OPERTYPE Type;//��������
	char SQL[200];//SQL���
	stuCA()
	{
		memset(this,0,sizeof(stuCA));
	}
};

struct stuLIST//����
{
	int ID;//֤��ID
	stuCA CA;//����
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
		UINT nHostPort,char * out);//��ͨ�׽�������
	int SSlConnect(char * out);//ssl�׽�������
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
	BOOL GetComCount();//�������Ƿ���Ԫ��
	void AddCommand(stuLIST * LIST);//��������
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
	X509 * LoadCert(char * cert,int certlen,char * outMsg);//ö��DER/PEM��ʽ
	EVP_PKEY * LoadKey(char * key,int keylen,char * pass,char * outMsg);//ö��DER/PEM��ʽ
	void InsertList(CListCtrl * pList,stuRA * pRa);
	SSL_CTX * m_Ctx;
	EVP_PKEY * load_key(BIO *bio, int format, char *pass,char * outMsg);
	X509 * load_cert(BIO *cert, int format,char * pwd,char * outMsg);
	BOOL m_ifCert,m_ifCrl;//�Ƿ����֤�顢CRL
	char * m_pCertKey;//֤��
	int m_CertLen,m_KeyLen;//֤�鳤��
	int m_MaxCount;//����¼����,���ڽ��������ֵ
	CString m_CertID;
	CPtrList  m_ComList;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SSLCLIENTSOCKET_H__4766C0AD_1F90_4315_A1D4_008ED8112A3F__INCLUDED_)
