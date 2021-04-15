// SslServerSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UsbKey.h"
#include "SslServerSocket.h"
#include <openssl/err.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSslServerSocket

CSslServerSocket::CSslServerSocket()
{
	m_Ctx=NULL;
	m_Ssl=NULL;
	m_pSocket=NULL;
	m_pList=NULL;
	m_type=0;//www
	m_pObSock=NULL;
}

CSslServerSocket::CSslServerSocket(int type)
{
	m_Ctx=NULL;
	m_Ssl=NULL;
	m_pSocket=NULL;
	m_pList=NULL;
	m_type=1;//ra
	m_pObSock=NULL;
}

CSslServerSocket::~CSslServerSocket()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSslServerSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CSslServerSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSslServerSocket member functions
X509 * CSslServerSocket::load_cert(BIO *cert/*输入BIO*/, int format/*格式*/,char * pwd,/*P12密码*/char * outMsg)
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

X509 * CSslServerSocket::LoadCert(char * cert,int certlen,char * outMsg)//枚举DER/PEM格式
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

EVP_PKEY * CSslServerSocket::load_key(BIO *bio, int format, char *pass,char * outMsg)
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

EVP_PKEY * CSslServerSocket::LoadKey(char * key,int keylen,char * pass,char * outMsg)
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

int CSslServerSocket::Rand(const char *file,int dont_warn,char * outMsg)
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

BOOL CSslServerSocket::GetPeerInfo(SSL * ssl,stuCLIENTINFO * stu)
{
	
	X509 *peer;
	BIO *bio=BIO_new(BIO_s_mem());
	const char *str=NULL;
	
	SSL_SESSION_print(bio,SSL_get_session(ssl));
	
	peer=SSL_get_peer_certificate(ssl);
	if (peer != NULL)
	{
		PEM_write_bio_X509(bio,peer);
		BIO_read(bio,stu->Cert,4*BUFSIZ);
		BIO_flush(bio);
		X509_NAME_oneline(X509_get_subject_name(peer),stu->peerCert.sub,BUFSIZ);
		X509_NAME_oneline(X509_get_issuer_name(peer),stu->peerCert.iss,BUFSIZ);
		X509_free(peer);
	}
	
	if (SSL_get_shared_ciphers(ssl,stu->Shared_ciphers,BUFSIZ) != NULL)
	{
		int bits2=0;
		SSL_CIPHER *sc=SSL_get_current_cipher(ssl);
		if(ssl==NULL) strcpy(stu->Current_cipher,"No current cipher?\n");
		else
		{
			int bits=SSL_CIPHER_get_bits(sc, &bits2);
			sprintf(stu->Current_cipher,"Version=%s Cipher=%s Bits=%d\n", SSL_get_version(ssl),
				SSL_CIPHER_get_name(sc), bits);
		}
	}
	if(strlen(stu->Cert))
		m_pList->AddMsg(stu->Cert);
	if(strlen(stu->Current_cipher))
		m_pList->AddMsg(stu->Current_cipher);
	if(strlen(stu->peerCert.iss))
		m_pList->AddMsg(stu->peerCert.iss);
	if(strlen(stu->peerCert.sub))
		m_pList->AddMsg(stu->peerCert.sub);
	if(strlen((char *)stu->Session))
		m_pList->AddMsg(stu->Session);
	if(strlen(stu->Shared_ciphers))
		m_pList->AddMsg(stu->Shared_ciphers);

	return TRUE;
	/*	if (s->hit) BIO_printf(bio,"Reused session-id\n");
	if (SSL_ctrl(s,SSL_CTRL_GET_FLAGS,0,NULL) &
	TLS1_FLAGS_TLS_PADDING_BUG)
	BIO_printf(bio,"Peer has incorrect TLSv1 block padding\n");*/
}

SSL_CTX * CSslServerSocket::InitCtx(SSL_METHOD *meth,char *certfile,int certlen,
									char *keyfile,int keylen,char * cafile, char * capath,
									int VerType/*对于客户端验证模式*/,CColorListBox * plist,
									CObList	* pObSock/*连接列表*/,
									_ConnectionPtr pConnection/*数据库连接*/,char * out)
{
	EVP_PKEY *pkey=NULL;
	X509 *x509=NULL;
	OpenSSL_add_ssl_algorithms();
	SSL_load_error_strings();
	
	m_pList=plist;/////////////////////
	m_pConnection=pConnection;/////////
	m_pObSock=pObSock;
    m_Ctx=SSL_CTX_new(meth);
	if (m_Ctx == NULL)
	{
		strcpy(out,"Create ctx error");
		return NULL;
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
	switch(VerType)
	{
	case 1:
		SSL_CTX_set_verify(m_Ctx,SSL_VERIFY_PEER,Verify);//要求对方证书
		break;
	case 2:
		SSL_CTX_set_verify(m_Ctx,SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT,Verify);
		break;
	case 3:
		SSL_CTX_set_verify(m_Ctx,SSL_VERIFY_PEER|SSL_VERIFY_CLIENT_ONCE,Verify);
		break;
	default:
		SSL_CTX_set_verify(m_Ctx,SSL_VERIFY_NONE,Verify);//不要求对方证书
		break;
	}

    /* Load randomness */
	Rand(NULL,1,out);
err:
	EVP_PKEY_free(pkey);
	X509_free(x509);
    return m_Ctx;
}

BOOL CSslServerSocket::CreateLisenSock(UINT nSocketPort, long lEvent)
{
	int sock;
	char out[100]={0};
	struct sockaddr_in sin;
	int val=1;
	memset(&sin,0,sizeof(sin));
	sin.sin_addr.s_addr=INADDR_ANY;
	sin.sin_family=AF_INET;
	sin.sin_port=htons(nSocketPort);
	
	if((sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
	{
		GetSockError(GetLastError(),out);
		return FALSE;
	}
	val=setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&val,sizeof(val));
	if (val < 0)
	{
		GetSockError(GetLastError(),out);
		return FALSE;
	}
	
	if(bind(sock,(struct sockaddr *)&sin,sizeof(sin))<0)//If no error occurs, bind returns zero
	{
		GetSockError(GetLastError(),out);
		return FALSE;
	}
	if(listen(sock,5))//return 0 no error
	{
		GetSockError(GetLastError(),out);
		return FALSE;
	}
	
	Attach(sock,lEvent);
	return TRUE;
}

void CSslServerSocket::OnAccept(int nErrorCode) //只有侦听sock执行
{
	// TODO: Add your specialized code here and/or call the base class
	BIO * sbio=NULL;
	int err;
	char out[100]={0};

	SOCKADDR_IN client;
	int iAddrSize=sizeof(client);

	m_pSocket = new CSslServerSocket();//用于连接

	m_pSocket->m_pList=m_pList;
	m_pSocket->m_pObSock=m_pObSock;//公用一个链表
	m_pSocket->m_type=m_type;
	m_pSocket->m_pConnection=m_pConnection;

	if(Accept(*m_pSocket,(SOCKADDR *)&client,&iAddrSize))
	{
		CString str;
		str.Format("客户 %s TCP接入成功,等待握手......",inet_ntoa(client.sin_addr));
		m_pList->AddMsg(str,M_WARING);
		m_pSocket->m_Ssl = SSL_new (m_Ctx); 
		SSL_set_accept_state(m_pSocket->m_Ssl);
		sbio=BIO_new_socket(m_pSocket->m_hSocket,BIO_NOCLOSE);
		SSL_set_bio(m_pSocket->m_Ssl,sbio,sbio);
		
		for(;;)
		{
			if ((err = SSL_accept (m_pSocket->m_Ssl)) <= 0)
			{
				if (BIO_sock_should_retry(err))
				{
					continue;
				}
				int verify_error=SSL_get_verify_result(m_pSocket->m_Ssl);
				if (verify_error != X509_V_OK)//succeeded or no peer certificate was presented
				{
					sprintf(out,"verify error:%s\n",
						X509_verify_cert_error_string(verify_error));
					m_pList->AddMsg(out,M_ERROR);

				}
				else
				{
					m_pList->AddMsg("客户端没有证书,握手结束",M_WARING);
					m_pSocket->Close();
					delete m_pSocket;
					m_pSocket=NULL;
				}
				return ;
			}
			else
			{
				m_pSocket->AsyncSelect(FD_READ|FD_CLOSE);//选择读事件(OnReceive)
				str.Format("握手结束,客户%s接入成功",inet_ntoa(client.sin_addr));
				GetPeerInfo(m_pSocket->m_Ssl,&m_CLIENTINFO);
				m_pList->AddMsg(str,M_WARING);
				m_pObSock->AddTail(m_pSocket);
				break;
			}
		}
		
	}	
	else
	{	
		m_pList->AddMsg("TCP连接失败",M_ERROR);
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket=NULL;
	}					
	CAsyncSocket::OnAccept(nErrorCode);
}

void CSslServerSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	CString clientIp;
	unsigned int port;
	POSITION pos;
	GetPeerName(clientIp,port);//得到用户ip,port
	clientIp+="已经断开连接!";
	clientIp="客户"+clientIp;
	m_pList->AddMsg(clientIp,M_WARING);

	pos=m_pObSock->Find(this);
	if(pos) m_pObSock->RemoveAt(pos);//客户端关闭

	if(m_Ssl!=NULL)
	{
		SSlShouDown();
	}
	delete this;
	CAsyncSocket::OnClose(nErrorCode);
}

int CSslServerSocket::SSlSend(char *buf, int len)
{
	if(m_Ssl==NULL)
		return -1;
	int k=0;//接收数量
	int offect=0;//偏移
	for(;0!=len;)//maximum record size of 16kB for SSLv3/TLSv1
	{
		k = SSL_write(m_Ssl,buf+offect,len);
		if (k <= 0)
		{
			if (BIO_sock_should_retry(k))
			{
				Sleep(100);
				continue;//重试
			}
			return k;//出错
		}
		offect+=k;
		len-=k;
	}
	AsyncSelect(FD_READ|FD_CLOSE);
	return offect;
}

int CSslServerSocket::SSlReceive(char *buf, int len)
{
	int k=0;
	do
	{
		for(;;)
		{
			k = SSL_read(m_Ssl,buf,len);
			if (k <= 0)
			{
				if (BIO_sock_should_retry(k))
				{
					Sleep(100);
					continue;//重试
				}
				return k;//错误退出
			}
			break;//成功
		}
	}while (SSL_pending(m_Ssl));

	return k;
}


void CSslServerSocket::DisplayError(_com_error &e)
{
	CString msgText;
	_bstr_t bstrSource(e.Source());
	_bstr_t bstrDescription(e.Description());
	
	msgText.Format("连接数据库错误\n错误代码 = %08lx\n", e.Error());
	msgText += " Msg: ";
	msgText += e.ErrorMessage();
	msgText += "\n 来源: ";
	msgText += bstrSource;
	msgText += "\n 内容: ";
	msgText += bstrDescription;
	m_pList->AddMsg(msgText,M_ERROR);

}

void CSslServerSocket::OnReceive(int nErrorCode) //与客户端交互
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_type==0)//www
	{
		char buf[1024]={0};
		SSlReceive(buf,1024);
		AsyncSelect(FD_WRITE|FD_CLOSE);
	}
	else//ra
	{
		stuCA CA;//接收用结构
		if(SSlReceive((char *)&CA,sizeof(stuCA))<=0)//对方已经关闭
			return;
		stuRA RA;//用于发送的结构
		
		_variant_t Affected;//影响行数
		_RecordsetPtr m_pRecordset;
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		
		switch(CA.Type)
		{
		case Input://录入证书
			{
				stuCERT sCERT;
				CString strSQL;
				if(SSlReceive((char * )&sCERT,sizeof(sCERT))<0)//接收客户信息
					return;
				char * p=(char *)&sCERT;
				VARIANT varBLOB;
				SAFEARRAY FAR *psa; 
				SAFEARRAYBOUND rgsabound[1];
				SYSTEMTIME tm;
				GetLocalTime(&tm);
				CString time;
				time.Format("%d-%d-%d", tm.wYear,tm.wMonth,tm.wDay);
				
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}		
					m_pRecordset->Open("CERTLIST",_variant_t((IDispatch*)m_pConnection,true),
						adOpenDynamic,adLockOptimistic,adCmdTable);//打开表
					
					m_pRecordset->AddNew(); ///添加新记录
					rgsabound[0].lLbound = 0;
					rgsabound[0].cElements = sizeof(stuCERT);
					psa = SafeArrayCreate(VT_UI1, 1, rgsabound); ///创建SAFEARRAY对象
					for (long i =0;i<sizeof(stuCERT); i++)
					{
						SafeArrayPutElement (psa, &i, p++); ///保存二进制数据
					}
					// 由于Variant没有SafeArray的构造函数，所以手工设置Variant的数据类型和值。
					varBLOB.vt = VT_ARRAY | VT_UI1;
					varBLOB.parray = psa; 
					m_pRecordset->Fields->GetItem("USERINFO")->AppendChunk(varBLOB); ///加入数据
					SafeArrayDestroy(psa);
					m_pRecordset->Fields->GetItem("INPUTTIME")->PutValue(_variant_t(time));
					_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;//得到id
					m_pRecordset->Update(); //更新
					RA.ID=UserID.lVal;//ID
					RA.Type=Input;//操作类型
					RA.State=TRUE;//操作状态
					SSlSend((char *)&RA,sizeof(RA));
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					RA.Type=Input;//操作类型
					RA.State=FALSE;//操作状态
					SSlSend((char *)&RA,sizeof(RA));
				}
				break;
			}
		case FInputD://待审核
		case FAuditD://待制作
		case FMadeD://有效
		case FRevokeD://无效
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}				
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenStatic,//静态游标
						adLockOptimistic,adCmdText); 
					m_Rcount=m_pRecordset->RecordCount;//纪录条数--静态游标有效
					if(!m_pRecordset->adoEOF)//存在纪录
					{
						for(int index=0;!m_pRecordset->adoEOF;m_pRecordset->MoveNext(),index++)//遍历所有记录
						{
							//得到用户ID,个体信息
							_variant_t	varBLOB;
							varBLOB = m_pRecordset->Fields->GetItem("USERINFO")->GetChunk(sizeof(RA.SUBJECT));
							if(varBLOB.vt == (VT_ARRAY | VT_UI1))
							{
								char *pBuf = NULL;
								SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
								memcpy(&RA.SUBJECT,pBuf,sizeof(RA.SUBJECT));//个体信息
								SafeArrayUnaccessData(varBLOB.parray);
							}
							
							_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;
							RA.ID=UserID.lVal;//ID
							
							switch(CA.Type)
							{
							case FInputD://查询代审核
								{
									_bstr_t InputTime=m_pRecordset->Fields->GetItem("INPUTTIME")->Value;
									CString Input=InputTime.copy();
									strcpy(RA.Time,Input);//操作时间
									RA.Type=FInputD;//操作类型
									RA.State=TRUE;//操作状态
									if(index==0)//第一次发送总纪录数
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=1;//KeyL=1 -->总纪录数
									}
									if(index==m_Rcount-1)//最后一条纪录(一条纪录时候m_Rcount=1)
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=-1;
									}
									if(index!=0&&index!=m_Rcount-1)
									{
										RA.CertL=index;//其余发送纪录数
										RA.KeyL=0;
									}
									break;
									
								}
							case FAuditD://查询代制作
								{
									_bstr_t AuditTime=m_pRecordset->Fields->GetItem("AUDITIME")->Value;
									CString Audit=AuditTime.copy();
									strcpy(RA.Time,Audit);//操作时间
									RA.Type=FAuditD;//操作类型
									RA.State=TRUE;//操作状态
									if(index==0)//第一次发送总纪录数
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=1;//KeyL=1 -->总纪录数
									}
									if(index==m_Rcount-1)//最后一条纪录(一条纪录时候m_Rcount=1)
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=-1;
									}
									if(index!=0&&index!=m_Rcount-1)
									{
										RA.CertL=index;//其余发送纪录数
										RA.KeyL=0;
									}
									break;
									
								}
							case FMadeD://查询已经制作
								{
									_bstr_t MadeTime=m_pRecordset->Fields->GetItem("MADETIME")->Value;
									CString Made=MadeTime.copy();
									strcpy(RA.Time,Made);//操作时间
									RA.Type=FMadeD;//操作类型
									RA.State=TRUE;//操作状态
									if(index==0)//第一次发送总纪录数
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=1;//KeyL=1 -->总纪录数
									}
									if(index==m_Rcount-1)//最后一条纪录(一条纪录时候m_Rcount=1)
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=-1;
									}
									if(index!=0&&index!=m_Rcount-1)
									{
										RA.CertL=index;//其余发送纪录数
										RA.KeyL=0;
									}
									break;
									
								}
							case FRevokeD: //查询已经作废
								{
									_bstr_t DelTime=m_pRecordset->Fields->GetItem("REVOKETIME")->Value;
									CString Del=DelTime.copy();
									strcpy(RA.Time,Del);//操作时间
									RA.Type=FRevokeD;//操作类型
									RA.State=TRUE;//操作状态
									if(index==0)//第一次发送总纪录数
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=1;//KeyL=1 -->总纪录数
									}
									if(index==m_Rcount-1)//最后一条纪录(一条纪录时候m_Rcount=1)
									{
										RA.CertL=m_Rcount;//总纪录数
										RA.KeyL=-1;
									}
									if(index!=0&&index!=m_Rcount-1)
									{
										RA.CertL=index;//其余发送纪录数
										RA.KeyL=0;
									}
									break;
								}
							default:
								{
									m_pList->AddMsg("未知命令",M_ERROR);
									break;
								}
							}
							if(SSlSend((char *)&RA,sizeof(RA))<=0)//发送
								break;
					}
				}
				else//纪录为0
				{
					switch(CA.Type)
					{
					case FInputD://查询代审核
						{
							RA.Type=FInputD;//操作类型
							RA.State=TRUE;//操作状态
							RA.KeyL=1;
							break;
						}
					case FAuditD://查询代制作
						{
							RA.Type=FAuditD;//操作类型
							RA.State=TRUE;//操作状态
							RA.KeyL=1;
							break;
						}
					case FMadeD://查询已经制作
						{
							RA.Type=FMadeD;//操作类型
							RA.State=TRUE;//操作状态
							RA.KeyL=1;
							break;
						}
					case FRevokeD://查询已经作废
						{
							RA.Type=FRevokeD;//操作类型
							RA.State=TRUE;//操作状态
							RA.KeyL=1;
							break;
						}
					default:
						{	
							m_pList->AddMsg("未知命令",M_ERROR);
							break;
						}
					}
					if(SSlSend((char *)&RA,sizeof(RA))<=0)//发送
						break;
				}
			}
			catch (_com_error &e)
			{
				DisplayError(e);
				SSlSend((char *)&RA,sizeof(RA));//发送
			}
			break;
		}
		case Audit://审核
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}				
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText); 
					if(!m_pRecordset->adoEOF)//记录
					{ 
						char out[100]="";
						char cert[4096]={0};
						char key[4096]={0};
						int certl=0,keyl=0;
						stuCERT sCERT;
						///////////////////////////////////////////////////////////////////////////////////
						_variant_t	varBLOB;
						varBLOB = m_pRecordset->Fields->GetItem("USERINFO")->GetChunk(sizeof(stuCERT));
						if(varBLOB.vt == (VT_ARRAY | VT_UI1))
						{
							char *pBuf = NULL;
							SafeArrayAccessData(varBLOB.parray,(void **)&pBuf);
							memcpy(&sCERT,pBuf,sizeof(stuCERT));//个体信息
							SafeArrayUnaccessData(varBLOB.parray);
						}
						///////////////////////////////////////////////////////////////////////////////////
						
						SYSTEMTIME tm;
						GetLocalTime(&tm);
						CString time;
						time.Format("%d-%d-%d", tm.wYear,tm.wMonth,tm.wDay);
						
						_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;
						
						HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
						DWORD lenCert = SizeofResource(NULL, hRsrc); 
						HGLOBAL hgCert=LoadResource(NULL,hRsrc);
						LPSTR lpCert=(LPSTR)LockResource(hgCert);
	
						/*私钥*/
						hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
						DWORD lenKey = SizeofResource(NULL, hRsrc); 
						HGLOBAL hgKey=LoadResource(NULL,hRsrc);
						LPSTR lpKey=(LPSTR)LockResource(hgKey);

			
						if(DirectCert(lpCert,lenCert,lpKey,lenKey,UserID.lVal,0,atoi("365"),&sCERT,1024,
							cert,&certl,key,&keyl,out/*,m_CertFormat*/))//固定有效期和密钥长度
						{
							m_pRecordset->Fields->GetItem("CERTSTATE")->PutValue(_variant_t((long)1));
							m_pRecordset->Fields->GetItem("AUDITIME")->PutValue(_variant_t(time));
							m_pRecordset->Fields->GetItem("USERCERT")->PutValue(_variant_t(cert));
							m_pRecordset->Fields->GetItem("USERKEY")->PutValue(_variant_t(key));
							m_pRecordset->Update();
							
							RA.ID=UserID.lVal;//ID
							RA.Type=Audit;//操作类型
							RA.State=TRUE;//操作状态
						}
						else
						{
							m_pList->AddMsg(out,M_ERROR);
							RA.Type=Audit;//操作类型
							RA.State=FALSE;//操作状态
						}
					}				
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					RA.Type=Made;//操作类型
					RA.State=FALSE;//操作状态
				}
				if(SSlSend((char *)&RA,sizeof(RA))<=0)
					return;
				break;
			}
		case Made://制作证书
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText); 
					if(!m_pRecordset->adoEOF)//记录
					{ 
						_bstr_t UserCert=m_pRecordset->Fields->GetItem("USERCERT")->Value;
						CString Cert=UserCert.copy();
						_bstr_t UserKey=m_pRecordset->Fields->GetItem("USERKEY")->Value;
						CString Key=UserKey.copy();
						_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;
						
						RA.ID=UserID.lVal;//ID
						RA.Type=Made;//操作类型
						RA.State=TRUE;//操作状态
						RA.CertL=Cert.GetLength();//公钥长度
						RA.KeyL=Key.GetLength();//私钥长度
						SSlSend((char *)&RA,sizeof(RA));//发送证书ID、公钥证书长度,私钥长度
						
						CString CertKey;
						CertKey=Cert+Key;
						SSlSend(CertKey.GetBuffer(0),strlen(CertKey));//发送证书内容
					}
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					RA.Type=Made;//操作类型
					RA.State=FALSE;//操作状态
					SSlSend((char *)&RA,sizeof(RA));
				}
				break;
			}
		case MadeOK://制作成功，用于更新数据库,不发送消息
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}				
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText); 
					if(!m_pRecordset->adoEOF)//记录
					{ 
						
						SYSTEMTIME tm;
						GetLocalTime(&tm);
						CString time;
						time.Format("%d-%d-%d", tm.wYear,tm.wMonth,tm.wDay);
						m_pRecordset->Fields->GetItem("CERTSTATE")->PutValue(_variant_t((long)2));
						m_pRecordset->Fields->GetItem("MADETIME")->PutValue(_variant_t(time));
						m_pRecordset->Update();
					}
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					m_pList->AddMsg("更新数据库失败",M_ERROR);
				}	 								 
				break;
			}
		case Revoke://作废证书
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}				
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText); 
					time_t ttime;//当前时间
					time(&ttime);
					if(!m_pRecordset->adoEOF)//记录
					{ 
						m_pRecordset->Fields->GetItem("CERTSTATE")->PutValue(_variant_t((long)-1));
						m_pRecordset->Fields->GetItem("REVOKETIME")->PutValue(_variant_t(ttime));
						m_pRecordset->Update();
						_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;
						
						RA.ID=UserID.lVal;//ID
						RA.Type=Revoke;//操作类型
						RA.State=TRUE;//操作状态
					}
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					RA.Type=Revoke;//操作类型
					RA.State=FALSE;//操作状态
				}
				SSlSend((char *)&RA,sizeof(RA));
				break;
			}
		case MadeCrl://制作CRL
			{
				try
				{
					if (m_pConnection == NULL)
					{
						return;
					}				
					time_t timet;//作废时间
					int id;//索引
					time_t t;
					time(&t);
					char out[100]={0};
					stuREVOKE * Head=NULL;
					m_pRecordset->Open((_bstr_t)CA.SQL,(IDispatch*)m_pConnection,adOpenDynamic,adLockOptimistic,adCmdText); 
					while(!m_pRecordset->adoEOF)//记录
					{ 
						_variant_t UserID=m_pRecordset->Fields->GetItem("ID")->Value;
						id=UserID.lVal;//ID
						_variant_t RevokeTime=m_pRecordset->Fields->GetItem("REVOKETIME")->Value;
						timet=RevokeTime.lVal;//time
						AddRevoke(Head,id,timet);
						m_pRecordset->MoveNext();//转到下一条纪录
					}
					HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_CERT),"CERT");
					DWORD lenCert = SizeofResource(NULL, hRsrc); 
					HGLOBAL hgCert=LoadResource(NULL,hRsrc);
					LPSTR lpCert=(LPSTR)LockResource(hgCert);
					/*私钥*/
					hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_ROOT_KEY),"CERT");
					DWORD lenKey = SizeofResource(NULL, hRsrc); 
					HGLOBAL hgKey=LoadResource(NULL,hRsrc);
					LPSTR lpKey=(LPSTR)LockResource(hgKey);
					char * Crl=NULL;
					int CrlLen=0;
					if(MakeCrl(lpCert,lenCert,lpKey,lenKey,Head,NewCrlMem,Crl,&CrlLen,NULL,out))
					{
						RA.Type=MadeCrl;//操作类型
						RA.State=TRUE;//操作状态
						RA.CertL=CrlLen;//crl长度
						if(SSlSend((char *)&RA,sizeof(RA))>0)//发送crl、crl长度
							int i=SSlSend(Crl,CrlLen);//发送证书内容
						delete Crl;
					}
					else
					{
						RA.Type=MadeCrl;//操作类型
						RA.State=FALSE;//操作状态
						m_pList->AddMsg(out,M_ERROR);
						SSlSend((char *)&RA,sizeof(RA));
					}
				}
				catch (_com_error &e)
				{
					DisplayError(e);
					RA.Type=Revoke;//操作类型
					RA.State=FALSE;//操作状态
					SSlSend((char *)&RA,sizeof(RA));
				}
				break;
			}
		}
		m_pRecordset->Close();
		m_pRecordset = NULL;
		AsyncSelect(FD_READ|FD_CLOSE);
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

char * CSslServerSocket::NewCrlMem(UINT len) //分配内存
{
	return new char [len];
}

void CSslServerSocket::OnSend(int nErrorCode)
{
	// TODO: Add your specialized code here and/or call the base class
	char out[100]={0};
	if(m_type==0)//www
	{
		/*得到html*/
		HRSRC hRsrc=FindResource(NULL,MAKEINTRESOURCE(IDR_HTML),RT_HTML);
		DWORD lenHtml = SizeofResource(NULL, hRsrc); 
		HGLOBAL hgHtml=LoadResource(NULL,hRsrc);
		LPSTR lpHtml=(LPSTR)LockResource(hgHtml);
		SSlWww(lpHtml,lenHtml,out);
	}
	CAsyncSocket::OnSend(nErrorCode);
}

void CSslServerSocket::SSlWww(char * file,int len, char *out)
{
	int i=0,k=0;
	POSITION pos;
	if(len==0)//磁盘文件
	{
		FILE *fp;
		char buf[1024]={0};
		if((fp=fopen(file,"r+b"))==NULL)
		{
			sprintf(out,"Error opening %s",file);
			return;
		}
		for (;;)
		{
			i=fread(buf,sizeof(char), 1024,fp);
			if (i <= 0) break;
			k=SSlSend(buf,i);
			memset(buf,0,1024);
			if (k <= 0)
			{
				break;
			}
		}
		fclose(fp);
	}
	else
	{
//		for(i=0;;i++)
		{
	//		k=SSlSend(file+i*1024,(len>1024)?1024:len);
			k=SSlSend(file,len);
//			if (k <= 0) break;
//			len-=1024;
//			if(len<=0)
//				break;
		}
	}
	CString clientIp,str;
	unsigned int port;
	GetPeerName(clientIp,port);//得到用户ip,port
	str.Format("断开客户连接%s",clientIp);
	SSL_set_shutdown(m_Ssl,SSL_SENT_SHUTDOWN|SSL_RECEIVED_SHUTDOWN);
	ShutDown(2);
	pos=m_pObSock->Find(this);
	if(pos) m_pObSock->RemoveAt(pos);//主动关闭
	Close();
	m_pList->AddMsg(str,M_WARING);
	delete this;

}

void CSslServerSocket::SSlShouDown()
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
		ShutDown(2);
		Close();
	}
}

int CSslServerSocket::Verify(int ok, X509_STORE_CTX *ctx)
{
	char buf[256];
	X509 *err_cert;
	int err,depth;
	char out[100]={0};
	int	verify_depth=1;
	long verify_error;
	err_cert=X509_STORE_CTX_get_current_cert(ctx);
	err=	X509_STORE_CTX_get_error(ctx);
	depth=	X509_STORE_CTX_get_error_depth(ctx);

	X509_NAME_oneline(X509_get_subject_name(err_cert),buf,256);
	sprintf(out,"depth=%d %s\n",depth,buf);
	if (!ok)
		{
		sprintf(out,"verify error:num=%d:%s\n",err,
			X509_verify_cert_error_string(err));
		if (verify_depth >= depth)
			{
			ok=1;
			verify_error=X509_V_OK;
			}
		else
			{
			ok=0;
			verify_error=X509_V_ERR_CERT_CHAIN_TOO_LONG;
			}
		}
	switch (ctx->error)
		{
	case X509_V_ERR_UNABLE_TO_GET_ISSUER_CERT:
		X509_NAME_oneline(X509_get_issuer_name(ctx->current_cert),buf,256);
		sprintf(out,"issuer= %s\n",buf);
		break;
	case X509_V_ERR_CERT_NOT_YET_VALID:
	case X509_V_ERR_ERROR_IN_CERT_NOT_BEFORE_FIELD:
		sprintf(out,"notBefore=");
		break;
	case X509_V_ERR_CERT_HAS_EXPIRED:
	case X509_V_ERR_ERROR_IN_CERT_NOT_AFTER_FIELD:
		sprintf(out,"notAfter=");
		break;
		}
	return(ok);
}
