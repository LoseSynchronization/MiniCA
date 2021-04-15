# Microsoft Developer Studio Project File - Name="UsbKey" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=UsbKey - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "UsbKey.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "UsbKey.mak" CFG="UsbKey - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "UsbKey - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "UsbKey - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "UsbKey - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\openssl" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386 /out:"Release/MiniCA.exe"

!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\openssl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /out:"Debug/MiniCA.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "UsbKey - Win32 Release"
# Name "UsbKey - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ColorListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\SslClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\SslServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbCaPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbCertPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbEvpPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbInfoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbKey.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbKey.rc
# End Source File
# Begin Source File

SOURCE=.\UsbKeySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbProcPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbPwdPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbRaServer.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbSoPage.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbSslClient.cpp
# End Source File
# Begin Source File

SOURCE=.\UsbSslServer.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ColorListBox.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SslClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\SslServerSocket.h
# End Source File
# Begin Source File

SOURCE=.\SslSocket.h
# End Source File
# Begin Source File

SOURCE=.\SslStruct.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TextProgressCtrl.h
# End Source File
# Begin Source File

SOURCE=.\UsbCaPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbCertPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbEvpPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbInfoPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbKey.h
# End Source File
# Begin Source File

SOURCE=.\UsbKeySheet.h
# End Source File
# Begin Source File

SOURCE=.\UsbProcPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbPwdPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbRaServer.h
# End Source File
# Begin Source File

SOURCE=.\UsbSoPage.h
# End Source File
# Begin Source File

SOURCE=.\UsbSslClient.h
# End Source File
# Begin Source File

SOURCE=.\UsbSslServer.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ca.ICO
# End Source File
# Begin Source File

SOURCE=.\res\cert.ico
# End Source File
# Begin Source File

SOURCE=.\res\client.ico
# End Source File
# Begin Source File

SOURCE=.\res\d_close.ICO
# End Source File
# Begin Source File

SOURCE=.\res\d_open.ico
# End Source File
# Begin Source File

SOURCE=.\res\device.ICO
# End Source File
# Begin Source File

SOURCE=.\res\DEVTOOL.ICO
# End Source File
# Begin Source File

SOURCE=.\res\DISK.ICO
# End Source File
# Begin Source File

SOURCE=.\res\error.ico
# End Source File
# Begin Source File

SOURCE=.\res\EVP.ico
# End Source File
# Begin Source File

SOURCE=.\res\File.ICO
# End Source File
# Begin Source File

SOURCE=.\res\FORMAT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\ID.ico
# End Source File
# Begin Source File

SOURCE=.\res\K.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Key.ICO
# End Source File
# Begin Source File

SOURCE=.\res\LEDOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LEDON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LOCK.ico
# End Source File
# Begin Source File

SOURCE=.\res\Ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\Oth017.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PWD.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Ra.ico
# End Source File
# Begin Source File

SOURCE=.\res\root.ICO
# End Source File
# Begin Source File

SOURCE=.\res\server.ICO
# End Source File
# Begin Source File

SOURCE=.\res\SO.ico
# End Source File
# Begin Source File

SOURCE=.\res\UNLOCK.ico
# End Source File
# Begin Source File

SOURCE=.\res\UsbKey.ico
# End Source File
# Begin Source File

SOURCE=.\res\UsbKey.rc2
# End Source File
# Begin Source File

SOURCE=.\res\VERIFY.ico
# End Source File
# Begin Source File

SOURCE=.\res\Waring.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\ClientCert.pem
# End Source File
# Begin Source File

SOURCE=..\Raclient\res\ClientCert.pem
# End Source File
# Begin Source File

SOURCE=.\res\ClientPriKey.pem
# End Source File
# Begin Source File

SOURCE=..\Raclient\res\ClientPriKey.pem
# End Source File
# Begin Source File

SOURCE=.\res\index.htm
# End Source File
# Begin Source File

SOURCE=.\res\Key
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\res\RootCert.pem
# End Source File
# Begin Source File

SOURCE=.\res\RootKey.pem
# End Source File
# Begin Source File

SOURCE=.\res\ServerCert.PEM
# End Source File
# Begin Source File

SOURCE=.\res\ServerKey.PEM
# End Source File
# Begin Source File

SOURCE=..\UsbKeyApi.lib
# End Source File
# Begin Source File

SOURCE=..\ep1kdl20.lib
# End Source File
# Begin Source File

SOURCE=..\Evp.lib
# End Source File
# Begin Source File

SOURCE=..\SocketErrDll.lib
# End Source File
# Begin Source File

SOURCE=..\CA.lib
# End Source File
# Begin Source File

SOURCE=..\ssleay32.lib
# End Source File
# Begin Source File

SOURCE=..\libeay32.lib
# End Source File
# End Target
# End Project
