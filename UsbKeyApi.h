#include ".\epassapi.h"	//ep1kdl20.lib

#define DIR_ID 1000	//证书应用分区
#define FILE_PUB	1001//公钥文件
#define FILE_PRI	1002//私钥文件

#define MD5  0XAAAA
#define SHA1 0XBBBB

BOOL USBKey_Connect(EPAS_HANDLE * handle); //打开钥匙
BOOL USBKey_InitKey(EPAS_HANDLE hKey,LPBYTE lpOldPIN);
BOOL USBKey_VerifyPin(EPAS_HANDLE hKey,//目标USBKey设备句柄
                     WORD dwPINType,//口令标识符 HPIN-使用口令
                     LPBYTE lpPIN//待验证口令
					 );
BOOL  USBKey_ChangePin(
                     EPAS_HANDLE hKey,//目标Key的句柄。
                     WORD dwPINType,//口令标识符:HPIN-使用口令
                     LPBYTE lpOldPin,//旧口令
                     LPBYTE lpNewPin// 新口令
                    );
BOOL  USBKey_UnlockPin(
                     EPAS_HANDLE hKey,//目标Key的句柄。
                     WORD dwPINType,// 口令类型 HPIN-使用口令
                     LPBYTE lpUnlockPin// 解锁口令
                    );
BOOL USBKey_ReadCert(
                     EPAS_HANDLE hKey,//目标USBKey的句柄
                     DWORD dwCertType, //证书类型(1 -公钥证书) (0 -私钥证书)
                     LPBYTE lpCert, //证书数据
                     LPDWORD lpdwCertLen//证书的长度
                    );
BOOL USBKey_WriteCert (
                     EPAS_HANDLE hKey,//目标Key的句柄
                     DWORD dwCertType,//证书类型(1 -公钥证书) (0 -私钥证书)
                     LPBYTE lpCert,//证书数据
                     DWORD dwCertLen//证书的长度
                    );
BOOL USBKey_GetRandom(
                     EPAS_HANDLE hKey,//目标USBKey的句柄
                     DWORD dwRandomLen,//用户指定的随机数的长度
                     LPBYTE lpRandom//为函数返回的随机数
                    );
