#include <time.h>
#define DER			    1 //FORMAT_ASN1
#define PEM			    3	/*定义格式*/
#define NET				4
#define P12				5

typedef char * (* PNewCrlMem)(UINT len);

struct stuSUBJECT//个体信息
{
	UCHAR C[4];//国家
	UCHAR ST[4];//省份
	UCHAR L[12];//城市
	UCHAR O[48];//组织
	UCHAR OU[24];//组织部门
	UCHAR CN[12];//个人信息
	UCHAR MAIL[24];//电子邮件
	UCHAR PMAIL[24];//安全电子邮件
	UCHAR T[12];//头衔
	UCHAR D[12];//描述
	UCHAR G[12];//曾用名
	UCHAR I[12];//描述
	UCHAR NAME[12];//描述
	UCHAR S[12];//描述
	UCHAR QUAL[12];//描述
	UCHAR STN[12];//没有结构的名称
	UCHAR PW[12];//挑战密码
	UCHAR ADD[12];//无结构地址

	stuSUBJECT()
	{
		memset(this,0,sizeof(stuSUBJECT));
	}
};

struct stuKEYUSAGE//密钥用途
{
	BOOL DS;//Digital Signature
	BOOL NR;//Non-Repudiation
	BOOL KE;//Key Encipherment
	BOOL DE;//Data Encipherment
	BOOL KA;//keyAgreement
	BOOL KC;//keyCertSign 
	BOOL CS;//cRLSign
	BOOL EO;//Encipher Only
	BOOL DO;//Decipher Only
	stuKEYUSAGE()
	{
		memset(this,0,sizeof(stuKEYUSAGE));
	}

};

struct stuEKEYUSAGE//增强型密钥用途
{
	BOOL SA;//服务器验证
	BOOL CA;//客户端验证
	BOOL CS;//代码签名
	BOOL EP;//安全电子邮件
	BOOL TS;//时间戳
	BOOL msCC;//代码完整
	BOOL msCTLS;//可签名信任列表
	BOOL msSGC;//联机事务处理
	BOOL msEFS;//加密磁盘上的数据
	BOOL msSC;//智能卡登录
	BOOL IP;//Internet
	stuEKEYUSAGE()
	{
		memset(this,0,sizeof(stuEKEYUSAGE));
	}

};

struct stuCERT//三者之和
{
	stuSUBJECT SUBJECT;
	stuKEYUSAGE KUSAGE;
	stuEKEYUSAGE EKUSAGE;
	stuCERT()
	{
		memset(this,0,sizeof(stuCERT));
	}
};

struct stuREVOKE//证书作废结构链表
{
	int Index;//证书序号
	time_t time;//吊销时间
	stuREVOKE * Link;
	stuREVOKE()
	{
		memset(this,0,sizeof(stuREVOKE));
	}
	stuREVOKE(int index,time_t t)
	{
		Index=index;
		time=t;;
		Link=NULL;
	}
};

/*添加链表节点*/
void AddRevoke(stuREVOKE *& Head,int index,time_t time);

/*证书格式转换函数*/
BOOL CertFormatConver(char * buf/*内存区域，存储文件内容或文件名称*/,int len/*内存长度==0则buf为文件名*/,
			  char * pwd/*p12文件密码*/,char * pem/*输出文件*/,int outformat,char * out/*操作结果*/);

/*根证书生成函数，根据rootInfo信息，生成根证书公、私钥文件*/
BOOL MakeRoot(stuSUBJECT * rootInfo,/*请求信息IN*/int bits/*位数IN*/, int serial/*序列号IN*/, 
			  int days/*有效期IN*/,char * certFile/*证书请求文件OUT*/,char * priFile/*私钥文件OUT*/,
			  char * out/*操作结果OUT*/,int type=PEM/*类型pem-der*/);

/*证书请求生成函数，根据reqInfo信息，生成用户证书私钥文件、证书请求文件*/
BOOL MakeReq(stuSUBJECT * reqInfo,/*请求信息IN*/int bits/*位数IN*/, char * reqFile/*证书请求文件OUT*/,
			 char * priFile/*私钥文件OUT*/,char * out/*操作结果OUT*/,int type=PEM/*类型pem-der*/);

/*证书生成函数，通过证书请求，生成用户证书公钥文件*/
BOOL MakeCert(char *certfile/*根证书公钥*/,int certlen,/*为0则certfile为磁盘文件，否则为内存区域*/
			  char *keyfile/*根证书私钥*/,int keylen,int serial/*序列号*/,char *enddate/*作废日期*/,
			  int days/*有效期*/, char *reqfile/*请求文件*/,stuKEYUSAGE * KUSAGE/*密钥用法*/,
			  stuEKEYUSAGE * EKUSAGE/*增强密钥用法*/,char *outfile/*结果文件*/,
			  char * outMsg/*操作结果*/,int type/*结果类型DER,PEM*/);//通过证书请求，得到证书

//直接生成公私钥
BOOL DirectCert(char *certfile/*根证书公钥*/,int certlen,/*为0则certfile为磁盘文件，否则为内存区域*/
			 char *keyfile/*根证书私钥*/,int keylen,int serial/*序列号*/,char *enddate/*作废日期*/,
			 int days/*有效期*/,stuCERT * sCERT/*用户信息与密钥用法*/,int bits,char * cert/*输出证书公钥*/,int * certl/*长度*/,
			 char * key/*输出证书私钥*/,int * keyl/*长度*/,char * outMsg/*,int type结果类型DER,PEM*/);//直接生成公私钥

/*黑名单生成函数*/
BOOL MakeCrl(char *certfile/*根证书公钥*/,int certlen,/*为0则certfile为磁盘文件，否则为内存区域*/
			  char *keyfile/*根证书私钥*/,int keylen,
			  stuREVOKE * Head/*作废链表*/,PNewCrlMem NewCrlMem/*回调函数*/,char *& outCrl,int * crll,char * outfile/*crl文件*/,
			  char * outMsg/*操作结果*/);

/*分解p12包*/
BOOL ParseDB(char * strP12/*包文件*/,char * strPwd/*解包密码*/,char * strCert/*公钥存放*/,
			 char * strkey/*私钥存放*/,int outformat/*输出格式*/,char * out/*返回结果*/);

/*组合p12包*/
BOOL CreateDB(char * strP12/*包文件IN*/,char * strPwd/*密码IN*/,char * strCert/*公钥存放IN*/,
			  char * strkey/*私钥存放IN*/,char * out/*返回结果OUT*/);

BOOL ChangePB(char * strP12/*IN包文件*/,char * strPwd/*IN原密码*/,char * strPwd2/*IN新密码*/,
			  char * strOutP12/*OUT包文件*/,char * out/*返回结果OUT*/);

//检验公钥、私钥是否配对
BOOL CertPairCheck(char * cert,char * key,char * out);//检验公钥、私钥是否配对
