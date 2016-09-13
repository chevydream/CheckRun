; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFullScreenShowDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "checkrun.h"
LastPage=0

ClassCount=5
Class1=CCheckRunApp
Class2=CAboutDlg
Class3=CCheckRunDlg
Class4=CFloatWnd

ResourceCount=5
Resource1=IDD_FLOATWND
Resource2=IDD_ABOUTBOX
Resource3=IDD_FULLSCREENSHOW
Resource4=IDD_CHECKRUN_DIALOG
Class5=CFullScreenShowDlg
Resource5=IDR_MENU

[CLS:CCheckRunApp]
Type=0
BaseClass=CWinApp
HeaderFile=checkRun.h
ImplementationFile=checkRun.cpp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=checkRunDlg.cpp
ImplementationFile=checkRunDlg.cpp

[CLS:CCheckRunDlg]
Type=0
BaseClass=CDialog
HeaderFile=checkRunDlg.h
ImplementationFile=checkRunDlg.cpp

[CLS:CFloatWnd]
Type=0
BaseClass=CDialog
HeaderFile=FloatWnd.h
ImplementationFile=FloatWnd.cpp
Filter=D
VirtualFilter=dWC
LastObject=CFloatWnd

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHECKRUN_DIALOG]
Type=1
Class=CCheckRunDlg
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_FLOATWND]
Type=1
Class=CFloatWnd
ControlCount=2
Control1=IDC_LOGO,static,1342177294
Control2=IDC_SHOWINFO,static,1342177280

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDM_ABOUT
Command2=IDM_EXIT
CommandCount=2

[DLG:IDD_FULLSCREENSHOW]
Type=1
Class=CFullScreenShowDlg
ControlCount=0

[CLS:CFullScreenShowDlg]
Type=0
HeaderFile=FullScreenShowDlg.h
ImplementationFile=FullScreenShowDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CFullScreenShowDlg
VirtualFilter=dWC

