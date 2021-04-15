#define MAX_MD_SIZE			(16+20) /* The SSLv3 md5+sha1 type */
#define DER			    1 //FORMAT_ASN1
#define PEM			    3	/*定义格式*/
#define P12				5

typedef void (* PDrawProg)(int pos);

/*对称算法*/
bool Crypt(char * cpname/*算法名称*/,char * filein/*输入文件*/, char * fileout/*输出文件*/,
		   char * pwd/*用于初始iv的密码*/, int type/*1-加密、0-解密*/,char * outMsg,
		   PDrawProg DrawProg=NULL);

/*消息摘要*/
bool Digest(char * mdname/*摘要算法*/,char * filein/*输入文件*/,unsigned char * md_value/*返回摘要*/,
			unsigned int * md_len/*摘要长度*/, char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);

/*数字签名*/
bool Sign(char * key/*私钥*/,int keylen/*0-内存内容*/,char * mdname/*签名算法*/,
		  char * filein/*输入文件*/,char * fileout/*输出文件*/,char * outMsg,
		  PDrawProg DrawProg=NULL/*回调函数*/);

/*数字签名验证*/
bool VerifySign(char * cert/*公钥*/,int certlen,char * mdname/*签名算法*/,char * filesource,/*原始文件*/ 
				char * filesign/*签名结果*/,char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);

/*数字信封*/
bool Seal(char * cert/*公钥*/,int certlen,char * cpname/*算法名称*/,char * filein/*输入文件*/, 
		  char * fileout/*输出文件*/,char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);

/*拆封数字信封*/
bool OpenSeal(char * key/*私钥*/,int keylen,char * cpname/*算法名称*/,char * filein/*输入文件*/, 
		  char * fileout/*输出文件*/,char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);

//公钥加密
bool RSAEnc(char * cert/*公钥*/,int certlen,char * filein/*输入文件*/, 
		  char * fileout/*输出文件*/,char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);

//私钥解密
int RSADec(char * key,int keylen,char * filein/*输入文件*/, 
		  char * fileout/*输出文件*/,char * outMsg,PDrawProg DrawProg=NULL/*回调函数*/);




