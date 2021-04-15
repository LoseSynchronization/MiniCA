#define MAX_MD_SIZE			(16+20) /* The SSLv3 md5+sha1 type */
#define DER			    1 //FORMAT_ASN1
#define PEM			    3	/*�����ʽ*/
#define P12				5

typedef void (* PDrawProg)(int pos);

/*�Գ��㷨*/
bool Crypt(char * cpname/*�㷨����*/,char * filein/*�����ļ�*/, char * fileout/*����ļ�*/,
		   char * pwd/*���ڳ�ʼiv������*/, int type/*1-���ܡ�0-����*/,char * outMsg,
		   PDrawProg DrawProg=NULL);

/*��ϢժҪ*/
bool Digest(char * mdname/*ժҪ�㷨*/,char * filein/*�����ļ�*/,unsigned char * md_value/*����ժҪ*/,
			unsigned int * md_len/*ժҪ����*/, char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);

/*����ǩ��*/
bool Sign(char * key/*˽Կ*/,int keylen/*0-�ڴ�����*/,char * mdname/*ǩ���㷨*/,
		  char * filein/*�����ļ�*/,char * fileout/*����ļ�*/,char * outMsg,
		  PDrawProg DrawProg=NULL/*�ص�����*/);

/*����ǩ����֤*/
bool VerifySign(char * cert/*��Կ*/,int certlen,char * mdname/*ǩ���㷨*/,char * filesource,/*ԭʼ�ļ�*/ 
				char * filesign/*ǩ�����*/,char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);

/*�����ŷ�*/
bool Seal(char * cert/*��Կ*/,int certlen,char * cpname/*�㷨����*/,char * filein/*�����ļ�*/, 
		  char * fileout/*����ļ�*/,char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);

/*��������ŷ�*/
bool OpenSeal(char * key/*˽Կ*/,int keylen,char * cpname/*�㷨����*/,char * filein/*�����ļ�*/, 
		  char * fileout/*����ļ�*/,char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);

//��Կ����
bool RSAEnc(char * cert/*��Կ*/,int certlen,char * filein/*�����ļ�*/, 
		  char * fileout/*����ļ�*/,char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);

//˽Կ����
int RSADec(char * key,int keylen,char * filein/*�����ļ�*/, 
		  char * fileout/*����ļ�*/,char * outMsg,PDrawProg DrawProg=NULL/*�ص�����*/);




