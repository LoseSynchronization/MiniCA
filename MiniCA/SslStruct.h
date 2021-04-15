/*服务器、客户端用到的一些结构*/
#include <openssl/ssl.h>
#include <openssl/pkcs12.h>
#include <openssl/rand.h>

#define DER			    1 //FORMAT_ASN1
#define PEM			    3	/*定义格式*/
#define NET				4
#define P12				5

struct stuISSU//主题、发行者
{
	char sub[BUFSIZ];
	char iss[BUFSIZ];
};

struct stuSERVERINFO
{
	stuISSU peerChain;//对方证书连
	char selfChain[BUFSIZ];//自己证书链
	stuISSU peerCert;//对方证书
	char Cert[4*BUFSIZ];//对方证书-pem
	char CiphersVer[64];//SSL版本
	char CiphersName[64];//SSL算法
	int read;//读取
	int written;//写入
	int CertBit;//共钥位数
	UCHAR Session[4*BUFSIZ];
	stuSERVERINFO()
	{
		memset(this,0,sizeof(stuSERVERINFO));
	}

};

struct stuCLIENTINFO
{
	UCHAR Session[4*BUFSIZ];
	char Cert[4*BUFSIZ];//对方证书-pem
	stuISSU peerCert;//对方证书
	char Shared_ciphers[4*BUFSIZ];
	char Current_cipher[64];
	stuCLIENTINFO()
	{
		memset(this,0,sizeof(stuCLIENTINFO));
	}
};