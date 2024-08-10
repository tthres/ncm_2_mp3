!include "MUI2.nsh"

; 基本信息
Name "NCM to MP3 Converter"
OutFile "ncm2mp3-setup.exe"
InstallDir "$PROGRAMFILES\NCM to MP3 Converter"
InstallDirRegKey HKCU "Software\NCM to MP3 Converter" ""

; 界面设置
!define MUI_ABORTWARNING

; 页面
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_INSTFILES
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM
!insertmacro MUI_UNPAGE_INSTFILES

; 语言
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装部分
Section "NCM to MP3 Converter" SecDummy
  SetOutPath "$INSTDIR"
  File /r "build\Release\*.*"
  
  ; 创建开始菜单快捷方式
  CreateDirectory "$SMPROGRAMS\NCM to MP3 Converter"
  CreateShortcut "$SMPROGRAMS\NCM to MP3 Converter\NCM to MP3 Converter.lnk" "$INSTDIR\ncm2mp3.exe"
  CreateShortcut "$SMPROGRAMS\NCM to MP3 Converter\Uninstall.lnk" "$INSTDIR\uninstall.exe"

  ; 创建卸载程序
  WriteUninstaller "$INSTDIR\uninstall.exe"

  ; 写入注册表信息
  WriteRegStr HKCU "Software\NCM to MP3 Converter" "" $INSTDIR
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\NCM to MP3 Converter" "DisplayName" "NCM to MP3 Converter"
  WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\NCM to MP3 Converter" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
SectionEnd

; 卸载部分
Section "Uninstall"
  ; 删除安装的文件
  RMDir /r "$INSTDIR"
  
  ; 删除开始菜单快捷方式
  Delete "$SMPROGRAMS\NCM to MP3 Converter\NCM to MP3 Converter.lnk"
  Delete "$SMPROGRAMS\NCM to MP3 Converter\Uninstall.lnk"
  RMDir "$SMPROGRAMS\NCM to MP3 Converter"

  ; 删除注册表信息
  DeleteRegKey HKCU "Software\NCM to MP3 Converter"
  DeleteRegKey HKCU "Software\Microsoft\Windows\CurrentVersion\Uninstall\NCM to MP3 Converter"
SectionEnd