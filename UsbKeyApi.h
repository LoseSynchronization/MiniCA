#include ".\epassapi.h"	//ep1kdl20.lib

#define DIR_ID 1000	//֤��Ӧ�÷���
#define FILE_PUB	1001//��Կ�ļ�
#define FILE_PRI	1002//˽Կ�ļ�

#define MD5  0XAAAA
#define SHA1 0XBBBB

BOOL USBKey_Connect(EPAS_HANDLE * handle); //��Կ��
BOOL USBKey_InitKey(EPAS_HANDLE hKey,LPBYTE lpOldPIN);
BOOL USBKey_VerifyPin(EPAS_HANDLE hKey,//Ŀ��USBKey�豸���
                     WORD dwPINType,//�����ʶ�� HPIN-ʹ�ÿ���
                     LPBYTE lpPIN//����֤����
					 );
BOOL  USBKey_ChangePin(
                     EPAS_HANDLE hKey,//Ŀ��Key�ľ����
                     WORD dwPINType,//�����ʶ��:HPIN-ʹ�ÿ���
                     LPBYTE lpOldPin,//�ɿ���
                     LPBYTE lpNewPin// �¿���
                    );
BOOL  USBKey_UnlockPin(
                     EPAS_HANDLE hKey,//Ŀ��Key�ľ����
                     WORD dwPINType,// �������� HPIN-ʹ�ÿ���
                     LPBYTE lpUnlockPin// ��������
                    );
BOOL USBKey_ReadCert(
                     EPAS_HANDLE hKey,//Ŀ��USBKey�ľ��
                     DWORD dwCertType, //֤������(1 -��Կ֤��) (0 -˽Կ֤��)
                     LPBYTE lpCert, //֤������
                     LPDWORD lpdwCertLen//֤��ĳ���
                    );
BOOL USBKey_WriteCert (
                     EPAS_HANDLE hKey,//Ŀ��Key�ľ��
                     DWORD dwCertType,//֤������(1 -��Կ֤��) (0 -˽Կ֤��)
                     LPBYTE lpCert,//֤������
                     DWORD dwCertLen//֤��ĳ���
                    );
BOOL USBKey_GetRandom(
                     EPAS_HANDLE hKey,//Ŀ��USBKey�ľ��
                     DWORD dwRandomLen,//�û�ָ����������ĳ���
                     LPBYTE lpRandom//Ϊ�������ص������
                    );
