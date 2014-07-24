# Microsoft Developer Studio Project File - Name="autogen" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=autogen - Win32 Local
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "autogen.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "autogen.mak" CFG="autogen - Win32 Local"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "autogen - Win32 Product" (based on "Win32 (x86) Console Application")
!MESSAGE "autogen - Win32 Symbian" (based on "Win32 (x86) Console Application")
!MESSAGE "autogen - Win32 Local" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 1
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Product"
# PROP BASE Intermediate_Dir "Product"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Product"
# PROP Intermediate_Dir "Product"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "AUTOGEN_ENVIRONMENT_PRODUCT_MCU" /FR /YX /FD /GZ /GZ /Zm200 /c
# ADD CPP /nologo /Za /W4 /GX /ZI /Od /I "..\..\..\include" /I "..\..\..\config" /I "..\..\..\ta_common" /I "product includes" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "AUTOGEN_ENVIRONMENT_PRODUCT_MCU" /FR /YX /FD /GZ /Zm200 /GZ /Zm200 /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "autogen___Win32_Symbian"
# PROP BASE Intermediate_Dir "autogen___Win32_Symbian"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "autogen___Win32_Symbian"
# PROP Intermediate_Dir "autogen___Win32_Symbian"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Za /W4 /GX /ZI /Od /I "product includes" /I "..\..\..\include" /I "..\..\..\config" /I "..\..\..\ta_common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN" /FR /YX /FD /GZ /Zm200 /GZ /Zm200 /c
# ADD CPP /nologo /Za /W4 /GX /ZI /Od /I "..\autogen_includes_product" /I "..\..\..\include" /I "..\..\..\config" /I "..\..\..\ta_common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "AUTOGEN_ENVIRONMENT_PRODUCT_SYMBIAN" /FR /YX /FD /GZ /Zm200 /GZ /Zm200 /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT BASE LINK32 /profile
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /profile

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Local"
# PROP BASE Intermediate_Dir "Local"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Local"
# PROP Intermediate_Dir "Local"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W4 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "AUTOGEN_ENVIRONMENT_LOCAL" /FR /YX /FD /GZ /GZ /Zm200 /c
# ADD CPP /nologo /Za /W4 /GX /ZI /Od /I "product includes" /I "..\..\..\include" /I "..\..\..\config" /I "..\..\..\ta_common" /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /FR /YX /FD /GZ /Zm200 /GZ /Zm200 /c
# ADD BASE RSC /l 0x406 /d "_DEBUG"
# ADD RSC /l 0x406 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /profile /debug /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386
# SUBTRACT LINK32 /profile

!ENDIF 

# Begin Target

# Name "autogen - Win32 Product"
# Name "autogen - Win32 Symbian"
# Name "autogen - Win32 Local"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\autogen_check.c
# End Source File
# Begin Source File

SOURCE=.\autogen_coresw.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw2.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw3.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw4.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw_cl.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw_mon.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_def.c
# End Source File
# Begin Source File

SOURCE=.\autogen_dsp.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_iam.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_iam2.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_iam3.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_init.c
# End Source File
# Begin Source File

SOURCE=.\autogen_main.c
# End Source File
# Begin Source File

SOURCE=.\autogen_object.c
# End Source File
# Begin Source File

SOURCE=.\autogen_prop.c
# End Source File
# Begin Source File

SOURCE=.\autogen_protocols.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols2.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols3.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_eutran.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_gsm.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_wcdma.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_ref.c
# End Source File
# Begin Source File

SOURCE=.\autogen_symbols.c
# End Source File
# Begin Source File

SOURCE=.\autogen_user.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_user_local.c

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_util.c
# End Source File
# Begin Source File

SOURCE=.\autogen_ver_history.c

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\output_html.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\output_pmd.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_debug.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_elf.c

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\output_pmd_generate.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_info.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_msg.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_typedef_hierarchy.c
# End Source File
# Begin Source File

SOURCE=.\output_pmd_types.c
# End Source File
# Begin Source File

SOURCE=.\output_srvhdr.c

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\output_tsa.c

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\output_xml.c

!IF  "$(CFG)" == "autogen - Win32 Product"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\pmd_compression2.c
# End Source File
# Begin Source File

SOURCE=.\pmd_constants.c
# End Source File
# Begin Source File

SOURCE=.\pmd_heap.c
# End Source File
# Begin Source File

SOURCE=.\pmd_stringpool.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\autogen_check.h
# End Source File
# Begin Source File

SOURCE=.\autogen_coresw.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw2.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw3.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw_cl.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_coresw_mon.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_def.h
# End Source File
# Begin Source File

SOURCE=.\autogen_dsp.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_iam.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_init.h
# End Source File
# Begin Source File

SOURCE=.\autogen_object.h
# End Source File
# Begin Source File

SOURCE=.\autogen_prop.h
# End Source File
# Begin Source File

SOURCE=.\autogen_protocols.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_eutran.h
# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_gsm.h
# End Source File
# Begin Source File

SOURCE=.\autogen_protocols_wcdma.h
# End Source File
# Begin Source File

SOURCE=.\autogen_ref.h
# End Source File
# Begin Source File

SOURCE=.\autogen_util.h
# End Source File
# Begin Source File

SOURCE=.\isi_macros.h
# End Source File
# Begin Source File

SOURCE=.\isi_macros_empty.h
# End Source File
# Begin Source File

SOURCE=.\output_pmd.h
# End Source File
# Begin Source File

SOURCE=.\pmd_compression2.h
# End Source File
# Begin Source File

SOURCE=.\pmd_heap.h
# End Source File
# Begin Source File

SOURCE=.\pmd_stringpool.h
# End Source File
# Begin Source File

SOURCE=.\pmdconstants.h
# End Source File
# End Group
# Begin Group "Configuration files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\autogen_local_server_conf.h
# End Source File
# Begin Source File

SOURCE=.\autogen_server_conf.h
# End Source File
# Begin Source File

SOURCE=.\autogen_ti_conf.h
# End Source File
# End Group
# Begin Group "Example configuration files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\example_autogen_server_conf.h
# End Source File
# Begin Source File

SOURCE=.\example_autogen_ti_conf.h
# End Source File
# End Group
# Begin Group "Message Definition Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=.\autogen_ostrich.h

!IF  "$(CFG)" == "autogen - Win32 Product"

!ELSEIF  "$(CFG)" == "autogen - Win32 Symbian"

# PROP BASE Exclude_From_Build 1
# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "autogen - Win32 Local"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\autogen_symbols.h
# End Source File
# End Group
# Begin Group "Release Notes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\autogen_rel.txt
# End Source File
# Begin Source File

SOURCE=.\autogen_user_guide.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\autogen.log
# End Source File
# End Target
# End Project
