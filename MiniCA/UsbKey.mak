# Microsoft Developer Studio Generated NMAKE File, Based on UsbKey.dsp
!IF "$(CFG)" == ""
CFG=UsbKey - Win32 Debug
!MESSAGE No configuration specified. Defaulting to UsbKey - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "UsbKey - Win32 Release" && "$(CFG)" != "UsbKey - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "UsbKey - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\UsbKey.exe"


CLEAN :
	-@erase "$(INTDIR)\ColorListBox.obj"
	-@erase "$(INTDIR)\SslClientSocket.obj"
	-@erase "$(INTDIR)\SslServerSocket.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TextProgressCtrl.obj"
	-@erase "$(INTDIR)\UsbCaPage.obj"
	-@erase "$(INTDIR)\UsbCertPage.obj"
	-@erase "$(INTDIR)\UsbEvpPage.obj"
	-@erase "$(INTDIR)\UsbInfoPage.obj"
	-@erase "$(INTDIR)\UsbKey.obj"
	-@erase "$(INTDIR)\UsbKey.pch"
	-@erase "$(INTDIR)\UsbKey.res"
	-@erase "$(INTDIR)\UsbKeySheet.obj"
	-@erase "$(INTDIR)\UsbProcPage.obj"
	-@erase "$(INTDIR)\UsbPwdPage.obj"
	-@erase "$(INTDIR)\UsbSoPage.obj"
	-@erase "$(INTDIR)\UsbSslClient.obj"
	-@erase "$(INTDIR)\UsbSslServer.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\UsbKey.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\UsbKey.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\UsbKey.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UsbKey.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\UsbKey.pdb" /machine:I386 /out:"$(OUTDIR)\UsbKey.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ColorListBox.obj" \
	"$(INTDIR)\SslClientSocket.obj" \
	"$(INTDIR)\SslServerSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextProgressCtrl.obj" \
	"$(INTDIR)\UsbCaPage.obj" \
	"$(INTDIR)\UsbCertPage.obj" \
	"$(INTDIR)\UsbEvpPage.obj" \
	"$(INTDIR)\UsbInfoPage.obj" \
	"$(INTDIR)\UsbKey.obj" \
	"$(INTDIR)\UsbKeySheet.obj" \
	"$(INTDIR)\UsbProcPage.obj" \
	"$(INTDIR)\UsbPwdPage.obj" \
	"$(INTDIR)\UsbSoPage.obj" \
	"$(INTDIR)\UsbSslClient.obj" \
	"$(INTDIR)\UsbSslServer.obj" \
	"$(INTDIR)\UsbKey.res" \
	"..\备份\lib\ep1kdl20.lib" \
	"..\SockError\Release\SocketErrDll.lib" \
	"..\UsbKeyApi\Release\UsbKeyApi.lib" \
	"..\openssl\ssleay32.lib" \
	"..\openssl\libeay32.lib" \
	".\CA\Debug\CA.lib" \
	".\Evp\Debug\Evp.lib"

"$(OUTDIR)\UsbKey.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\UsbKey.exe" "$(OUTDIR)\UsbKey.bsc"


CLEAN :
	-@erase "$(INTDIR)\ColorListBox.obj"
	-@erase "$(INTDIR)\ColorListBox.sbr"
	-@erase "$(INTDIR)\SslClientSocket.obj"
	-@erase "$(INTDIR)\SslClientSocket.sbr"
	-@erase "$(INTDIR)\SslServerSocket.obj"
	-@erase "$(INTDIR)\SslServerSocket.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TextProgressCtrl.obj"
	-@erase "$(INTDIR)\TextProgressCtrl.sbr"
	-@erase "$(INTDIR)\UsbCaPage.obj"
	-@erase "$(INTDIR)\UsbCaPage.sbr"
	-@erase "$(INTDIR)\UsbCertPage.obj"
	-@erase "$(INTDIR)\UsbCertPage.sbr"
	-@erase "$(INTDIR)\UsbEvpPage.obj"
	-@erase "$(INTDIR)\UsbEvpPage.sbr"
	-@erase "$(INTDIR)\UsbInfoPage.obj"
	-@erase "$(INTDIR)\UsbInfoPage.sbr"
	-@erase "$(INTDIR)\UsbKey.obj"
	-@erase "$(INTDIR)\UsbKey.pch"
	-@erase "$(INTDIR)\UsbKey.res"
	-@erase "$(INTDIR)\UsbKey.sbr"
	-@erase "$(INTDIR)\UsbKeySheet.obj"
	-@erase "$(INTDIR)\UsbKeySheet.sbr"
	-@erase "$(INTDIR)\UsbProcPage.obj"
	-@erase "$(INTDIR)\UsbProcPage.sbr"
	-@erase "$(INTDIR)\UsbPwdPage.obj"
	-@erase "$(INTDIR)\UsbPwdPage.sbr"
	-@erase "$(INTDIR)\UsbSoPage.obj"
	-@erase "$(INTDIR)\UsbSoPage.sbr"
	-@erase "$(INTDIR)\UsbSslClient.obj"
	-@erase "$(INTDIR)\UsbSslClient.sbr"
	-@erase "$(INTDIR)\UsbSslServer.obj"
	-@erase "$(INTDIR)\UsbSslServer.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\UsbKey.bsc"
	-@erase "$(OUTDIR)\UsbKey.exe"
	-@erase "$(OUTDIR)\UsbKey.ilk"
	-@erase "$(OUTDIR)\UsbKey.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UsbKey.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\UsbKey.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\UsbKey.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ColorListBox.sbr" \
	"$(INTDIR)\SslClientSocket.sbr" \
	"$(INTDIR)\SslServerSocket.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TextProgressCtrl.sbr" \
	"$(INTDIR)\UsbCaPage.sbr" \
	"$(INTDIR)\UsbCertPage.sbr" \
	"$(INTDIR)\UsbEvpPage.sbr" \
	"$(INTDIR)\UsbInfoPage.sbr" \
	"$(INTDIR)\UsbKey.sbr" \
	"$(INTDIR)\UsbKeySheet.sbr" \
	"$(INTDIR)\UsbProcPage.sbr" \
	"$(INTDIR)\UsbPwdPage.sbr" \
	"$(INTDIR)\UsbSoPage.sbr" \
	"$(INTDIR)\UsbSslClient.sbr" \
	"$(INTDIR)\UsbSslServer.sbr"

"$(OUTDIR)\UsbKey.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\UsbKey.pdb" /debug /machine:I386 /out:"$(OUTDIR)\UsbKey.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ColorListBox.obj" \
	"$(INTDIR)\SslClientSocket.obj" \
	"$(INTDIR)\SslServerSocket.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TextProgressCtrl.obj" \
	"$(INTDIR)\UsbCaPage.obj" \
	"$(INTDIR)\UsbCertPage.obj" \
	"$(INTDIR)\UsbEvpPage.obj" \
	"$(INTDIR)\UsbInfoPage.obj" \
	"$(INTDIR)\UsbKey.obj" \
	"$(INTDIR)\UsbKeySheet.obj" \
	"$(INTDIR)\UsbProcPage.obj" \
	"$(INTDIR)\UsbPwdPage.obj" \
	"$(INTDIR)\UsbSoPage.obj" \
	"$(INTDIR)\UsbSslClient.obj" \
	"$(INTDIR)\UsbSslServer.obj" \
	"$(INTDIR)\UsbKey.res" \
	"..\备份\lib\ep1kdl20.lib" \
	"..\SockError\Release\SocketErrDll.lib" \
	"..\UsbKeyApi\Release\UsbKeyApi.lib" \
	"..\openssl\ssleay32.lib" \
	"..\openssl\libeay32.lib" \
	".\CA\Debug\CA.lib" \
	".\Evp\Debug\Evp.lib"

"$(OUTDIR)\UsbKey.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("UsbKey.dep")
!INCLUDE "UsbKey.dep"
!ELSE 
!MESSAGE Warning: cannot find "UsbKey.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "UsbKey - Win32 Release" || "$(CFG)" == "UsbKey - Win32 Debug"
SOURCE=.\ColorListBox.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\ColorListBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\ColorListBox.obj"	"$(INTDIR)\ColorListBox.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\SslClientSocket.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\SslClientSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\SslClientSocket.obj"	"$(INTDIR)\SslClientSocket.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\SslServerSocket.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\SslServerSocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\SslServerSocket.obj"	"$(INTDIR)\SslServerSocket.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /Fp"$(INTDIR)\UsbKey.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\UsbKey.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\UsbKey.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\UsbKey.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TextProgressCtrl.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\TextProgressCtrl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\TextProgressCtrl.obj"	"$(INTDIR)\TextProgressCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbCaPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbCaPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbCaPage.obj"	"$(INTDIR)\UsbCaPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbCertPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbCertPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbCertPage.obj"	"$(INTDIR)\UsbCertPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbEvpPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbEvpPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbEvpPage.obj"	"$(INTDIR)\UsbEvpPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbInfoPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbInfoPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbInfoPage.obj"	"$(INTDIR)\UsbInfoPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbKey.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbKey.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbKey.obj"	"$(INTDIR)\UsbKey.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbKey.rc

"$(INTDIR)\UsbKey.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\UsbKeySheet.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbKeySheet.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbKeySheet.obj"	"$(INTDIR)\UsbKeySheet.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbProcPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbProcPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbProcPage.obj"	"$(INTDIR)\UsbProcPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbPwdPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbPwdPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbPwdPage.obj"	"$(INTDIR)\UsbPwdPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbSoPage.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbSoPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbSoPage.obj"	"$(INTDIR)\UsbSoPage.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbSslClient.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbSslClient.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbSslClient.obj"	"$(INTDIR)\UsbSslClient.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 

SOURCE=.\UsbSslServer.cpp

!IF  "$(CFG)" == "UsbKey - Win32 Release"


"$(INTDIR)\UsbSslServer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ELSEIF  "$(CFG)" == "UsbKey - Win32 Debug"


"$(INTDIR)\UsbSslServer.obj"	"$(INTDIR)\UsbSslServer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\UsbKey.pch"


!ENDIF 


!ENDIF 

