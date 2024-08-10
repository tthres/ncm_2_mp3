!include "MUI2.nsh"
!include "FileFunc.nsh"

; 基本信息
Name "ncm2mp3"
OutFile "ncm2mp3-setup.exe"
InstallDir "$PROGRAMFILES64\ncm2mp3"
InstallDirRegKey HKCU "Software\ncm2mp3" ""
RequestExecutionLevel admin

; 版本信息
VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" "ncm2mp3"
VIAddVersionKey "FileDescription" "ncm2mp3 Installer"
VIAddVersionKey "FileVersion" "1.0.0"
VIAddVersionKey "ProductVersion" "1.0.0"

; 界面设置
!define MUI_ABORTWARNING
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

; 页面
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!define MUI_FINISHPAGE_RUN "$INSTDIR\ncm2mp3.exe"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; 语言
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装部分
Section "ncm2mp3" SecDummy
  SetOutPath "$INSTDIR"
  
  ; 复制主程序和依赖项
  File "ncm2mp3.exe"
  File "Qt6Core.dll"
  File "Qt6Gui.dll"
  File "Qt6Widgets.dll"
  File "Qt6Concurrent.dll"
  
  ; 复制 Qt 插件
  SetOutPath "$INSTDIR\plugins\platforms"
  File "plugins\platforms\qwindows.dll"
  
  SetOutPath "$INSTDIR\plugins\styles"
  File "plugins\styles\qwindowsvistastyle.dll"
  
  ; 复制其他必要的 DLL
  SetOutPath "$INSTDIR"
  File "*.dll"
  
  ; 创建开始菜单快捷方式
  CreateDirectory "$SMPROGRAMS\ncm2mp3"
  CreateShortcut "$SMPROGRAMS\ncm2mp3\ncm2mp3.lnk" "$INSTDIR\ncm2mp3.exe"
  CreateShortcut "$SMPROGRAMS\ncm2mp3\Uninstall.lnk" "$INSTDIR\uninstall.exe"

  ; 创建桌面快捷方式
  CreateShortcut "$DESKTOP\ncm2mp3.lnk" "$INSTDIR\ncm2mp3.exe"

  ; 创建卸载程序
  WriteUninstaller "$INSTDIR\uninstall.exe"

  ; 写入注册表信息
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "DisplayName" "ncm2mp3"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "InstallLocation" "$\"$INSTDIR$\""
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "DisplayIcon" "$\"$INSTDIR\ncm2mp3.exe$\""
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "Publisher" "Your Company Name"
  
  ; 获取安装大小
  ${GetSize} "$INSTDIR" "/S=0K" $0 $1 $2
  IntFmt $0 "0x%08X" $0
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3" "EstimatedSize" "$0"
SectionEnd

; 卸载部分
Section "Uninstall"
  ; 删除安装的文件
  Delete "$INSTDIR\ncm2mp3.exe"
  Delete "$INSTDIR\Qt6Core.dll"
  Delete "$INSTDIR\Qt6Gui.dll"
  Delete "$INSTDIR\Qt6Widgets.dll"
  Delete "$INSTDIR\Qt6Concurrent.dll"
  Delete "$INSTDIR\plugins\platforms\qwindows.dll"
  Delete "$INSTDIR\plugins\styles\qwindowsvistastyle.dll"
  Delete "$INSTDIR\*.dll"
  Delete "$INSTDIR\uninstall.exe"
  
  RMDir "$INSTDIR\plugins\platforms"
  RMDir "$INSTDIR\plugins\styles"
  RMDir "$INSTDIR\plugins"
  RMDir "$INSTDIR"
  
  ; 删除开始菜单快捷方式
  Delete "$SMPROGRAMS\ncm2mp3\ncm2mp3.lnk"
  Delete "$SMPROGRAMS\ncm2mp3\Uninstall.lnk"
  RMDir "$SMPROGRAMS\ncm2mp3"

  ; 删除桌面快捷方式
  Delete "$DESKTOP\ncm2mp3.lnk"

  ; 删除注册表信息
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\ncm2mp3"
SectionEnd