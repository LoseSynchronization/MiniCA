// SslClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
//#include "winsock2.h"
#include "SslClientSocket.h"

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
	m_pList=NULL;
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
X509 * CSslClientSocket::load_cert(BIO *cert/*输入BIO*/, int format/*格式*/,char * pwd,/*P12密码*/char * outMsg)
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

X509 * CSslClientSocket::LoadCert(char * cert,int certlen,char * outMsg)//枚举DER/PEM格式
{
	BIO * in=NULL;
	X509 * x509=NULL;

	if(certlen==0)//输入为磁盘文件
	{
		if((in=BIO_new_file(cert, "r")) == NULL)
		{
			sprintf(outMsg,"open CA certificate file error");
			return NULL;
		}
	}
	else//输入为内存中文件
	{
		if((in=BIO_new_mem_buf(cert,certlen))== NULL)//只读类型
		{
			sprintf(outMsg,"Make Mem Bio Error");
			return NULL;
		}
	}
	if((x509=load_cert(in,DER,NULL,outMsg))==NULL)//尝试DER
	{
		BIO_reset(in);//恢复bio
		x509=load_cert(in,PEM,NULL,outMsg);//尝试PEM
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

	if(keylen==0)//输入为磁盘文件
	{
		if((in=BIO_new_file(key, "r")) == NULL)
		{
			sprintf(outMsg,"open CA certificate file error");
			return NULL;
		}
	}
	else//输入为内存中文件
	{
		if((in=BIO_new_mem_buf(key,keylen))== NULL)//只读类型
		{
			sprintf(outMsg,"Make Mem Bio Error");
			return NULL;
		}
	}

	if((pkey=load_key(in,DER,pass,outMsg))==NULL)//尝试DER
	{
		BIO_reset(in);//BIO是可读写的，那么该BIO所有数据都会被清空；
						//如果该BIO是只读的，那么该操作只会简单将指
						//针指向原始位置，里面的数据可以再读.
		pkey=load_key(in,PEM,pass,outMsg);//尝试PEM
	}
	if (in != NULL) BIO_free(in);
	return pkey;
}

int CSslClientSocket::Rand(const char *file,int dont_warn,char * outMsg)
{
	int consider_randfile = (file == NULL);
	char buffer[200];
	
#ifdef WINDOWS
//	BIO_flush(bio_e);
	RAND_screen();
#endif
	
	if (file == NULL)
		file = RAND_file_name(buffer, sizeof buffer);
	else if (RAND_egd(file) > 0)
	{
	/* we try if the given filename is an EGD socket.
		if it is, we don't write anything back to the file. */
		return 1;
	}
	if (file == NULL || !RAND_load_file(file, -1))
	{
		if (RAND_status() == 0 && !dont_warn)
		{
			sprintf(outMsg,"unable to load 'random state'\n");
			sprintf(outMsg,"This means that the random number generator has not been seeded\n");
			if (consider_randfile) /* explanation does not apply when a file is explicitly named */
			{
				sprintf(outMsg,"Consider setting the RANDFILE environment variable to point at a file that\n");
				sprintf(outMsg,"'random' data can be kept in (the file will be overwritten).\n");
			}
		}
		return 0;
	}
	return 1;
}

void CSslClientSocket::GetPeerInfo(SSL * ssl,stuSERVERINFO * stu)
{
	
	X509 *peer=NULL;
	char *p;
	static char *space="                ";
	char buf[BUFSIZ];//512
	STACK_OF(X509) *sk;
	STACK_OF(X509_NAME) *sk2;
	SSL_CIPHER *c;
	X509_NAME *xn;
	int j,i;
	BIO *bio=BIO_new(BIO_s_mem());
	char bufout[1024]={0};
	
	int got_a_chain = 0;
	
	sk=SSL_get_peer_cert_chain(ssl);//returns a pointer to STACKOF(X509) certificates
	if (sk != NULL)
	{
		got_a_chain = 1; /* we don't have it for SSL2 (yet) */
		
		for (i=0; i<sk_X509_num(sk); i++)
		{
			X509_NAME_oneline(X509_get_subject_name(sk_X509_value(sk,i)),
				stu->peerChain.sub,BUFSIZ);
			X509_NAME_oneline(X509_get_issuer_name(sk_X509_value(sk,i)),
				stu->peerChain.iss,BUFSIZ);
			//	PEM_write_bio_X509(bio,sk_X509_value(sk,i));
			//	BIO_read(bio,bufout,4*BUFSIZ);
		}
	}
	
	peer=SSL_get_peer_certificate(ssl);
	if (peer != NULL)
	{
		//	Server certificate
		PEM_write_bio_X509(bio,peer);
		BIO_read(bio,stu->Cert,4*BUFSIZ);
		BIO_flush(bio);
		X509_NAME_oneline(X509_get_subject_name(peer),
			stu->peerCert.sub,BUFSIZ);
		X509_NAME_oneline(X509_get_issuer_name(peer),
			stu->peerCert.iss,BUFSIZ);
	}
	else
		strcpy(stu->Cert,"no peer certificate available");
	
	sk2=SSL_get_client_CA_list(ssl);
	if ((sk2 != NULL) && (sk_X509_NAME_num(sk2) > 0))
	{
		//	BIO_printf(bio,"---\nAcceptable client certificate CA names\n");
		for (i=0; i<sk_X509_NAME_num(sk2); i++)
		{
			xn=sk_X509_NAME_value(sk2,i);
			X509_NAME_oneline(xn,stu->selfChain,BUFSIZ);
			//	BIO_write(bio,buf,strlen(buf));
			//	BIO_write(bio,"\n",1);
		}
	}
	else
	{
		strcpy(stu->selfChain,"No client certificate CA names sent");
	}
	
	p=SSL_get_shared_ciphers(ssl,buf,BUFSIZ);
	if (p != NULL)
	{
	/* This works only for SSL 2.  In later protocol
	* versions, the client does not know what other
	* ciphers (in addition to the one to be used
		* in the current connection) the server supports. */
		
		//	BIO_printf(bio,"---\nCiphers common between both SSL endpoints:\n");
		j=i=0;
		while (*p)
		{
			if (*p == ':')
			{
				BIO_write(bio,space,15-j%25);
				i++;
				j=0;
				BIO_write(bio,((i%3)?" ":"\n"),1);
			}
			else
			{
				BIO_write(bio,p,1);
				j++;
			}
			p++;
		}
		BIO_write(bio,"\n",1);
	}
	
	//SSL handshake has read %ld bytes and written %ld bytes\n",
	stu->read=BIO_number_read(SSL_get_rbio(ssl));
	stu->written=BIO_number_written(SSL_get_wbio(ssl));
	
	//	BIO_printf(bio,((s->hit)?"---\nReused, ":"---\nNew, "));
	c=SSL_get_current_cipher(ssl);
	//BIO_printf(bio,"%s, Cipher is %s\n",
	strcpy(stu->CiphersVer,SSL_CIPHER_get_version(c));
	strcpy(stu->CiphersName,SSL_CIPHER_get_name(c));
	if (peer != NULL)
	{
		EVP_PKEY *pktmp;
		pktmp = X509_get_pubkey(peer);
		//Server public key bit
		stu->CertBit=EVP_PKEY_bits(pktmp);
		EVP_PKEY_free(pktmp);
	}
	SSL_SESSION_print(bio,SSL_get_session(ssl));
	BIO_read(bio,stu->Session,4*BUFSIZ);
	/* flush, or debugging output gets mixed with http response */
	BIO_flush(bio);
	if (peer != NULL)
		X509_free(peer);
	BIO_free(bio);
}

BOOL CSslClientSocket::SockConnect(SSL_METHOD *meth,char *certfile,int certlen, char *keyfile,int keylen,
		char * cafile, char * capath,CColorListBox * plist,LPCTSTR lpszHostAddress, UINT nHostPort,char * out)
{
	EVP_PKEY *pkey=NULL;
	X509 *x509=NULL;
	CString str;
	unsigned long l=1;
	BIO * sbio=NULL;
	struct hostent *hp;
    struct sockaddr_in addr;
    int sock,i=0;

	m_pList=plist;/////////////////////

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
	Rand(NULL,1,out);

	/*连接服务器*/

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
	
	if (connect(sock,(struct sockaddr *)&addr,sizeof(addr)) == SOCKET_ERROR)
	{
		SSlShouDown();
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
	Attach(sock,FD_WRITE|FD_CLOSE);
	str.Format("%d接入服务器%s，等待握手....",m_hSocket,inet_ntoa(addr.sin_addr));
	m_pList->AddMsg(str,M_WARING);
    return TRUE;

err:
	EVP_PKEY_free(pkey);
	X509_free(x509);
	SSlShouDown();
	return FALSE;
}

int CSslClientSocket::SSlConnect(stuSERVERINFO * stu,char * out)
{
	if(m_Ssl==NULL)
	{
		strcpy(out,"SSL没有正确初始化");
		return -1;
	}
	int err=0;
	if ((err = SSL_connect(m_Ssl)) <= 0)
	{
		if (BIO_sock_should_retry(err))
		{
			return 0;//重试
		}
		else 
		{
			strcpy(out,"SSL连接失败");//ERR_clear_error
			return -1;
		}
	}
	GetPeerInfo(m_Ssl,stu);
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
	if(m_hSocket != INVALID_SOCKET)
	{
		ShutDown(0);//receives
		Close();
	}
}

int CSslClientSocket::SSlSend(char *buf, int len)
{
	if(m_Ssl==NULL)
		return -1;
	int k=0;
	for(;;)
	{
		k = SSL_write(m_Ssl,buf,len);
		if (k <= 0)
		{
			if (BIO_sock_should_retry(k))
			{
				Sleep(100);
				continue;//重试
			}
			return k;//出错
		}
		break;
	}
	AsyncSelect(FD_READ|FD_CLOSE);
	return k;
}

int CSslClientSocket::SSlReceive(char *buf, int len)
{
	if(m_Ssl==NULL)
		return 0;
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
					Sleep(100);
					continue;//重试
				}
				return k;//错误退出				
			}
			m_pList->AddMsg(buf);
			break;
		}
	}while (SSL_pending(m_Ssl));

	return k;
}

void CSslClientSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString serverIp,str;
	unsigned int port;
	GetPeerName(serverIp,port);//得到用户ip,port
	str.Format("%d被服务器%s断开",m_hSocket,serverIp);
	m_pList->AddMsg(str,M_WARING);
	SSlShouDown();
	CAsyncSocket::OnClose(nErrorCode);
}

void CSslClientSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	char buf[1024]={0};
	SSlReceive(buf,1024);
	CAsyncSocket::OnReceive(nErrorCode);
}
