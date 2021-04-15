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
			char * cafile, char * capath,int VerType,CColorListBox * plist,CObList	* pObSock/*�����б�*/,
			_ConnectionPtr pConnection/*���ݿ�����*/,char * out);
	BOOL CreateLisenSock( UINT nSocketPort = 0, long lEvent = FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE );
	int SSlReceive(char * buf,int len);
	int SSlSend(char * buf,int len);
	void SSlShouDown();
	CSslServerSocket * m_pSocket;//����
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
	X509 * LoadCert(char * cert,int certlen,char * outMsg);//ö��DER/PEM��ʽ
	EVP_PKEY * LoadKey(char * key,int keylen,char * pass,char * outMsg);//ö��DER/PEM��ʽ
	BOOL GetPeerInfo(SSL * ssl,stuCLIENTINFO * stu);
	stuCLIENTINFO m_CLIENTINFO;
private:
	static char * NewCrlMem(UINT len);
	CObList	* m_pObSock;//�����б�
	CColorListBox *	m_pList;
	_ConnectionPtr m_pConnection;
	SSL_CTX * m_Ctx;
	SSL * m_Ssl;
	int m_type;//����---www����ra
	int m_Rcount;//��¼����
	X509 * load_cert(BIO *cert, int format,char * pwd,char * outMsg);
	EVP_PKEY * load_key(BIO *bio, int format, char *pass,char * outMsg);
	int static Verify(int ok, X509_STORE_CTX *ctx);
	void SSlWww(char * file,int len, char *out);//������ҳ��Ϣ
	void DisplayError(_com_error &e);

	enum OPERTYPE//��������
	{
		Input,//¼��
		Audit,//���
		Made,//����
		MadeOK,//�����ɹ���ֻ���ڿͻ���
		Revoke,//����
		MadeCrl,//����������
		FInputD,//�����Ѿ�¼��---�����
		FAuditD,//�����Ѿ����---������
		FMadeD,//�����Ѿ����� ---��Ч
		FRevokeD//�����Ѿ�����---��Ч
	};

	struct stuRA//�ͻ��˽����ýṹ
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

	struct stuCA//������������
	{
		OPERTYPE Type;//��������
		char SQL[200];//SQL���
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
