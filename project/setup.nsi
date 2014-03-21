Name Open-Transactions

RequestExecutionLevel admin
SetCompressor /SOLID lzma

!define NAME Open-Transactions

# General Symbol Definitions
!define REGKEY "SOFTWARE\${NAME}"
!define /file VERSION ..\VERSION
!define COMPANY "Open Transactions"
!define URL https://github.com/FellowTraveler/Open-Transactions

# MUI Symbol Definitions
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_RIGHT
!define MUI_FINISHPAGE_NOAUTOCLOSE
!define MUI_STARTMENUPAGE_REGISTRY_ROOT HKLM
!define MUI_STARTMENUPAGE_REGISTRY_KEY ${REGKEY}
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME StartMenuGroup
!define MUI_STARTMENUPAGE_DEFAULTFOLDER Open-Transactions
!define MUI_UNFINISHPAGE_NOAUTOCLOSE

# Included files
!include Sections.nsh
!include MUI2.nsh
!include "Library.nsh"
!include "x64.nsh"

# Variables
Var StartMenuGroup

# Installer pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_STARTMENU Application $StartMenuGroup
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH
!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

# Installer languages
!insertmacro MUI_LANGUAGE English

# Installer attributes
OutFile ${NAME}-${VERSION}-Win32-setup.exe
InstallDir $PROGRAMFILES\${NAME}
CRCCheck on
XPStyle on
BrandingText " "
ShowInstDetails show
VIProductVersion "0.91.3.0"
VIAddVersionKey ProductName "${NAME}"
VIAddVersionKey ProductVersion ${VERSION}
VIAddVersionKey CompanyName "${COMPANY}"
VIAddVersionKey CompanyWebsite "${URL}"
VIAddVersionKey FileVersion ${VERSION}
VIAddVersionKey FileDescription ""
VIAddVersionKey LegalCopyright ""
InstallDirRegKey HKLM "${REGKEY}" Path
ShowUninstDetails show





# Installer sections
Section -Main SEC0000

    SetOutPath $INSTDIR
    SetOverwrite on

## DLL's

# OpenSSL
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\OpenSSL-Win32\libeay32.dll $INSTDIR\libeay32.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\OpenSSL-Win32\ssleay32.dll $INSTDIR\ssleay32.dll $INSTDIR

# MSVC Runtime v120
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED "C:\windows\winsxs\x86_microsoft.vc90.crt_1fc8b3b9a1e18e3b_9.0.30729.8387_none_5094ca96bcb6b2bb\msvcr90.dll" $INSTDIR\msvcr90.dll $INSTDIR

# MSVC Runtime v120
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcp120.dll" $INSTDIR\msvcp120.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\msvcr120.dll" $INSTDIR\msvcr120.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\redist\x86\Microsoft.VC120.CRT\vccorlib120.dll" $INSTDIR\vccorlib120.dll $INSTDIR

# Chaiscript
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED ..\lib\Win32\Release\chaiscript_stdlib.dll $INSTDIR\chaiscript_stdlib.dll $INSTDIR

# ZMQ
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED ..\lib\Win32\Release\libzmq.dll $INSTDIR\libzmq.dll $INSTDIR

# QT
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\Qt5Widgets.dll $INSTDIR\Qt5Widgets.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\Qt5Network.dll $INSTDIR\Qt5Network.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\Qt5Sql.dll $INSTDIR\Qt5Sql.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\Qt5Gui.dll $INSTDIR\Qt5Gui.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\libEGL.dll $INSTDIR\libEGL.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\libGLESv2.dll $INSTDIR\libGLESv2.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\bin\Qt5Core.dll $INSTDIR\Qt5Core.dll $INSTDIR

# OT
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED ..\lib\Win32\Release\otapi.dll $INSTDIR\otapi.dll $INSTDIR
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED ..\lib\Win32\Release\otlib.dll $INSTDIR\otlib.dll $INSTDIR

    File ..\lib\Win32\Release\otmint.exe
    File ..\lib\Win32\Release\ot.exe
    File ..\lib\Win32\Release\otserver.exe

# Moneychanger

    File ..\lib\Win32\Release\moneychanger-qt.exe

# QT Plugins
SetOutPath $INSTDIR\platforms
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\plugins\platforms\qwindows.dll $INSTDIR\platforms\qwindows.dll $INSTDIR

SetOutPath $INSTDIR\sqldrivers
!insertmacro InstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED C:\qt5\plugins\sqldrivers\qsqlite.dll $INSTDIR\sqldrivers\qsqlite.dll $INSTDIR

# Scripts

    SetOutPath $INSTDIR\scripts
    File /r ..\scripts\*

# Docs

    SetOutPath $INSTDIR\docs
    File ..\docs\CLIENT-COMMANDS.txt
    File ..\docs\INSTALL-Windows.txt
    File ..\docs\LICENSE-AND-CREDITS.txt
    File ..\docs\RELEASE-NOTES.txt
    File ..\docs\SECURITY.txt
    File ..\docs\SSL-NOTES.txt
    File ..\docs\WIPE-USERS-ACCOUNTS.txt

    SetOutPath $INSTDIR
    WriteRegStr HKLM "${REGKEY}\Components" Main 1

SectionEnd

Section -post SEC0001
    WriteRegStr HKLM "${REGKEY}" Path $INSTDIR
    SetOutPath $INSTDIR
    WriteUninstaller $INSTDIR\uninstall.exe

    !insertmacro MUI_STARTMENU_WRITE_BEGIN Application
    SetShellVarContext all
    CreateDirectory $SMPROGRAMS\$StartMenuGroup
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Moneychanger.lnk" "$INSTDIR\moneychanger-qt.exe"
    CreateShortcut "$SMPROGRAMS\$StartMenuGroup\Uninstall ${NAME} Win32.lnk" $INSTDIR\uninstall.exe
    !insertmacro MUI_STARTMENU_WRITE_END

    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" DisplayName "${NAME} Win32"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" DisplayVersion "${VERSION}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" Publisher "${COMPANY}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" URLInfoAbout "${URL}"
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" DisplayIcon $INSTDIR\uninstall.exe
    WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" UninstallString $INSTDIR\uninstall.exe
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" NoModify 1
    WriteRegDWORD HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" NoRepair 1
SectionEnd

# Macro for selecting uninstaller sections
!macro SELECT_UNSECTION SECTION_NAME UNSECTION_ID
    Push $R0
    ReadRegStr $R0 HKLM "${REGKEY}\Components" "${SECTION_NAME}"
    StrCmp $R0 1 0 next${UNSECTION_ID}
    !insertmacro SelectSection "${UNSECTION_ID}"
    GoTo done${UNSECTION_ID}
next${UNSECTION_ID}:
    !insertmacro UnselectSection "${UNSECTION_ID}"
done${UNSECTION_ID}:
    Pop $R0
!macroend

# Uninstaller sections
Section /o -un.Main UNSEC0000

!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\libeay32.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\ssleay32.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\msvcr90.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\msvcp120.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\msvcr120.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\vccorlib120.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\chaiscript_stdlib.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\libzmq.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\Qt5Widgets.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\Qt5Network.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\Qt5Sql.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\Qt5Gui.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\libEGL.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\libGLESv2.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\Qt5Core.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\platforms\qwindows.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\sqldrivers\qsqlite.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\otapi.dll
!insertmacro UninstallLib DLL    NOTSHARED NOREBOOT_NOTPROTECTED $INSTDIR\otlib.dll


    RMDir /r /REBOOTOK $INSTDIR
    DeleteRegValue HKLM "${REGKEY}\Components" Main
SectionEnd

Section -un.post UNSEC0001
    DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}"

    SetShellVarContext all
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Uninstall ${NAME} Win32.lnk"
    Delete /REBOOTOK "$SMPROGRAMS\$StartMenuGroup\Moneychanger.lnk"
    Delete /REBOOTOK "$SMSTARTUP\${NAME} Win32.lnk"
    Delete /REBOOTOK $INSTDIR\uninstall.exe
    Delete /REBOOTOK $INSTDIR\debug.log
    Delete /REBOOTOK $INSTDIR\db.log
    DeleteRegValue HKLM "${REGKEY}" StartMenuGroup
    DeleteRegValue HKLM "${REGKEY}" Path
    DeleteRegKey /IfEmpty HKLM "${REGKEY}\Components"
    DeleteRegKey /IfEmpty HKLM "${REGKEY}"
    DeleteRegKey HKLM "${NAME}"
    RmDir $SMPROGRAMS\$StartMenuGroup
    RmDir /REBOOTOK $INSTDIR
    Push $R0
    StrCpy $R0 $StartMenuGroup 1
    StrCmp $R0 ">" no_smgroup
no_smgroup:
    Pop $R0
SectionEnd

# Installer functions
Function .onInit
 
  ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${NAME}" "UninstallString"
  StrCmp $R0 "" done
 
  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "${NAME} is already installed. $\n$\nClick `OK` to remove the \
  previous version or `Cancel` to cancel this upgrade." \
  IDOK uninst
  Abort
 
;Run the uninstaller
uninst:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
  IfErrors no_remove_uninstaller done
    ;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.
  no_remove_uninstaller:
 
done:
    InitPluginsDir
FunctionEnd

# Uninstaller functions
Function un.onInit
    ReadRegStr $INSTDIR HKLM "${REGKEY}" Path
    !insertmacro MUI_STARTMENU_GETFOLDER Application $StartMenuGroup
    !insertmacro SELECT_UNSECTION Main ${UNSEC0000}
FunctionEnd