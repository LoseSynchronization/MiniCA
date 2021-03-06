; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CUsbRaServer
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "usbkey.h"
LastPage=0

ClassCount=16
Class1=CColorListBox
Class2=CSslClientSocket
Class3=CSslServerSocket
Class4=CTextProgressCtrl
Class5=CUsbCaPage
Class6=CUsbCertPage
Class7=CUsbEvpPage
Class8=CUsbInfoPage
Class9=CUsbKeyApp
Class10=CUsbKeySheet
Class11=CUsbProcPage
Class12=CUsbPwdPage
Class13=CUsbRaServer
Class14=CUsbSoPage
Class15=CUsbSslClient
Class16=CUsbSslServer

ResourceCount=11
Resource1=IDD_PROPPAGE_SSLSERVER
Resource2=IDD_PROPPAGE_PWD
Resource3=IDD_PROPPAGE_RASERVER
Resource4=IDD_PROPPAGE_CA
Resource5=IDD_PROPPAGE_SO
Resource6=IDD_PROPPAGE_EVP
Resource7=IDD_PROPPAGE_PROC
Resource8=IDD_PROPPAGE_EXT
Resource9=IDD_PROPPAGE_KEYINFO
Resource10=IDD_PROPPAGE_SSLCLIENT
Resource11=IDR_MENU_INFO

[CLS:CColorListBox]
Type=0
BaseClass=CListBox
HeaderFile=ColorListBox.h
ImplementationFile=ColorListBox.cpp
LastObject=CColorListBox

[CLS:CSslClientSocket]
Type=0
BaseClass=CAsyncSocket
HeaderFile=SslClientSocket.h
ImplementationFile=SslClientSocket.cpp

[CLS:CSslServerSocket]
Type=0
BaseClass=CAsyncSocket
HeaderFile=SslServerSocket.h
ImplementationFile=SslServerSocket.cpp

[CLS:CTextProgressCtrl]
Type=0
BaseClass=CProgressCtrl
HeaderFile=TextProgressCtrl.h
ImplementationFile=TextProgressCtrl.cpp

[CLS:CUsbCaPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbCaPage.h
ImplementationFile=UsbCaPage.cpp

[CLS:CUsbCertPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbCertPage.h
ImplementationFile=UsbCertPage.cpp

[CLS:CUsbEvpPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbEvpPage.h
ImplementationFile=UsbEvpPage.cpp

[CLS:CUsbInfoPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbInfoPage.h
ImplementationFile=UsbInfoPage.cpp

[CLS:CUsbKeyApp]
Type=0
BaseClass=CWinApp
HeaderFile=UsbKey.h
ImplementationFile=UsbKey.cpp

[CLS:CUsbKeySheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=UsbKeySheet.h
ImplementationFile=UsbKeySheet.cpp

[CLS:CUsbProcPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbProcPage.h
ImplementationFile=UsbProcPage.cpp

[CLS:CUsbPwdPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbPwdPage.h
ImplementationFile=UsbPwdPage.cpp

[CLS:CUsbRaServer]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbRaServer.h
ImplementationFile=UsbRaServer.cpp
LastObject=CUsbRaServer

[CLS:CUsbSoPage]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbSoPage.h
ImplementationFile=UsbSoPage.cpp

[CLS:CUsbSslClient]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbSslClient.h
ImplementationFile=UsbSslClient.cpp

[CLS:CUsbSslServer]
Type=0
BaseClass=CPropertyPage
HeaderFile=UsbSslServer.h
ImplementationFile=UsbSslServer.cpp

[DLG:IDD_PROPPAGE_CA]
Type=1
Class=CUsbCaPage
ControlCount=34
Control1=IDC_EDIT_PATH,edit,1350631552
Control2=IDC_B_PATH,button,1342275584
Control3=IDC_EDIT_C,edit,1350631552
Control4=IDC_EDIT_ST,edit,1350631552
Control5=IDC_EDIT_L,edit,1350631552
Control6=IDC_EDIT_O,edit,1350631552
Control7=IDC_EDIT_OU,edit,1350631552
Control8=IDC_EDIT_CN,edit,1350631552
Control9=IDC_EDIT_E,edit,1350631552
Control10=IDC_COMBO_L,combobox,1344340226
Control11=IDC_EDIT_DAY,edit,1350631552
Control12=IDC_EDIT_SN,edit,1350631552
Control13=IDC_B_MKROOT,button,1342275584
Control14=IDC_B_MKREQ,button,1342275584
Control15=IDC_EDIT4,edit,1350631552
Control16=IDC_B_PATH4,button,1342275584
Control17=IDC_B_MKCERT,button,1342275584
Control18=IDC_B_CRL,button,1342275584
Control19=IDC_CHECK,button,1342275587
Control20=IDC_LIST_CA,listbox,1353777505
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,button,1342177287
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342177287
Control33=IDC_CHECK_P12,button,1342275587
Control34=IDC_B_MKCERT2,button,1342275584

[DLG:IDD_PROPPAGE_EXT]
Type=1
Class=CUsbCertPage
ControlCount=25
Control1=IDC_LIST_CERT,listbox,1353777505
Control2=IDC_STATIC,button,1342177287
Control3=IDC_BPTOD,button,1342275584
Control4=IDC_EDIT_PASSWORD,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_B_KEY,button,1342275584
Control7=IDC_B_PUB,button,1342275584
Control8=IDC_STATIC,button,1342177287
Control9=IDC_EDIT_PATH,edit,1350631552
Control10=IDC_B_PATH,button,1342275584
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_PASSWORD2,edit,1350631552
Control13=IDC_B_OK,button,1342275584
Control14=IDC_R_PARSE,button,1342341129
Control15=IDC_R_CREATE,button,1342210057
Control16=IDC_R_CHANGEP,button,1342210057
Control17=IDC_STATIC,button,1342177287
Control18=IDC_EDIT_P12,edit,1350631552
Control19=IDC_EDIT_KEY,edit,1350631552
Control20=IDC_BDTOP,button,1342275584
Control21=IDC_EDIT_INFILE,edit,1350631552
Control22=IDC_EDIT_OUTFILE,edit,1350631552
Control23=IDC_BSOUT,button,1342275584
Control24=IDC_BSIN,button,1342275584
Control25=IDC_B_CHECK,button,1342275584

[DLG:IDD_PROPPAGE_EVP]
Type=1
Class=CUsbEvpPage
ControlCount=21
Control1=IDC_LIST_EVP,listbox,1353777505
Control2=IDC_STATIC,button,1342177287
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,button,1342177287
Control5=IDC_EDIT_INFILE,edit,1350631552
Control6=IDC_EDIT_OUTFILE,edit,1350631552
Control7=IDC_BSOUT,button,1342275584
Control8=IDC_BSIN,button,1342275584
Control9=IDC_COMBO_CRYPT,combobox,1344339970
Control10=IDC_BENC,button,1342275584
Control11=IDC_BDEC,button,1342275584
Control12=IDC_BSEAL,button,1342275584
Control13=IDC_BOPENSEAL,button,1342275584
Control14=IDC_COMBO_DIGEST,combobox,1344339970
Control15=IDC_BDIGEST,button,1342275584
Control16=IDC_EDIT_DIGEST,edit,1342244992
Control17=IDC_BSIGN,button,1342275584
Control18=IDC_BVSIGN,button,1342275584
Control19=IDC_BRSACERT,button,1342275584
Control20=IDC_BRSAKEY,button,1342275584
Control21=IDC_PROGRESS,msctls_progress32,1342177281

[DLG:IDD_PROPPAGE_KEYINFO]
Type=1
Class=CUsbInfoPage
ControlCount=25
Control1=IDC_TREE,SysTreeView32,1350635683
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342177283
Control4=IDC_EDIT,edit,1342244992
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_STATIC,static,1342308352
Control12=IDC_EDIT_ID,edit,1342245000
Control13=IDC_EDIT_TYPE,edit,1342244992
Control14=IDC_EDIT_SPACE,edit,1342244992
Control15=IDC_EDIT_READ,edit,1342244992
Control16=IDC_EDIT_WRITE,edit,1342244992
Control17=IDC_STATIC,static,1342308352
Control18=IDC_EDIT_CRYPT,edit,1342244992
Control19=IDC_STATIC,static,1484787720
Control20=IDC_EDIT_INPUTID,edit,1350631552
Control21=IDC_B_OK,button,1342275584
Control22=IDC_B_CANLE,button,1342275584
Control23=IDC_STATIC,static,1342308352
Control24=IDC_LIST_INFO,listbox,1353777504
Control25=IDC_STATIC,static,1342308352

[DLG:IDD_PROPPAGE_PROC]
Type=1
Class=CUsbProcPage
ControlCount=20
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EDIT_RAND,edit,1350631552
Control3=IDC_B_GETRAND,button,1342275584
Control4=IDC_EDIT_LEN,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_LIST_PROC,listbox,1353777504
Control7=IDC_STATIC,static,1342177283
Control8=IDC_STATIC,button,1342177287
Control9=IDC_PROGRESS,msctls_progress32,1350565888
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDIT_INFILE,edit,1350631552
Control12=IDC_EDIT_OUTFILE,edit,1350631552
Control13=IDC_BSOUT,button,1342275584
Control14=IDC_BSIN,button,1342275584
Control15=IDC_BSIGN,button,1476493312
Control16=IDC_B_VERIFY,button,1476493312
Control17=IDC_B_SEAL,button,1476493312
Control18=IDC_B_OPEN,button,1476493312
Control19=IDC_B_ENC,button,1476493312
Control20=IDC_B_DEC,button,1476493312

[DLG:IDD_PROPPAGE_PWD]
Type=1
Class=CUsbPwdPage
ControlCount=27
Control1=IDC_STATIC,button,1342210055
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_UPWD2,edit,1350631584
Control4=IDC_B_VERUSER,button,1342275584
Control5=IDC_STATIC,button,1342341127
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_UPWD3,edit,1350697120
Control9=IDC_EDIT_UPWD4,edit,1350697120
Control10=IDC_B_MODPWD,button,1342275584
Control11=IDC_LIST,listbox,1353777504
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_EDIT_TESTMAX,edit,1342179456
Control15=IDC_EDIT_TESTCURRENT,edit,1342179456
Control16=IDC_STATIC_STATE,static,1342177283
Control17=IDC_STATIC,button,1342210055
Control18=IDC_STATIC,static,1342308352
Control19=IDC_EDIT_SPWD,edit,1350697120
Control20=IDC_B_VERSO,button,1342275584
Control21=IDC_STATIC,button,1342341127
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_EDIT_UPWD5,edit,1350697088
Control25=IDC_EDIT_UPWD6,edit,1350697088
Control26=IDC_B_MODPWD2,button,1342275584
Control27=IDC_STATIC,static,1342177283

[DLG:IDD_PROPPAGE_RASERVER]
Type=1
Class=CUsbRaServer
ControlCount=11
Control1=IDC_LISTEN,button,1476493312
Control2=IDC_LIST_SERVER,listbox,1353777504
Control3=IDC_STATIC_ON,static,1342177294
Control4=IDC_STATIC_OFF,static,1342177294
Control5=IDC_IPADDRESS_IP,SysIPAddress32,1342177280
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_PORT,edit,1350631552
Control10=IDC_LIST_SERVER2,listbox,1352728928
Control11=IDC_B_GETC,button,1342275584

[DLG:IDD_PROPPAGE_SO]
Type=1
Class=CUsbSoPage
ControlCount=32
Control1=IDC_STATIC,button,1342210055
Control2=IDC_B_UNLOCK,button,1342275584
Control3=IDC_BInitKey,button,1342275584
Control4=IDC_STATIC,button,1342210055
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_UPWD,edit,1350631584
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT_PATH,edit,1350631552
Control9=IDC_B_SELPATH,button,1342275584
Control10=IDC_STATIC,button,1342210055
Control11=IDC_B_WRITE,button,1342275584
Control12=IDC_STATIC,static,1342308352
Control13=IDC_EDIT_PRIPWD,edit,1350631584
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,button,1342210055
Control16=IDC_STATIC,button,1342210055
Control17=IDC_RADIO_ANYONE,button,1342341129
Control18=IDC_RADIO_PIN,button,1342210057
Control19=IDC_RADIO_SOPIN,button,1342210057
Control20=IDC_RADIO_NONE,button,1342210057
Control21=IDC_RADIO_ANYONE2,button,1342341129
Control22=IDC_RADIO_PIN2,button,1342210057
Control23=IDC_RADIO_SOPIN2,button,1342210057
Control24=IDC_RADIO_NONE2,button,1342210057
Control25=IDC_LIST_SO,listbox,1353777504
Control26=IDC_B_SET,button,1342275584
Control27=IDC_STATIC_SOLOCK,static,1342177283
Control28=IDC_B_FORMAT,button,1342275584
Control29=IDC_STATIC,static,1342177283
Control30=IDC_STATIC,static,1342308352
Control31=IDC_EDIT_PATH2,edit,1350631552
Control32=IDC_B_SELPATH2,button,1342275584

[DLG:IDD_PROPPAGE_SSLCLIENT]
Type=1
Class=CUsbSslClient
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_EDIT_PORT,edit,1350631552
Control4=IDC_B_CONNECT,button,1342275584
Control5=IDC_LIST_CLIENT,listbox,1353777504
Control6=IDC_B_DISCON,button,1342275584
Control7=IDC_EDIT_SEND,edit,1350631552
Control8=IDC_B_SEND,button,1476493312
Control9=IDC_COM_IP,combobox,1344339970

[DLG:IDD_PROPPAGE_SSLSERVER]
Type=1
Class=CUsbSslServer
ControlCount=12
Control1=IDC_LISTEN,button,1342275584
Control2=IDC_LIST_SERVER,listbox,1353777504
Control3=IDC_STATIC_ON,static,1342177294
Control4=IDC_STATIC_OFF,static,1342177294
Control5=IDC_IPADDRESS_IP,SysIPAddress32,1342177280
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_EDIT_PORT,edit,1350631552
Control10=IDC_CHECK,button,1342275587
Control11=IDC_LIST_SERVER2,listbox,1352728928
Control12=IDC_B_GETC,button,1342275584

[MNU:IDR_MENU_INFO]
Type=1
Class=?
Command1=ID_MENU_CREATEDIR
Command2=ID_MENU_DELDIR
Command3=ID_MENU_PUTFILE
Command4=ID_MENU_KEYFILE
Command5=ID_MENU_POPFILE
Command6=ID_MENU_DELFILE
CommandCount=6

