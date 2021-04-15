# Microsoft Developer Studio Project File - Name="Raclient" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Raclient - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Raclient.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Raclient.mak" CFG="Raclient - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Raclient - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Raclient - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Raclient - Win32 Release"

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
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Raclient - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\openssl" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Raclient - Win32 Release"
# Name "Raclient - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AuditingCertView.cpp
# End Source File
# Begin Source File

SOURCE=.\ColorListBox.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBar.cpp
# End Source File
# Begin Source File

SOURCE=.\IconBtn.cpp
# End Source File
# Begin Source File

SOURCE=.\InputCertView.cpp
# End Source File
# Begin Source File

SOURCE=.\LogDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\MadeCertView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ProgStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\RaChildFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\Raclient.cpp
# End Source File
# Begin Source File

SOURCE=.\Raclient.rc
# End Source File
# Begin Source File

SOURCE=.\RevokeCertView.cpp
# End Source File
# Begin Source File

SOURCE=.\SslClientSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AuditingCertView.h
# End Source File
# Begin Source File

SOURCE=.\ColorListBox.h
# End Source File
# Begin Source File

SOURCE=.\DlgBar.h
# End Source File
# Begin Source File

SOURCE=.\IconBtn.h
# End Source File
# Begin Source File

SOURCE=.\InputCertView.h
# End Source File
# Begin Source File

SOURCE=.\LogDlg.h
# End Source File
# Begin Source File

SOURCE=.\MadeCertView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\ProgStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\RaChildFrame.h
# End Source File
# Begin Source File

SOURCE=.\Raclient.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RevokeCertView.h
# End Source File
# Begin Source File

SOURCE=.\SslClientSocket.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\1.ico
# End Source File
# Begin Source File

SOURCE=.\res\10.ico
# End Source File
# Begin Source File

SOURCE=.\res\11.ico
# End Source File
# Begin Source File

SOURCE=.\res\12.ico
# End Source File
# Begin Source File

SOURCE=.\res\13.ico
# End Source File
# Begin Source File

SOURCE=.\res\14.ico
# End Source File
# Begin Source File

SOURCE=.\res\15.ico
# End Source File
# Begin Source File

SOURCE=.\res\16.ico
# End Source File
# Begin Source File

SOURCE=.\res\17.ico
# End Source File
# Begin Source File

SOURCE=.\res\2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\2.ico
# End Source File
# Begin Source File

SOURCE=.\res\3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\41.ico
# End Source File
# Begin Source File

SOURCE=.\res\81.ICO
# End Source File
# Begin Source File

SOURCE=.\res\addu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\audit.ico
# End Source File
# Begin Source File

SOURCE=.\res\auditpass.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BITMAPAUDVIEW.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\BOOK01A.ICO
# End Source File
# Begin Source File

SOURCE=.\res\BOOK01B.ICO
# End Source File
# Begin Source File

SOURCE=.\res\cancle.bmp
# End Source File
# Begin Source File

SOURCE=.\res\canlel.bmp
# End Source File
# Begin Source File

SOURCE=.\res\canlelbig.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cert.ico
# End Source File
# Begin Source File

SOURCE=.\res\crl.ico
# End Source File
# Begin Source File

SOURCE=.\res\EOapp.ico
# End Source File
# Begin Source File

SOURCE=.\res\error.ico
# End Source File
# Begin Source File

SOURCE=.\res\Find.ico
# End Source File
# Begin Source File

SOURCE=.\res\fmade.ico
# End Source File
# Begin Source File

SOURCE=.\res\HELP.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon5.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon7.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon9.ico
# End Source File
# Begin Source File

SOURCE=".\res\input ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\input.bmp
# End Source File
# Begin Source File

SOURCE=.\res\input.ico
# End Source File
# Begin Source File

SOURCE=.\res\inputc.ico
# End Source File
# Begin Source File

SOURCE=.\res\inputviewuser.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LEDOFF.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LEDON.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LOG.ico
# End Source File
# Begin Source File

SOURCE=.\res\logc.ico
# End Source File
# Begin Source File

SOURCE=.\res\made.ico
# End Source File
# Begin Source File

SOURCE=.\res\madecert.bmp
# End Source File
# Begin Source File

SOURCE=.\res\makecrl.ico
# End Source File
# Begin Source File

SOURCE=.\res\MISC26.ICO
# End Source File
# Begin Source File

SOURCE=".\res\Network Drive Connected.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Network Drive Offline.ico"
# End Source File
# Begin Source File

SOURCE=.\res\NO.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ok.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Ok.ico
# End Source File
# Begin Source File

SOURCE=.\res\pass.bmp
# End Source File
# Begin Source File

SOURCE=.\res\printok.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Raclient.ico
# End Source File
# Begin Source File

SOURCE=.\res\Raclient.rc2
# End Source File
# Begin Source File

SOURCE=.\res\revoke.ico
# End Source File
# Begin Source File

SOURCE=".\res\Rich Text Format.ico"
# End Source File
# Begin Source File

SOURCE=.\res\SECUR08.ICO
# End Source File
# Begin Source File

SOURCE=".\res\Text Document.ico"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=".\res\view ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\view.bmp
# End Source File
# Begin Source File

SOURCE=".\res\viewmade ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\viewmade.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Waring.ico
# End Source File
# Begin Source File

SOURCE=".\res\µÇÂ¼.ico"
# End Source File
# Begin Source File

SOURCE=".\res\¸´ÖÆ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\¹ØÓÚ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\¼ôÇÐ.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ÀúÊ·.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ÉêÇë.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ÉóºË.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Î´±êÌâ-1 ¿½±´.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Î´ÃüÃû.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\ÐÅÏ¢.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Õ³Ìù.ico"
# End Source File
# Begin Source File

SOURCE=".\res\ÖÆ×÷.ico"
# End Source File
# Begin Source File

SOURCE=".\res\×¢Ïú.ico"
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\ClientCert.pem
# End Source File
# Begin Source File

SOURCE=.\res\ClientPriKey.pem
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\libeay32.lib
# End Source File
# Begin Source File

SOURCE=..\ssleay32.lib
# End Source File
# End Target
# End Project
