// SslClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "Raclient.h"
#include "SslClientSocket.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSslClientSocket

CSslClientSocket::CSslClientSocket()
{
	m_Ctx=NULL;
	m_Ssl=NULL;
	m_AuditList=NULL;
	m_MadeList=NULL;
	m_RevokeList=NULL;
	m_ifCert=false;
	m_ifCrl=false;
	m_MaxCount=0;
}

CSslClientSocket::~CSslClientSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSslClientSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSslClientSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSslClientSocket member functions
X509 * CSslClientSocket::load_cert(BIO *cert/*����BIO*/, int format/*��ʽ*/,char * pwd,/*P12����*/char * outMsg)
{
	ASN1_HEADER *ah=NULL;
	BUF_MEM *buf=NULL;
	X509 *x=NULL;

	if 	(format == DER)
		x=d2i_X509_bio(cert,NULL);
	else if (format == PEM)
		x=PEM_read_bio_X509(cert,NULL,NULL,NULL);//PEM_read_bio_X509_AUX
	else if (format == P12)
	{
		PKCS12 *p12 = d2i_PKCS12_bio(cert, NULL);
		PKCS12_parse(p12, pwd, NULL, &x, NULL);
		PKCS12_free(p12);
		p12 = NULL;
	}
	else
	{
		sprintf(outMsg,"bad input format specified for input cert\n");
		goto end;
	}
end:
	if (x == NULL)
	{
		sprintf(outMsg,"unable to load certificate\n");
	}
	if (ah != NULL) ASN1_HEADER_free(ah);
	if (buf != NULL) BUF_MEM_free(buf);
	return(x);
}

X509 * CSslClientSocket::LoadCert(char * cert,int certlen,char * outMsg)//ö��DER/PEM��ʽ
{
	BIO * in=NULL;
	X509 * x509=NULL;

	if(certlen==0)//����Ϊ�����ļ�
	{
		if((in=BIO_new_file(cert, "r")) == NULL)
		{
			sprintf(outMsg,"open CA certificate file error");
			return NULL;
		}
	}
	else//����Ϊ�ڴ����ļ�
	{
		if((in=BIO_new_mem_buf(cert,certlen))== NULL)//ֻ������
		{
			sprintf(outMsg,"Make Mem Bio Error");
			return NULL;
		}
	}
	if((x509=load_cert(in,DER,NULL,outMsg))==NULL)//����DER
	{
		BIO_reset(in);//�ָ�bio
		x509=load_cert(in,PEM,NULL,outMsg);//����PEM
	}
	if (in != NULL) BIO_free(in);
	return x509;
}

EVP_PKEY * CSslClientSocket::load_key(BIO *bio, int format, char *pass,char * outMsg)
{
	EVP_PKEY *pkey=NULL;

	if (format == DER)
	{
		pkey=d2i_PrivateKey_bio(bio, NULL);
	}
	else if (format == PEM)
	{
		pkey=PEM_read_bio_PrivateKey(bio,NULL,NULL,pass);
	}
	else if (format == P12)
	{
		PKCS12 *p12 = d2i_PKCS12_bio(bio, NULL);
		PKCS12_parse(p12, pass, &pkey, NULL, NULL);
		PKCS12_free(p12);
		p12 = NULL;
	}
	else
	{
		sprintf(outMsg,"bad input format specified for key\n");
		goto end;
	}
end:
	if (pkey == NULL)
		sprintf(outMsg,"unable to load Private Key\n");
	return(pkey);
}

EVP_PKEY * CSslClientSocket::LoadKey(char * key,int keylen,char * pass,char * outMsg)
{
	EVP_PKEY *pkey=NULL;
	BIO * in=NULL;

	if(keylen==0)//����Ϊ�����ļ�
	{
		if((in=BIO_new_file(key, "r")) == NULL)
		{
			sprintf(outMsg,"open CA certificate file error");
			return NULL;
		}
	}
	else//����Ϊ�ڴ����ļ�
	{
		if((in=BIO_new_mem_buf(key,keylen))== NULL)//ֻ������
		{
			sprintf(outMsg,"Make Mem Bio Error");
			return NULL;
		}
	}

	if((pkey=load_key(in,DER,pass,outMsg))==NULL)//����DER
	{
		BIO_reset(in);//BIO�ǿɶ�д�ģ���ô��BIO�������ݶ��ᱻ��գ�
						//�����BIO��ֻ���ģ���ô�ò���ֻ��򵥽�ָ
						//��ָ��ԭʼλ�ã���������ݿ����ٶ�.
		pkey=load_key(in,PEM,pass,outMsg);//����PEM
	}
	if (in != NULL) BIO_free(in);
	return pkey;
}

BOOL CSslClientSocket::SockConnect(SSL_METHOD *meth,char *certfile,int certlen, char *keyfile,int keylen,
		char * cafile, char * capath,LPCTSTR lpszHostAddress, UINT nHostPort,char * out)
{
	EVP_PKEY *pkey=NULL;
	X509 *x509=NULL;
	CString str;
	unsigned long l=1;
	BIO * sbio=NULL;
	struct hostent *hp;
    struct sockaddr_in addr;
    int sock,i=0;

//	m_pList=plist;/////////////////////

	OpenSSL_add_ssl_algorithms();

    m_Ctx=SSL_CTX_new(meth);
	if (m_Ctx == NULL)
	{
		strcpy(out,"Create ctx error");
		return FALSE;
	}
	SSL_CTX_set_options(m_Ctx,SSL_OP_ALL);
	
	pkey=LoadKey(keyfile,keylen,NULL,out);
	
	if (pkey == NULL)
	{
		sprintf(out,"unable to load CA private key\n");
		m_Ctx=NULL;
		goto err;
	}
	
    if(!(SSL_CTX_use_PrivateKey(m_Ctx,pkey)))
	{
		strcpy(out,"adds private key to ctx error");
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
		goto err;
	}
	
	x509=LoadCert(certfile,certlen,out);
	if (x509 == NULL)
	{
		sprintf(out,"unable to load CA certificate\n");
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
		goto err;
	}
	
    if(!(SSL_CTX_use_certificate(m_Ctx,x509)))
	{
		strcpy(out,"loads certificate into ctx error");
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
		goto err;
	}
	
	if (!SSL_CTX_check_private_key(m_Ctx))
	{
		strcpy(out,"Private key does not match the certificate public key");
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
		goto err;
	}
	
    /* Load the CAs we trust*/
   if(!(SSL_CTX_load_verify_locations(m_Ctx,cafile,/*capath*/NULL)))
	{
		strcpy(out,"Couldn't read CA list");
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
		goto err;
	}
	SSL_CTX_set_verify_depth(m_Ctx,1);
    SSL_CTX_set_client_CA_list(m_Ctx,SSL_load_client_CA_file(cafile));
    m_Ssl=SSL_new(m_Ctx);
	if(m_Ssl==NULL)
	{
		strcpy(out,"Make SSL Error");
		goto err;
	}
    /* Load randomness */
//	Rand(NULL,1,out);

	/*���ӷ�����*/

    if(!(hp=gethostbyname(lpszHostAddress)))
	{
		strcpy(out,"Couldn't resolve host");
		return FALSE;
	}
    memset(&addr,0,sizeof(addr));
    addr.sin_addr=*(struct in_addr*)hp->h_addr_list[0];
    addr.sin_family=AF_INET;
    addr.sin_port=htons(nHostPort);
	
	sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if (sock == INVALID_SOCKET) 
	{
		strcpy(out,"create socket error"); 
		return FALSE;
	}
	
	i=setsockopt(sock,SOL_SOCKET,SO_KEEPALIVE,(char *)&i,sizeof(i));
	if (i < 0)
	{
		strcpy(out,"setsockopt error"); 
		return FALSE;
	}
	
	if (connect(sock,(struct sockaddr *)&addr,sizeof(addr)) == -1)
	{
		shutdown(sock,2);
		closesocket(sock);
		strcpy(out,"connect error"); 
		return FALSE; 
	}

    /* Connect the SSL socket */
	if (BIO_socket_ioctl(sock,FIONBIO,&l) < 0)
	{
		strcpy(out,"io set error");
		shutdown(sock,2);
		closesocket(sock);
		SSlShouDown();
		return FALSE;
	}
	
    sbio=BIO_new_socket(sock,BIO_NOCLOSE);
    SSL_set_bio(m_Ssl,sbio,sbio);
	SSL_set_connect_state(m_Ssl);
	Attach(sock, FD_CLOSE);
	str.Format("%d���������%s���ȴ�����....",m_hSocket,inet_ntoa(addr.sin_addr));
//	m_pList->AddMsg(str,M_WARING);
    return TRUE;

err:
	EVP_PKEY_free(pkey);
	X509_free(x509);
	SSlShouDown();
	return FALSE;
}

int CSslClientSocket::SSlConnect(char * out)
{
	if(m_Ssl==NULL)
	{
		strcpy("SSLû����ȷ��ʼ��",out);
		return -1;
	}
	int err=0;
	if ((err = SSL_connect(m_Ssl)) <= 0)
	{
		if (BIO_sock_should_retry(err))
		{
			return 0;//����
		}
		else 
		{
			strcpy(out,"SSL����ʧ��");//ERR_clear_error
			return -1;
		}
	}
	return 1;
}

void CSslClientSocket::SSlShouDown()
{
	if(m_Ctx!=NULL)
	{
		SSL_CTX_free(m_Ctx);
		m_Ctx=NULL;
	}
	if(m_Ssl!=NULL)
	{
		SSL_shutdown(m_Ssl);
		SSL_free(m_Ssl);
		m_Ssl=NULL;
	}
	stuLIST * LIST=NULL;
	for(;!m_ComList.IsEmpty();)
	{
		LIST=(stuLIST *)m_ComList.RemoveHead();
		delete LIST;
	}
	ShutDown(2);
	Close();
}

int CSslClientSocket::SSlSend(char *buf, int len)
{
	if(m_Ssl==NULL)
		return -1;
	int k=0;//��������
	int offect=0;//ƫ��
	for(;0!=len;)//maximum record size of 16kB for SSLv3/TLSv1
	{
		k = SSL_write(m_Ssl,buf+offect,len);
		if (k <= 0)
		{
			if (BIO_sock_should_retry(k))
			{
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(0,"SSlSend",M_WARING);
				Sleep(100);
				continue;
			}
		}
		offect+=k;//���յ�����
		len-=k;
	}
	AsyncSelect(FD_READ|FD_CLOSE);//ѡ���(����һ������һ��)
	return offect;
}

int CSslClientSocket::SSlReceive(char * buf, int len)
{
	int k=0;
	do
	{
		for(;;)
		{
			k = SSL_read(m_Ssl,buf,len);
			if (k <=0)
			{
				if (BIO_sock_should_retry(k))
				{
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(0,"SSlReceive",M_WARING);
					Sleep(100);
					continue;//����
				}
				return k;//�����˳�
			}
			break;//�ɹ�
		}
	}while (SSL_pending(m_Ssl));
	return k;
	/*����Է�һ���Է��͡�16k(16384),���ֻ���յ�16k,SSL_pending����0��
	   �������len<16k����SSL_pending���أ�16k-len)*/
}

void CSslClientSocket::InsertList(CListCtrl * pList,stuRA * pRa)
{
	if(pList==NULL)
	{
		AfxMessageBox("InsertList Error");
		return;
	}
	CString item;
	char buf[48]={0};//��󳤶�48
	item.Format("%d",pRa->ID);
	LVFINDINFO Info;
	Info.flags=LVFI_STRING;
	Info.psz=item;
	if(pList->FindItem(&Info,-1)!=-1)//����
		return;
	pList->InsertItem(0,item);//ID
	strncpy(buf,(char *)pRa->SUBJECT.CN,sizeof(pRa->SUBJECT.CN));
	pList->SetItemText(0,1,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.C,sizeof(pRa->SUBJECT.C));
	pList->SetItemText(0,2,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.ST,sizeof(pRa->SUBJECT.ST));
	pList->SetItemText(0,3,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.L,sizeof(pRa->SUBJECT.L));
	pList->SetItemText(0,4,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.O,sizeof(pRa->SUBJECT.O));
	pList->SetItemText(0,5,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.OU,sizeof(pRa->SUBJECT.OU));
	pList->SetItemText(0,6,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.MAIL,sizeof(pRa->SUBJECT.MAIL));
	pList->SetItemText(0,7,buf);
	ZeroMemory(buf,48);
	strncpy(buf,(char *)pRa->SUBJECT.PMAIL,sizeof(pRa->SUBJECT.PMAIL));
	pList->SetItemText(0,8,buf);
	pList->SetItemText(0,9,pRa->Time);
	
}

void CSslClientSocket::OnReceive(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	if(!m_ifCert&&!m_ifCrl)
	{
		stuRA RA;//���ڽ��ܵĽṹ
		if(SSlReceive((char *)&RA,sizeof(stuRA))==0)//�Է��Ѿ��ر�
			return;
		else if(RA.Type==FInputD)//��ѯ�����֤��
		{
			if(RA.State)
			{
				if(RA.KeyL==1) //�ܼ�¼,��һ�η����ܼ�¼
				{
					CString str;
					str.Format("�����֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);
					if(RA.CertL==0)//0����¼
						return;
				}
				else if((RA.KeyL==-1)&&(1==RA.CertL))//�ܹ�һ����¼
				{
					CString str;
					str.Format("�����֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);

				}
				if(1==m_MaxCount)
					((CMainFrame *)AfxGetMainWnd())->SetPos(1);
				else if(RA.CertL!=m_MaxCount)//���������Ŀ
					((CMainFrame *)AfxGetMainWnd())->SetPos(RA.CertL+1);
				if(RA.KeyL==-1)//���һ��
				{
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,"��ѯ�����֤�����");
					m_AuditList->SetRedraw();
					((CMainFrame *)AfxGetMainWnd())->SetPos(m_MaxCount);
				}
				InsertList(m_AuditList,&RA);
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,"��ѯ�����֤��ʧ��",M_ERROR);
		}
		else if(RA.Type==FAuditD)//��ѯ������֤��
		{
			if(RA.State)
			{
				if(RA.KeyL==1) //�ܼ�¼,��һ�η����ܼ�¼
				{
					CString str;
					str.Format("������֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);
					if(RA.CertL==0)//0����¼
						return;
				}
				else if((RA.KeyL==-1)&&(1==RA.CertL))//�ܹ�һ����¼
				{
					CString str;
					str.Format("������֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);
				}
				if(1==m_MaxCount)//һ����¼
					((CMainFrame *)AfxGetMainWnd())->SetPos(1);
				else if(RA.CertL!=m_MaxCount)//���������Ŀ
					((CMainFrame *)AfxGetMainWnd())->SetPos(RA.CertL+1);
				if(RA.KeyL==-1)//���һ��
				{
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,"��ѯ������֤�����");
					m_MadeList->SetRedraw();
					((CMainFrame *)AfxGetMainWnd())->SetPos(m_MaxCount);
				}
				InsertList(m_MadeList,&RA);
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,"���մ�����֤����Ϣʧ��",M_ERROR);
		}
		else if(RA.Type==FMadeD)//��ѯ��Ч֤�飨�Ѿ���������δ����)
		{
			if(RA.State)
			{
				if(RA.KeyL==1) //�ܼ�¼,��һ�η����ܼ�¼
				{
					CString str;
					str.Format("��Ч֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);
					if(RA.CertL==0)//0����¼
						return;
				}
				else if((RA.KeyL==-1)&&(1==RA.CertL))//�ܹ�һ����¼
				{
					CString str;
					str.Format("��Ч֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);

				}
				if(1==m_MaxCount)
					((CMainFrame *)AfxGetMainWnd())->SetPos(1);
				else if(RA.CertL!=m_MaxCount)//���������Ŀ
					((CMainFrame *)AfxGetMainWnd())->SetPos(RA.CertL+1);
				if(RA.KeyL==-1)//���һ��
				{
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"��ѯ��Ч֤�����");
					m_RevokeList->SetRedraw();
					((CMainFrame *)AfxGetMainWnd())->SetPos(m_MaxCount);
				}
				InsertList(m_RevokeList,&RA);
			}
			
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"������Ч֤����Ϣʧ��",M_ERROR);
		}
		else if(RA.Type==FRevokeD)//��ѯ����֤��
		{
			if(RA.State)
			{
				if(RA.KeyL==1) //�ܼ�¼,��һ�η����ܼ�¼
				{
					CString str;
					str.Format("����֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,str);
					m_MaxCount=RA.CertL;
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,m_MaxCount);
					if(RA.CertL==0)//0����¼
						return;
				}
				else if((RA.KeyL==-1)&&(1==RA.CertL))//�ܹ�һ����¼
				{
					CString str;
					str.Format("����֤���¼����%d",RA.CertL);//�ܼ�¼��RA.CertL
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,str);
					((CMainFrame *)AfxGetMainWnd())->SetRange(0,1);
				}
				if(1==m_MaxCount)
					((CMainFrame *)AfxGetMainWnd())->SetPos(1);
				else if(RA.CertL!=m_MaxCount)//���������Ŀ
					((CMainFrame *)AfxGetMainWnd())->SetPos(RA.CertL+1);
				if(RA.KeyL==-1)//���һ��
				{
					((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"��ѯ����֤�����");
					m_RevokeList->SetRedraw();
					((CMainFrame *)AfxGetMainWnd())->SetPos(m_MaxCount);
				}

				InsertList(m_RevokeList,&RA);
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"��������֤����Ϣʧ��",M_ERROR);
		}
		if(RA.Type==Input)//����������
		{
			if(RA.State)
			{
				CString ID;
				ID.Format("֤��¼��ɹ���֤�����к�Ϊ%d",RA.ID);
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(0,ID);;
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(0,"֤��¼��ʧ��",M_ERROR);;
		}
		else if(RA.Type==Audit)//��˲������
		{
			if(RA.State)
			{
				CString item,Msg;
				item.Format("%d",RA.ID);
				LVFINDINFO Info;
				Info.flags=LVFI_STRING;
				Info.psz=item;
				int index=m_AuditList->FindItem(&Info,-1);
				m_AuditList->DeleteItem(index);
				Msg.Format("֤����˲������,֤��%d�Ѿ�ͨ�����",RA.ID);
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,Msg);

			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,"֤����˲���ʧ��",M_ERROR);;
		}
		else if(RA.Type==Made)//�����������
		{
			if(RA.State)
			{
				CString id,msg;
				id.Format("%d",RA.ID);
				m_CertLen=RA.CertL;
				m_KeyLen=RA.KeyL;
				m_CertID=id;
				m_pCertKey=new char[m_CertLen+m_KeyLen];//��̬����
				m_ifCert=true;//��һ�����ܵ�Ԫ��֤��
				msg.Format("����֤��������Ϣͷ�ɹ�,�ȴ�֤��%d������Ϣ......",RA.ID);
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,msg);;
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,"����֤��������Ϣͷʧ��",M_ERROR);;
		}
		else if(RA.Type==Revoke)//֤�����ϲ������
		{
			if(RA.State)
			{
				CString item,msg;
				item.Format("%d",RA.ID);
				LVFINDINFO Info;
				Info.flags=LVFI_STRING;
				Info.psz=item;
				int index=m_RevokeList->FindItem(&Info,-1);
				m_RevokeList->DeleteItem(index);
				msg.Format("֤�����ϲ������,֤��%d�Ѿ�����",RA.ID);
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,msg);
//				AsyncSelect(FD_CLOSE|FD_WRITE);

			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"֤�����ϲ���ʧ��",M_ERROR);;
		}
		else if(RA.Type==MadeCrl)//����crl
		{
			if(RA.State)
			{
				m_CertLen=RA.CertL;
				m_pCertKey=new char[m_CertLen];//��̬����
				m_ifCrl=true;//��һ�����ܵ�Ԫ��֤��
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,"����CRL������Ϣͷ�ɹ�,�ȴ�CRL������Ϣ......");;
			}
			else
				((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,"����CRL������Ϣʧ��",M_ERROR);;
		}		
	}
	else if(m_ifCert)//����֤��
	{

		SSlReceive(m_pCertKey,m_CertLen+m_KeyLen);
		CString info;
		info.Format("����֤��%s������Ϣ�ɹ�,����֤��......",m_CertID);
		((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,info);

		info.Format("%s\\%scert.pem",((CMainFrame *)AfxGetMainWnd())->m_PathCert,m_CertID);
		FILE * cert=fopen(info,"w");
		if(cert==NULL)
		{
			CString strerr;
			strerr.Format("���湫Կ%s����",m_CertID);
			((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,strerr);
			return;
		}

		fwrite(m_pCertKey,sizeof(char),m_CertLen,cert);
		fclose(cert);
		cert=NULL;
		info.Format("%s\\%skey.pem",((CMainFrame *)AfxGetMainWnd())->m_PathCert,m_CertID);
		cert=fopen(info,"w");
		if(cert==NULL)
		{
			CString strerr;
			strerr.Format("����˽Կ%s����",m_CertID);
			((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,strerr);
			return;
		}
		fwrite(m_pCertKey+m_CertLen,sizeof(char),m_KeyLen,cert);
		fclose(cert);
		cert=NULL;

		info.Format("����֤��%s�ɹ�",m_CertID);
		((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,info);

		m_ifCert=false;//��һ��Ԫ����֤��
		
		LVFINDINFO Info;
		Info.flags=LVFI_STRING;
		Info.psz=m_CertID;
		int index=m_MadeList->FindItem(&Info,-1);
		m_MadeList->DeleteItem(index);
		delete [] m_pCertKey;

		CString query;
		query.Format("Select ID,CERTSTATE,MADETIME From CERTLIST Where ID=%s",m_CertID);

		stuCA CA;
		CA.Type=MadeOK;
		strcpy(CA.SQL,query);
		if(SSlSend((char *)&CA,sizeof(CA))>0)
		{
			info.Format("����֤��%s����ȷ����Ϣ�ɹ�",m_CertID);
			((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,info);
		}
		else
		{
			info.Format("����֤��%s����ȷ����Ϣʧ��",m_CertID);
			((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,info,M_ERROR);
		}
	}
	else//crl
	{
		memset(m_pCertKey,0,m_CertLen);
		for(int offect=0,len=0;offect!=m_CertLen;offect+=len)//��������ֻ�����ﳤ�ȿ���>16k
		{
			len=SSlReceive(m_pCertKey+offect,m_CertLen-offect);
		}
		((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"����CRL������Ϣ�ɹ�,����CRL......");;
		CString path;
		path.Format("%s\\hpxsCrl.crl",((CMainFrame *)AfxGetMainWnd())->m_PathCrl);
		FILE * crl=fopen(path,"w");
		if(crl==NULL)
		{
			((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"����CRLʧ��");
			return;
		}

		fwrite(m_pCertKey,sizeof(char),m_CertLen,crl);
		fclose(crl);
		((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,"����CRL�ɹ�");
		m_ifCrl=false;
		delete [] m_pCertKey;
	}
	AsyncSelect(FD_READ|FD_CLOSE|FD_WRITE);//������ϣ��������͡�����
	CAsyncSocket::OnReceive(nErrorCode);
}

void CSslClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString serverIp,str;
	unsigned int port;
	GetPeerName(serverIp,port);//�õ��û�ip,port
	str.Format("%d��������%s�Ͽ�",m_hSocket,serverIp);
	((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(0,str,M_ERROR);
	((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(1,str,M_ERROR);
	((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(2,str,M_ERROR);
	((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(3,str,M_ERROR);
	SSlShouDown();
	((CMainFrame *)AfxGetMainWnd())->SetStatusIcon(IDS_STRING_STATE,IDI_ICON2);
	((CMainFrame *)AfxGetMainWnd())->ShowFind(0);
	CAsyncSocket::OnClose(nErrorCode);
}

void CSslClientSocket::OnSend(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_ComList.IsEmpty())
		return;
	stuLIST * LIST=(stuLIST *)m_ComList.RemoveHead();
	int window=0;
	if(SSlSend((char *)(&LIST->CA),sizeof(stuCA))>0)//���ͳɹ�
	{
		CString str;
		switch(LIST->CA.Type)
		{
		case FInputD://��ѯ�����
			str.Format("���ʹ����֤���ѯָ��ɹ�,�ȴ���������Ӧ......");
			window=1;
			break;
		case Audit://���֤��
			str.Format("����֤��%d�������ָ��ɹ�,�ȴ���������Ӧ......",LIST->ID);
			window=1;
			break;
		case FAuditD://��ѯ������:
			str.Format("���ʹ�����֤���ѯָ��ɹ�,�ȴ���������Ӧ......");
			window=2;
			break;
		case Made://����:
			str.Format("����֤��%d��������ָ��ɹ�,�ȴ���������Ӧ......",LIST->ID);
			window=2;
			break;
		case FRevokeD://��ѯ������
			str.Format("����������֤���ѯָ��ɹ�,�ȴ���������Ӧ......");
			window=3;
			break;
		case FMadeD://��ѯ������
			str.Format("����������֤���ѯָ��ɹ�,�ȴ���������Ӧ......");
			window=3;
			break;
		case Revoke://����
			str.Format("����֤��%d��������ָ��ɹ�,�ȴ���������Ӧ......",LIST->ID);
			window=3;
			break;
		case MadeCrl://����������
			str.Format("���ͺ���������ָ��ɹ�,�ȴ���������Ӧ......");
			window=3;
			break;
		}
		((CMainFrame *)AfxGetMainWnd())->AddDialogBarInfo(window,str,M_WARING);
		delete LIST;
		int pos=m_ComList.GetCount();
		((CMainFrame *)AfxGetMainWnd())->SetPos(pos);//������
	}
	else//ʧ�����¼���ͷ��
	{
		m_ComList.AddHead(LIST);
	}
	CAsyncSocket::OnSend(nErrorCode);
}

void CSslClientSocket::AddCommand(stuLIST * LIST)
{
	m_ComList.AddTail((stuLIST *)LIST);
	int pos=m_ComList.GetCount();
	((CMainFrame *)AfxGetMainWnd())->SetPos(pos);
}

BOOL CSslClientSocket::GetComCount()
{
	return m_ComList.GetCount()==0?FALSE:TRUE;
}
